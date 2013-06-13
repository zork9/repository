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
#include <iostream>
#include<cmath> 
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include<pthread.h> 
#include "RayManta.h"
#include "RayMantaPoint.h"
#include "config.h"
#include "WindowManager.h"
#include "RayManta.h"
#include "RayMantaWindow.h"

RayManta pixie;

#define NIL (0)       // A name for the void pointer
Display *dpy;
int xx,yy,zz;	
Window w;

void *drawonce(void *arg) {
	double r = 4;
	Point s(xx*10,yy*10,zz*10);
  	Point center(10,10,10); 
  	Point v = s - center; 
  	Point d(1,1,0);
  	//double t = (2*v*d + std::sqrt(2*v*d-4(v*v-r*r))/2 
  	double discr = (v*d)*(v*d) - (v*v - r*r);
  	double t1 = - (v*d) - std::sqrt((v*d)*(v*d) - (v*v - r*r));
 	double t2 = - (v*d) + std::sqrt((v*d)*(v*d) - (v*v - r*r));

  	std::cout<< "--->"<<t1<<t2<<std::endl;

  	//if (discr >= 0) 
	{
      	GC gc = XCreateGC(dpy, w, 0, NIL);
  	//XDrawRectangle(dpy, w, gc, 0,0,t1,t2);
  	XDrawLine(dpy, w, gc, 0,0,t1,t2);
      	//XMapWindow(dpy, w);
	}
	return (void *)0;
}

int main(int argc, char*argv[])
{
      // Open the display

      dpy = XOpenDisplay(NIL);
      assert(dpy);

      // Get some colors

      int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
      int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

      // Create the window
	
      Window titlebarw;
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
        theSizeHints.width = 320;//width;
        theSizeHints.height = 200;//height;




  w = XCreateWindow(pixie.getDisplay(), pixie.getRootWindow(), 40, 40, 
			320, 200,
			1, pixie.getDepth(), InputOutput,
			pixie.getVisual(), create_mask,
			&attrib_create);
        //XSetWMHints(dpy,w,&theWMHints);
        //XSetNormalHints(dpy,w,&theSizeHints);
	//w = RayMantaWindow().createTopLevelWindow(0,0,100,100,3,&w);
  //titlebarw = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 80, 80,320, 200, 0, blackColor, blackColor);
  titlebarw = XCreateWindow(pixie.getDisplay(), pixie.getRootWindow(), 40, 20, 
			320, 20,
			1, pixie.getDepth(), InputOutput,
			pixie.getVisual(), create_mask,
			&attrib_create);
  XReparentWindow(pixie.getDisplay(), titlebarw, w, 0, 0);
	//RayMantaWindow *rmw = new RayMantaWindow();
      RayMantaWindow raywindow(w,titlebarw);

      // We want to get MapNotify events

      XSelectInput(dpy, w, StructureNotifyMask);

      // "Map" the window (that is, make it appear on the screen)

      XMapWindow(dpy, titlebarw);
      XMapWindow(dpy, w);

      // Create a "Graphics Context"

      GC gc = XCreateGC(dpy, w, 0, NIL);

      // Tell the GC we draw using the white color

      XSetForeground(dpy, gc, whiteColor);

      // Wait for the MapNotify event
/*
      for(;;) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
      }
*/
      // Draw the line
      //raywindow.drawline(w, 0,0,70,70); 
      //XDrawLine(dpy, w, gc, 10, 60, 180, 20);
      // Send the "DrawLine" request to the server
//	raywindow.drawsphere(w);

  for (zz = 0; zz< 20; zz++) {
  for (xx = 0; xx < 20; xx++) {
  for (yy = 0; yy < 20; yy++) {
  pthread_t pid;
  pthread_create(&pid, NULL, drawonce, NULL);	
  }
  }
  }
  pixie.set_windows(&raywindow);
  pixie.eventloop();
  XFlush(dpy);

      sleep(10);
}

