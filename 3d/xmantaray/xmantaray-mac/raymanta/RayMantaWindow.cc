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
//local
#include "RayMantaWindow.h"
#include "RayMantaPoint.h"
#include <iostream>
#include <cmath>

RayMantaWindow::RayMantaWindow ()
{}

RayMantaWindow::RayMantaWindow(Display **dpy, Window& w, Window& title) 
{
  printf("creating RayMantaWindow..\n");
  created = False;
 frame.x = 40;//attrib.x;
  frame.y = 40;//attrib.y;
  frame.width = 320;//attrib.width;
  frame.height = 200;//attrib.height;
  frame.border_width = 3;//attrib.border_width;
  frame.window = w;
  frame.title = title;
  title_y = 20; //height of the title frame
  lowerborder_y = 7; //height of the lower border

  /*frame.window = createTopLevelWindow(frame.x, frame.y, frame.width,\
				      frame.height + title_y + lowerborder_y,\
  				      frame.border_width);
  */ //XRaiseWindow(*dpy, frame.application_window);
  //XMapWindow(*dpy, frame.window);
  XMapWindow(*dpy, w);
//  //  XMapSubwindows(*dpy, frame.application_window);
//  XMapSubwindows(*dpy, frame.window);
  
//  XMapSubwindows(*dpy, frame.title);
  
//  XUngrabServer(*dpy); 
//   decorate_title();
  	XFlush(*dpy);
//	sleep(10);
 /* 
  Pixel back_pix, fore_pix;
  back_pix = GetColor("black");
  fore_pix = GetColor("darkcyan");
  
  unsigned long gc_mask = 0;
  gc_mask = GCForeground|GCBackground|GCGraphicsExposures|GCLineWidth;
  XGCValues values;
  values.foreground = fore_pix;
  values.background = back_pix;
  values.graphics_exposures = True;
  //values.function = GXcopy|GXand;
  values.line_width = 3;
  gc = XCreateGC(*dpy, pixie.getRootWindow(), gc_mask, &values);
  //XChangeGC(*dpy, gc, gc_mask, &values); //overbodig?
  //XSetFillStyle(*dpy, gc, FillSolid);
  XSetClipOrigin(*dpy, gc, 0, 0);
  XSetClipMask(*dpy, gc, None);
  XFillRectangle(*dpy, pixie.getRootWindow(), gc, 0,0,50,50);
  //XDrawRectangle(*dpy, pixie.getRootWindow(), gc, 0,0,200,200);
  //XFillRectangle(*dpy, pixie.getRootWindow(), gc, 0,0,50,50);
*/
/*#define NIL (0)
 gc = XCreateGC(0,w,0,NIL);
//XSetForeground(0,gc,whiteColor);
//XDrawLine(0,w,gc,10,60,180,20);
XFlush(0);
//sleep(10);
*/
}

RayMantaWindow::~RayMantaWindow()
{
  //XDestroyWindow(*dpy, frame.title);
  //XDestroyWindow(*dpy, frame.application_window);
  //XDestroyWindow(*dpy, window);
//  XDestroyWindow(*dpy, frame.window);//destroys subwindows
  printf("RayMantaWindow destroyed.\n");
}
void RayMantaWindow::drawsphere(Window const& w)
{
 /* for (int xx = 0; xx < 200; xx++) {
	for (int yy = 0; yy < 200; yy++) {

  double r = 4;
  ray3d::Point s(xx,yy,0);
  ray3d::Point center(10,10,10); 
  ray3d::Point v = s - center; 
  ray3d::Point d(7,7,7);
  //double t = (2*v*d + std::sqrt(2*v*d-4(v*v-r*r))/2 
  double t1 = - (v*d) - std::sqrt((v*d)*(v*d) - (v*v - r*r));
  double t2 = - (v*d) + std::sqrt((v*d)*(v*d) - (v*v - r*r));


  if (t1 > 0 && t2 > 0) {
  std::cout<< "--->"<<t1<<t2<<std::endl;
#define NIL (0)
        gc = XCreateGC(*dpy, w, 0, NIL);
      XDrawLine(*dpy, w, gc, 10, 60, 180, 20);
  //	XDrawLine(*dpy, pixie.getRootWindow(), gc, 0,0,t1,t2);
	}
	}
	}
*/
}

