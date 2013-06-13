/*
 Copyright (C) Johan Ceuppens 2011

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Written by Ch. Tronche (http://tronche.lri.fr:8000/)
// Copyright by the author. This is unmaintained, no-warranty free software. 
// Please use freely. It is appreciated (but by no means mandatory) to
// acknowledge the author's contribution. Thank you.
// Started on Thu Jun 26 23:29:03 1997

//
// Xlib tutorial: 2nd program
// Make a window appear on the screen and draw a line inside.
// If you don't understand this program, go to
// http://tronche.lri.fr:8000/gui/x/xlib-tutorial/2nd-program-anatomy.html
//

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <vector>
#include <iostream>
#include<cmath> 
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include "raymanta/RayManta.h"
#include "raymanta/RayMantaRayTracer.h"
#include "raymanta/RayMantaPoint.h"
#include "raymanta/RayMantaPolygonModel.h"
#include "raymanta/RayMantaPixmapTextureModelRotate.h"
#include "raymanta/RayMantaSpiderModel.h"
#include "raymanta/RayMantaEngine.h"
#include "raymanta/RayMantaMatrix3.h"
#include "config.h"
#include "raymanta/WindowManager.h"
#include "raymanta/RayManta.h"
#include "raymanta/RayMantaWindow.h"

static Display *dpy;
static DisplayBase<Display **> dpyb;
static RayManta xmantaray(xmantaray, dpyb);

void init(Display **dpy, Window *w);
void print_usage();

int main(int argc, char*argv[])
{
//try {//main code block
	
	//Display *dpy = XOpenDisplay(NIL);
	dpy = XOpenDisplay(NIL);
	assert(dpy);
	dpyb = DisplayBase<Display **>(&dpy);
	xmantaray.init(dpyb);	
	if (argc > 1 && (std::string(argv[1]) == std::string("-h") 
		|| std::string(argv[1]) == std::string("-help")
		|| std::string(argv[1]) == std::string("--help"))) {
		print_usage();
		exit(0);
	}

	//FIXME us e a bridge
	//dpyb = DisplayBase<Display **>(&dpy);
	//xmantaray = RayManta(xmantaray, dpyb);

	int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
 	int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
	
	Window w, titlebarw;
	XSetWindowAttributes attrib_create;
	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask | CWBackingPixel;

	attrib_create.background_pixmap = None;
	attrib_create.override_redirect = True;
	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;
	XSizeHints theSizeHints;
        XWMHints theWMHints;

	theWMHints.initial_state = NormalState;
        theWMHints.flags = StateHint;

        theSizeHints.flags = PPosition | PSize;
        theSizeHints.x = 0;//x;
        theSizeHints.y = 0;//y;
        theSizeHints.width = 800;//width;
        theSizeHints.height = 600;//height;

  	Window root_window = RootWindow(dpy, DefaultScreen(dpy));
  	int depth = DefaultDepth(dpy, DefaultScreen(dpy));
  	Visual *visual = DefaultVisual(dpy, DefaultScreen(dpy));
	w = XCreateWindow(dpy, root_window, 40, 40, 
			800, 600,
			1, depth, InputOutput,
			visual, create_mask,
			&attrib_create);
        //XSetWMHints(dpy,w,&theWMHints);
        //XSetNormalHints(dpy,w,&theSizeHints);
  	titlebarw = XCreateWindow(dpy, root_window, 40, 20, 
				800, 20,
				1, depth, InputOutput,
				visual, create_mask,
				&attrib_create);
	XReparentWindow(dpy, titlebarw, w, 0, 0);
	RayMantaWindow raywindow(&dpy,w,titlebarw);

	XSelectInput(dpy, w, StructureNotifyMask);

	XMapWindow(dpy, titlebarw);
	XMapWindow(dpy, w);

	GC gc = XCreateGC(dpy, w, 0, NIL);

	XSetForeground(dpy, gc, whiteColor);
 
  	xmantaray.initwindow(&raywindow);

//	init(&dpy,&w);
        ray3d::PixmapTextureModelRotate pm3(dpyb.get_display(),&w,&gc,"./post.xpm",24,24);
        ray3d::SpiderModel pm4(dpyb.get_display(),&w,&gc,"./gradient.xpm",24,24);

	XEvent e;
  for (int k = 0; k < 100000; k++) {
	//NOTE: draw() is inside eventloop processor
	XFillRectangle(dpy, titlebarw, gc,0,0,800,20);
	XFillRectangle(dpy, w, gc,0,0,800,600);
	xmantaray.eventloop(xmantaray/*,&dpy*/,&e);
	pm3.draw(dpyb.get_display(), &w,200,200);
	pm4.draw(dpyb.get_display(), &w,100,100);
	XFlush(dpy);
  }
  sleep(20);

/*} catch (std::exception &e) {

	std::cout<<"main excepted - "<<e.what()<<std::endl;

}*/
}
/*
void init(Display **dpy, Window *w)
{
  Pixel back_pix, fore_pix;
  back_pix = GetColor(dpy,(char *)"red");
  fore_pix = GetColor(dpy,(char *)"red");
  
  unsigned long gc_mask = 0;
  gc_mask = GCForeground|GCBackground|GCGraphicsExposures|GCLineWidth;
  XGCValues values;
  values.foreground = fore_pix;
  values.background = back_pix;
  values.graphics_exposures = True;
  //values.function = GXcopy|GXand;
  values.line_width = 3;

  Pixel back_pix2, fore_pix2;
  back_pix2 = GetColor(dpy,(char *)"red");
  fore_pix2 = GetColor(dpy,(char *)"red");
  
  unsigned long gc_mask2 = 0;
  gc_mask2 = GCForeground|GCBackground|GCGraphicsExposures|GCLineWidth;
  XGCValues values2;
  values.foreground = fore_pix2;
  values.background = back_pix2;
  values.graphics_exposures = True;
  //values.function = GXcopy|GXand;
  values.line_width = 3;
}
*/
void print_usage()
{
	std::cout<<"\txmantaray [OPTIONS]\n"<<
		   "\t-cast : raytracer code init\n"<<
		   "\tno options : 3D framework\n"<<std::endl;
} 
