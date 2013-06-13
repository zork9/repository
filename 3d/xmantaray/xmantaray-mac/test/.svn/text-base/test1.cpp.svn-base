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
#include <cassert>
#include <X11/Xlib.h>
#include "RayManta.h"
#include "RayMantaEngine.h"
#define NIL (0)
RayManta pixie;
void draw(Display **dpy, Window *w, int const& k);
void init() {
	Display *dpy = XOpenDisplay(NIL);
//	std::assert(dpy);

	int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
 	int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
	
	Window w, titlebarw;
	XSetWindowAttributes attrib_create;
	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

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

	w = XCreateWindow(pixie.getDisplay(), pixie.getRootWindow(), 40, 40, 
			800, 600,
			1, pixie.getDepth(), InputOutput,
			pixie.getVisual(), create_mask,
			&attrib_create);
        //XSetWMHints(dpy,w,&theWMHints);
        //XSetNormalHints(dpy,w,&theSizeHints);
  	titlebarw = XCreateWindow(pixie.getDisplay(), pixie.getRootWindow(), 40, 20, 
				800, 20,
				1, pixie.getDepth(), InputOutput,
				pixie.getVisual(), create_mask,
				&attrib_create);
	XReparentWindow(pixie.getDisplay(), titlebarw, w, 0, 0);
	RayMantaWindow raywindow(w,titlebarw);

	XSelectInput(dpy, w, StructureNotifyMask);

	XMapWindow(dpy, titlebarw);
	XMapWindow(dpy, w);

	GC gc = XCreateGC(dpy, w, 0, NIL);

	XSetForeground(dpy, gc, whiteColor);

  pixie.init(&raywindow,&gc);
  for (int k = 0; k < 100000; k++) {
	draw(&dpy,&w,k);
	pixie.eventloop();
	XFlush(dpy);
  }

}

void draw(Display **dpy, Window *w, int const& k)
{
	init();

	//3D rotation code
        ray3d::Engine e(0.1,0.1,0.1);
        ray3d::Vector3 v1(0,0,0), v2(100,100,100);
        ray3d::Matrix3 rotm = ray3d::Matrix3(e.rotate(0.1,0.1,0.1));
        GC gc = XCreateGC(*dpy, *w, 0, NIL);
        rotm = ray3d::Matrix3(e.rotate(0.1*k,0.1*k,0.1*k));
        //rotm = ray3d::Matrix3(e.initrotatex(0.1*k));

        v1 = rotm*v1;
        v2 = rotm*v2;
        std::cout<<"matrix x22>"<<rotm.get_x22()<<std::endl;
        XDrawLine(*dpy,*w,gc,(int)v1.get_x(),(int)v1.get_y(),(int)v2.get_x(),(int)v2.get_y());
}