void RayMantaWindow::drawline(Window const& w, int x1, int y1, int x2 ,int y2)
{
/*
      int blackColor = BlackPixel(*dpy, DefaultScreen(*dpy));
      int whiteColor = WhitePixel(*dpy, DefaultScreen(*dpy));
      XSelectInput(*dpy, w, StructureNotifyMask);

      // "Map" the window (that is, make it appear on the screen)

      XMapWindow(*dpy, w);

      // Create a "Graphics Context"
#define NIL (0)
      GC gc = XCreateGC(*dpy, w, 0, NIL);

      // Tell the GC we draw using the white color

      XSetForeground(*dpy, gc, whiteColor);

      // Wait for the MapNotify event

      for(;;) {
	    XEvent e;
	    XNextEvent(*dpy, &e);
	    if (e.type == MapNotify)
		  break;
      }

      // Draw the line
      
      XDrawLine(*dpy, w, gc, 10, 20, 10, 200);

      // Send the "DrawLine" request to the server

      XFlush(*dpy);
*/
}


Window RayMantaWindow::createTopLevelWindow(int x, int y, unsigned int width,\
				   unsigned int height,\
				   unsigned int borderwidth,Window *w)
{
/*  XSetWindowAttributes attrib_create;
  unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  attrib_create.background_pixmap = None;
  attrib_create.override_redirect = True;
  attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

  *w =  (XCreateWindow(*dpy, pixie.getRootWindow(), x, y, 
			width, height,
			borderwidth, pixie.getDepth(), InputOutput,
			pixie.getVisual(), create_mask,
			&attrib_create));
   return *w;
*/
}

Window RayMantaWindow::createTopLevelSimpleWindow(int x, int y, unsigned int width,\
				   unsigned int height,\
				   unsigned int borderwidth)
{
 /* XSetWindowAttributes attrib_create;
  unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  attrib_create.background_pixmap = None;
  attrib_create.override_redirect = True;
  attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;
      int blackColor = BlackPixel(*dpy, DefaultScreen(*dpy));
      int whiteColor = WhitePixel(*dpy, DefaultScreen(*dpy));
      Window w = XCreateSimpleWindow(*dpy, DefaultRootWindow(*dpy), 0, 0, 
				     200, 100, 0, blackColor, blackColor);
	return w;
*/
}

Window RayMantaWindow::createChildWindow(Window parent, Cursor cursor) 
{
/*  XSetWindowAttributes attrib_create;
  unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWEventMask;

  attrib_create.background_pixmap = None;
  attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | ExposureMask |
                             EnterWindowMask | LeaveWindowMask;

  if (cursor) {
    create_mask |= CWCursor;
    attrib_create.cursor = cursor;
  }

  return (XCreateWindow(*dpy, parent, 0, 0, 1, 1, 0,
			pixie.getDepth(), InputOutput, pixie.getVisual(),
			create_mask, &attrib_create));
*/
}

void RayMantaWindow::decorate_title() 
{
/*  unsigned long valuemask = *//*GCFunction;*//*GCForeground | GCBackground | GCGraphicsExposures;
  XGCValues values;
  //Pixel f_pix, b_pix;
  //values.function = GXxor;    
  //GC gc = XCreateGC(*dpy, pixie.getRootWindow(),valuemask, &values); 
  gc = XCreateGC(*dpy, frame.window,rootwin,valuemask, &values); 
  

  //RayMantaImage * pix = new RayMantaImage ("/usr/X11R6/include/X11/pixmaps/mini-eyes.xpm", 
  //			   (Drawable)frame.title, gc);


  //new RayMantaImage("/home/johan/mutt.xpm", pixie.getRootWindow());
  //XSetClipOrigin(*dpy,gc,frame.x, frame.y);
  //XSetClipMask(*dpy, gc,None);// pix->pixmap);  
  //XFillRectangle(*dpy, frame.title, gc, 0,0,50,50);
  XDrawLine(*dpy, frame.window, gc, 0,0, frame.width, 0);
  XDrawLine(*dpy, frame.window, gc, frame.width-1,0,frame.width-1,title_y);
  char **argv;
  int argc;
  if (XGetCommand(*dpy, window, &argv, &argc))
    {
  */    /*
	int i;
	char **fonts = XListFonts(*dpy, "helvetica", 100, &i);
	for (int j = 0; j<100; j++)
	printf("%s ", fonts[j]);
      */
   /*   //XFontSet fs = pixie.createFontSet();
      Pixel back_pix, fore_pix;
      back_pix = GetColor((char *)"black");
      fore_pix = GetColor((char *)"black");
      
      unsigned long gc_mask = 0;
      gc_mask = GCForeground|GCBackground|GCGraphicsExposures|GCLineWidth;
      XGCValues values;
      values.foreground = fore_pix;
      values.background = back_pix;
      values.graphics_exposures = True;
      //values.function = GXcopy|GXand;
      values.line_width = 3;
      XChangeGC(*dpy, gc, gc_mask, &values);
      XmbDrawString(*dpy, frame.title, pixie.getFontSet(), gc, 10, 15, argv[0], strlen(argv[0]));
      back_pix = GetColor((char *)"black");
      fore_pix = GetColor((char *)"darkcyan");
      
      values.foreground = fore_pix;
      values.background = back_pix;
      XChangeGC(*dpy, gc, gc_mask, &values);
  XDrawLine(*dpy, frame.window, gc, 0,0, 30, 30);
    }
*/
}

