/******************************************************
*
*     ©keithhedger Mon 17 Jun 12:11:12 BST 2013
*     kdhedger68713@gmail.com
*
*     panels.cpp
* 
******************************************************/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <xfconf/xfconf.h>

#include "globals.h"

bool	panelChanging=false;
int		panelNumbers[10];

void setPanelData(bool fromwidget)
{
	panelData*	panel;
	GdkColor	colour;
	char		buffer[1024];
	XfconfChannel*	channelptr=xfconf_channel_get(XFCEPANELS);
	int alpha=65535;

	if(panelChanging==false)
		{
			panel=panels[currentPanel];
//style
			if(fromwidget==true)
				panel->style=gtk_combo_box_get_active((GtkComboBox*)panelStyleWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/background-style",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->style);

//size
			if(fromwidget==true)
				panel->size=gtk_range_get_value((GtkRange*)panelSizeWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/size",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->size);
//image
			if(fromwidget==true)
				{
					freeAndNull(&panel->imagePath);
					panel->imagePath=gtk_file_chooser_get_filename((GtkFileChooser*)panelImagePathWidget);
				}
			sprintf((char*)&buffer,"/panels/panel-%i/background-image",panel->panelNumber);
			setValue(XFCEPANELS,buffer,STRING,(void*)(long)panel->imagePath);

//alpha
			if(fromwidget==true)
				panel->alpha=gtk_range_get_value((GtkRange*)panelAlphaWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/background-alpha",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->alpha);
//colour
			if(fromwidget==true)
				{
					gtk_color_button_get_color((GtkColorButton*)panelColourWidget,&colour);
					panel->red=colour.red;
					panel->green=colour.green;
					panel->blue=colour.blue;
				}

			sprintf((char*)&buffer,"/panels/panel-%i/background-color",panel->panelNumber);
			xfconf_channel_set_array(channelptr,(const gchar*)&buffer,XFCONF_TYPE_UINT16,&panel->red,XFCONF_TYPE_UINT16,&panel->green,XFCONF_TYPE_UINT16,&panel->blue,XFCONF_TYPE_UINT16,&alpha,G_TYPE_INVALID);
		}
}

gboolean panelSizeCallback(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	setPanelData(true);
	return(false);
}

void commnonPanelCallback(GtkWidget* widget,gpointer data)
{
	setPanelData(true);
}

void selectPanelStyle(GtkWidget* widget,gpointer data)
{
	int style;
	style=gtk_combo_box_get_active((GtkComboBox*)widget);

	switch(style)
		{
			case 0:
				gtk_widget_set_sensitive(panelImageBox,false);
				gtk_widget_set_sensitive(panelColourBox,false);
				gtk_widget_set_sensitive(panelAlphaBox,true);
				break;
			case 1:
				gtk_widget_set_sensitive(panelImageBox,false);
				gtk_widget_set_sensitive(panelColourBox,true);
				gtk_widget_set_sensitive(panelAlphaBox,true);
				break;
			case 2:
				gtk_widget_set_sensitive(panelColourBox,false);
				gtk_widget_set_sensitive(panelAlphaBox,false);
				gtk_widget_set_sensitive(panelImageBox,true);
				break;
		}

	setPanelData(true);
}

void selectPanel(GtkComboBox *widget, gpointer user_data)
{
	panelData*	panel;
	GdkColor	colour;

	panelChanging=true;
	currentPanel=gtk_combo_box_get_active((GtkComboBox*)panelSelect);

	panel=panels[currentPanel];

	gtk_combo_box_set_active((GtkComboBox*)panelStyleWidget,panel->style);
	gtk_file_chooser_set_filename((GtkFileChooser*)panelImagePathWidget,panel->imagePath);
	gtk_range_set_value((GtkRange*)panelSizeWidget,panel->size);

	colour.red=panel->red;
	colour.green=panel->green;
	colour.blue=panel->blue;
	gtk_color_button_set_color((GtkColorButton*)panelColourWidget,&colour);

	gtk_range_set_value((GtkRange*)panelAlphaWidget,panel->alpha);

	selectPanelStyle(panelStyleWidget,NULL);
	panelChanging=false;
}

void setPanelColour(GtkColorButton *widget, gpointer user_data)
{
	GdkColor	colour;
	int			panelnum;

	gtk_color_button_get_color((GtkColorButton*)widget,&colour);
	panelnum=gtk_combo_box_get_active((GtkComboBox*)panelSelect);
	panels[panelnum]->red=colour.red;
	panels[panelnum]->green=colour.green;
	panels[panelnum]->blue=colour.blue;
	setPanelData(true);
}

void makeNewPanelData(int num,int panelnum)
{
	panels[num]=(panelData*)malloc(sizeof(panelData));
	panels[num]->style=0;
	panels[num]->size=48;
	panels[num]->imagePath=NULL;
	panels[num]->red=56540;
	panels[num]->green=56026;
	panels[num]->blue=54741;
	panels[num]->alpha=100;
	panels[num]->panelNumber=panelnum;
	panelNumbers[num]=panelnum;
}

void populatePanels(void)
{
	FILE*	fp;
	char	buffer[1024];
	char	command[1024];
	int		cnt=0;

	bool	gotthispanel;
	for(int j=0;j<10;j++)
		{
			gotthispanel=false;
			buffer[0]=0;

			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-style 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->style=atoi(buffer);
				}
			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/size 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->size=atoi(buffer);
				}

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-image 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}

					buffer[strlen(buffer)-1]=0;
					panels[cnt]->imagePath=strdup(buffer);
				}

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-color 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}

					fgets(buffer,1024,fp);

					fgets(buffer,1024,fp);
					panels[cnt]->red=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[cnt]->green=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[cnt]->blue=atoi(buffer);
				}
			pclose(fp);

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-alpha 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->alpha=atoi(buffer);
				}

			if(gotthispanel==true)
				{
					revertPanels[cnt]=(panelData*)malloc(sizeof(panelData));
					revertPanels[cnt]->style=panels[cnt]->style;
					revertPanels[cnt]->size=panels[cnt]->size;
					if(panels[cnt]->imagePath!=NULL)
						revertPanels[cnt]->imagePath=strdup(panels[cnt]->imagePath);
					else
						revertPanels[cnt]->imagePath=NULL;
					revertPanels[cnt]->red=panels[cnt]->red;
					revertPanels[cnt]->green=panels[cnt]->green;
					revertPanels[cnt]->blue=panels[cnt]->blue;
					revertPanels[cnt]->alpha=panels[cnt]->alpha;
					revertPanels[cnt]->panelNumber=panelNumbers[cnt];
					cnt++;
				}
		}
	numOfPanels=cnt;
}

void setPanels(void)
{
	panelChanging=false;
	for(int j=0;j<numOfPanels;j++)
		{
			currentPanel=j;
			setPanelData(false);
		}

	currentPanel=0;
	selectPanel((GtkComboBox*)panelSelect,NULL);
}

void resetPanels(void)
{
	for(int j=0;j<numOfPanels;j++)
		{
			if(panels[j]->imagePath!=NULL)
				g_free(panels[j]->imagePath);
			g_free(panels[j]);
			panels[j]=(panelData*)malloc(sizeof(panelData));
			panels[j]->style=revertPanels[j]->style;
			panels[j]->size=revertPanels[j]->size;
			if(revertPanels[j]->imagePath!=NULL)
				panels[j]->imagePath=strdup(revertPanels[j]->imagePath);
			else
				panels[j]->imagePath=NULL;
			panels[j]->red=revertPanels[j]->red;
			panels[j]->green=revertPanels[j]->green;
			panels[j]->blue=revertPanels[j]->blue;
			panels[j]->alpha=revertPanels[j]->alpha;
			panels[j]->panelNumber=panelNumbers[j];
		}
	setPanels();
}
