/*
 * Original author of parts of gtkpreview David D Lowe <daviddlowe.flimm@gmail.com>
 * Parts of cursor preveiw Copyright (c) 2008 Nick Schermer <nick@xfce.org> & Jannis Pohlmann <jannis@xfce.org>
 * from xfce4-settings-4.6.5/dialogs/mouse-settings
 *
 * Parts of xwm4 4.10pre
 *
 * oroborus - (c) 2001 Ken Lynch
 * xfwm4    - (c) 2002-2011 Olivier Fourdan
 *
 * Seriously mucked about by:
 *
 * K.D.Hedger 2012 <kdheger@yahoo.co.uk>
 *
 * Globals.h
 */

#include <gdk-pixbuf/gdk-pixbuf.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define PADWIDTH 72
#define MAXBOXWIDTH 240
#define ICONSIZE 32
#define ICONPAD 8

#define XCONFSETSTYLE "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style -s "
#define XCONFSETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/brightness -s "
#define XCONFSETSATU "xfconf-query -nRt double -c xfce4-desktop -vp /backdrop/screen0/monitor0/saturation -s "
#define XCONFSETIMAGEPATH "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path -s "

#define XCONFSETFRAME "xfconf-query -nRt string -c xfwm4 -vp /general/theme -s "
#define XCONFSETCONTROLS "xfconf-query -nRt string -c xsettings -vp /Net/ThemeName -s "
#define XCONFSETICONS "xfconf-query -nRt string -c xsettings -vp /Net/IconThemeName -s "
#define XCONFSETCURSOR "xfconf-query -nRt string -c xsettings -vp /Gtk/CursorThemeName -s "

#define GLOBALICONS "/usr/share/icons"
#define GLOBALTHEMES "/usr/share/themes"

#define XCONFGETCONTROLS "xfconf-query -c xsettings -vp /Net/ThemeName"
#define XCONFGETICONS "xfconf-query -c xsettings -vp /Net/IconThemeName"
#define XCONFGETCURSOR "xfconf-query -c xsettings -vp /Gtk/CursorThemeName"
#define XCONFGETFRAME "xfconf-query -c xfwm4 -vp /general/theme"
#define XCONFGETPAPER "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path"

extern int		wallStyle;
extern char*		currentIconTheme;
extern char*		currentWmTheme;
extern char*		currentCursorTheme;
extern char*		currentWallPaper;
extern char*		currentGtkTheme;
extern char*		currentTheme;

//db
extern char*		metaFolder;
extern char*		framesFolder;
extern char*		controlsFolder;
extern char*		iconsFolder;
extern char*		cursorsFolder;
extern char*		wallpapersFolder;

//to bie gone
extern int		button_offset,button_spacing;
extern GdkPixbuf*	gtkPixbuf;
extern int		boxhite;
extern int		gtkwidth;
extern int		gtkheight;
extern char*		cursorTheme;
extern char*		iconTheme;
extern char*		localIcons;
extern char*		localThemes;


#endif
