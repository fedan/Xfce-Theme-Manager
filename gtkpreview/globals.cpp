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
 * Globals.cpp
 */
#include <gdk-pixbuf/gdk-pixbuf.h>

//current stuff
int		wallStyle=0;
char*		currentIconTheme;
char*		currentWmTheme;
char*		currentCursorTheme;
char*		currentWallPaper;
char*		currentGtkTheme;
char*		currentTheme;

//db
//char		metaFolder[4096];
char*		metaFolder;
char*		framesFolder;
char*		controlsFolder;
char*		iconsFolder;
char*		cursorsFolder;
char*		wallpapersFolder;

//to bie gone
int		button_offset,button_spacing;
GdkPixbuf*	gtkPixbuf;
int		boxhite=90;
int		gtkwidth=200;
int		gtkheight=50;
char*		cursorTheme;
char*		iconTheme;
char*		localIcons;
char*		localThemes;