//remove this and use the pixie.getcolor
Pixel RayMantaWindow::GetColor(Display **dpy, char *name)
{
  XColor color;
  XWindowAttributes attributes;

  Window root_window = RootWindow(*dpy, DefaultScreen(*dpy));
  XGetWindowAttributes(*dpy,root_window,&attributes);
  color.pixel = 0;
   if (!XParseColor (*dpy, attributes.colormap, name, &color)) 
     {
       printf("parse no color");
     }
   else if(!XAllocColor (*dpy, attributes.colormap, &color)) 
     {
       printf("parse no color");
     }
  return color.pixel;
}

void RayMantaWindow::destroy(Display **dpy) 
  //first unmap then destroy after the unmap event
{
  // XDestroyWindow(*dpy, frame.window);
  //XSelectInput(*dpy, window, NoEventMask);
  XUnmapWindow(*dpy, frame.window); //unmaps subwindows
  //XFlush(*dpy);test
  //XUnmapSubwindows(*dpy, frame.window);
  delete this;
}

void RayMantaWindow::unmap(Display **dpy)
{
  //XGrabServer(*dpy); //This bugs some apps
  //the next could break since wins are referenced after during destroy
  // XSelectInput(*dpy, window, NoEventMask);
  //XSelectInput(*dpy, frame.window, NoEventMask); //redundant
  //XSetWindowAttributes attrib;
  
  XUnmapWindow(*dpy, frame.window);
  //XUnmapWindow(*dpy, frame.title);
  //  XUnmapWindow(*dpy, window);
  XFlush(*dpy);
  //delete this; This bugs apps (gv) i.e. the parent unmapped while a little wondow takes care of the user 
  //XUngrabServer(*dpy);
}

void RayMantaWindow::resize(Display **dpy, int x, int y)
{
  frame.width = frame.width-x;
  frame.height = frame.height-y;
  XResizeWindow(*dpy, frame.window, frame.width, frame.height + lowerborder_y + title_y);
  XResizeWindow(*dpy, window, frame.width, frame.height);
  XResizeWindow(*dpy, frame.title, frame.width, title_y);	      
  XResizeWindow(*dpy, frame.lowerborder, frame.width, lowerborder_y);
  XReparentWindow(*dpy, frame.lowerborder, frame.window, 0, frame.height+title_y);
 // XReparentWindow(*dpy, frame.destroy, frame.title, frame.width-title_y, 5);
  decorate_title();
}

void RayMantaWindow::configure(Display **dpy, XConfigureRequestEvent xcr)
{
  //if (xcr.window == window) //only the client window should get configurerequest
  //{
      frame.x = xcr.x;
      frame.y = xcr.y;
      frame.width = xcr.width;
      frame.height = xcr.height;
      XResizeWindow(*dpy, window, frame.width, frame.height);
      XMoveResizeWindow(*dpy, frame.window, frame.x, frame.y, frame.width, frame.height+title_y+lowerborder_y); //--FIXME This moves too no check for x,y =(0,0) or something!
      XResizeWindow(*dpy, frame.title, frame.width, title_y);
      XResizeWindow(*dpy, frame.lowerborder, frame.width, lowerborder_y);
      XReparentWindow(*dpy, frame.lowerborder, frame.window, 0, frame.height+title_y);
      decorate_title();
      //    }
}

void RayMantaWindow::expose(XExposeEvent& xe)
{/*
  if (xe.window == frame.title)
    {
      decorate_title();
      frame.x_root = xe.x;
   */   frame.y_root = xe.y;
      printf("RayMantaWindow expose\n");
     /* 
      if (!created)
	{
	  //pixie.positionWindow(this);
	  created = True;
	}
      
    }*/
  /* this doesnt' do anything apparently only title and lowerborder get expose events
     else if (xe.window == frame.window && !created)//last window created maybe
     {
     pixie.positionWindow(this);
     }*/
}

void RayMantaWindow::move(Display **dpy, int new_x, int new_y)
{
  XMoveWindow(*dpy, frame.window, new_x, new_y);
  frame.x = new_x;
  frame.y = new_y;
}

void RayMantaWindow::buttonpress()
{
  
}

void RayMantaWindow::motion()
{

}
