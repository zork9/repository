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

#include "RayManta.h"
#include "RayMantaRayTracer.h"
#include "Xmanager.h"
#include "RayMantaWindow.h"
#include "RayMantaPoint.h"
#include "RayMantaEngine.h"
#include "RayMantaMatrix3.h"
#include "RayMantaPolygonModel.h"
#include "RayMantaSphereModel.h"
#include "RayMantaImage.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaPixmapTextureModelRotate.h"


static double theta = 1.5;
static double theta2 = 2.5;
static double theta3 = 3.5;
int RayManta::draw2(Display **dpy, int const& k)
{
	Window w = window->getTitleWindow();
	Window w2 = window->getWindow(); 
//	RayMantaImage pix(dpyb->dpy);
//	pix.init();
//	pix.putpixel(10,10,12000);


      int blackColor = 128;//BlackPixel(dpyb->dpy, DefaultScreen(dpyb->dpy));
      int whiteColor = 2048;//WhitePixel(dpyb->dpy, DefaultScreen(dpyb->dpy));
	//blackColor <<= 8;
	//whiteColor <<= 16;

  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*(dpyb.get_display()),w,create_mask,&attrib_create);
	XGCValues values;
	values.foreground = 10400;//RedPixel(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display())));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), valuemask, &values);
	//3D rotation code
        ray3d::SphereModel sm(dpy,&w,&gc);
	//pix.draw(dpy, &w2,0,0);
	//XDrawLine(*(dpyb.get_display()), w2,gc, 0,0,100,100);
	sm.generatesphere(dpy, &w2);
	//sm.draw(dpy,&w2);
	sm.raytrace(dpy,&w2,ray3d::Point(0,0,0));
	return 0;
}

int RayManta::draw(RayMantaBase& rmb)
{
	Window w = window->getWindow(); 
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
	//3D rotation code
        ray3d::PolygonModel pm(dpyb.get_display(),&w,&gc);
        ray3d::PolygonModel pm2(dpyb.get_display(),&w,&gc);
        //ray3d::PixmapTextureModel pm3(dpyb.get_display(),&w,&gc,"./test640x480.xpm",640,480);
	ray3d::Polygon poly;

	poly += ray3d::Point(2,2,2);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(520,220,220);
	poly += ray3d::Point(2,2,2);
	pm.add(poly);
//	pm3.add(poly);

	pm2.filein("./polygonmodel");	

	pm.draw(dpyb.get_display(), &w);
	pm2.draw(dpyb.get_display(), &w);
//	pm3.draw(dpyb.get_display(), &w,200,200);
	//poly.draw(dpy, &w);
        ray3d::Vector3 v1(0,0,0), v2(100,100,100);
        ray3d::Matrix3 rotmx,rotmy,rotmz;
        //rotm = ray3d::Matrix3(e.initrotatex(0.1*k));
        rotmx = ray3d::rotatex(theta);
        rotmy = ray3d::rotatey(theta2);
        rotmz = ray3d::rotatez(theta3);

        v2 = rotmx*v2;
        v2 = rotmy*v2;
        v2 = rotmz*v2;
        //std::cout<<"matrix x22>"<<rotm.get_x22()<<std::endl;
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)v1.get_x(),(int)v1.get_y()+TITLEWINH,(int)v2.get_x(),(int)v2.get_y()+TITLEWINH);

	return 0;
}
//#include "widget/Button.h"
int RayManta::draw3(Display **dpy, int const& k)
{
	//3D rotation code
	theta *= 2;
	theta2 *= 3;
	theta3 *= 8;
        ray3d::Engine e(0.1,0.1,0.1);
        ray3d::Vector3 v1(10,10,10), v2(140,140,140);
	ray3d::Vector3 v3(140,140,140);
        ray3d::Matrix3 rotmx,rotmy,rotmz;
#define NIL (0)
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
        //rotm = ray3d::Matrix3(e.rotate(theta,theta2,theta3));
        rotmx = ray3d::rotatex(theta);
        rotmy = ray3d::rotatey(theta2);
        rotmz = ray3d::rotatez(theta3);

	v2 = rotmx*v3;	
	v2 = rotmy*v2;	
	v2 = rotmz*v2;	

        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)(v3.get_x()),(int)(v3.get_y()),(int)(v2.get_x()),(int)(v2.get_y()));

	return 0;
}

int RayManta::drawsphere(Display **dpy, int const& k)
{
	Window w = window->getWindow(); 
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
	//3D rotation code
        ray3d::SphereModel sm(dpy,&w,&gc);

	sm.generatesphere(dpy, &w);
	sm.draw(dpy,&w);
/*        ray3d::Vector3 v1(0,0,0), v2(100,100,100);
        ray3d::Matrix3 rotmx,rotmy,rotmz;
        //rotm = ray3d::Matrix3(e.initrotatex(0.1*k));
        rotmx = ray3d::rotatex(theta1);
        rotmy = ray3d::rotatey(theta12);
        rotmz = ray3d::rotatez(theta13);

//        v2 = rotmx*v2;
//        v2 = rotmy*v2;
//        v2 = rotmz*v2;
        //std::cout<<"matrix x22>"<<rotm.get_x22()<<std::endl;
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,0,0,100,100);
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)v1.get_x(),(int)v1.get_y(),(int)v2.get_x(),(int)v2.get_y());
*/
	return 0;
}

int RayManta::drawdish(Display **dpy, int const& k)
{
	//3D rotation code
	theta *= 2;
        ray3d::Engine e(0.1,0.1,0.1);
        ray3d::Vector3 v1(10,10,10), v2(140,140,140);
        ray3d::Matrix3 rotm;// = ray3d::Matrix3(e.rotate(0.1,0.1,0.1));
#define NIL (0)
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
        //rotm = ray3d::Matrix3(e.rotate(theta,theta,theta));
        rotm = ray3d::rotatex(theta);//ray3d::Matrix3(e.rotatex(3.1));

	ray3d::Vector3 v3(140,140,140);
	v2 = rotm*v3;	

        //v2 = rotm*v1;
        //ray3d::Vector3 v3 = rotm*v2;
        std::cout<<"matrix x22>"<<rotm.get_x22()<<std::endl;
        //std::cout<<"v3.x>"<<v3.get_x()<<std::endl;
	  //XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,0,0,100,100);
        //XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)v1.get_x()*100,(int)v1.get_y()*100,(int)v2.get_x()*100,(int)v2.get_y()*100);
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)(v3.get_x()),(int)(v3.get_y()),(int)(v2.get_x()),(int)(v2.get_y()));


	return 0;
}

void RayManta::init(DisplayBase<Display **>& dpyb2)
{
	if (dpyb2.get_display() != NULL)
		dpyb = dpyb2;
}
	
RayManta::RayManta(RayMantaBase& rmb, DisplayBase<Display **>& dpyb2) : Xmanager(), WindowManager() , RayMantaBaseVisit() 
  //default :O display
{
	if (dpyb2.get_display() != NULL)
		dpyb = dpyb2;
		
  //::xmantaray= *this;
  pressed = False;
  motion = False;
  dx= dy = 0;
  window = (RayMantaWindow *) 0;
  unsigned long gc_mask = 0;
  gc_mask = GCForeground|GCBackground|GCGraphicsExposures|GCLineWidth;
  Pixel back_pix, fore_pix;
//  back_pix = GetColor(*(dpyb.get_display()),(char *)"blue");
//  fore_pix = GetColor(*(dpyb.get_display()),(char *)"lightblue");
/*
  XGCValues values;
  values.foreground = fore_pix;
  values.background = back_pix;
  values.graphics_exposures = True;
  //values.function = GXcopy|GXand;
  values.line_width = 3;
  GC gc = XCreateGC(*(dpyb.get_display()), getRootWindow(), gc_mask, &values);
*/
  //XSetFillStyle(*(dpyb.get_display()), gc, FillSolid);
//  XSetClipOrigin(*(dpyb.get_display()), gc, 0, 0);
//  XSetClipMask(*(dpyb.get_display()), gc, None);
  
  //  setBackground();
  //foregroundWindows();
  printf("made XMantaRay Server\n");
}

RayManta::~RayManta() {}

void RayManta::initwindow(RayMantaWindow *w) 
{
  	fontset = createFontSet(dpyb);
	window = w;	
}

void RayManta::eventloop(RayMantaBase& rmb, XEvent *e) 
{
  #define NIL (0)
  int events;
  GC gc;
  gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
  const char * test = "XMantaRay - 3D framework";
  XmbDrawString(*(dpyb.get_display()), window->getTitleWindow(), fontset, gc, 20, 10, test, strlen(test));
  draw(*this);
  
  for (int i = 0; i < 1000; i++) {//calibrator
    if (events = XPending(*(dpyb.get_display()))) { 
      //XEvent e;
      XNextEvent(*(dpyb.get_display()), e);
      printf("got event %d from number of events = %d\n", e->type, events);
	process_event(e);
	XFillRectangle(*(dpyb.get_display()), window->getTitleWindow(), gc,0,0,800,20);
	XFillRectangle(*(dpyb.get_display()), window->getWindow(), gc,0,0,800,600);
    	//XSync(*dpy, 0);
	}
	
  }
	XFlush(*(dpyb.get_display()));
}

int RayManta::process_event(XEvent *e) 
{

    printf("process eventtype= %d\n", e->type);
  switch (e->type) {
  case MapRequest:{
    printf("maprequest processed: %d windows\n", (int)windows.size());
    XMapWindow(e->xany.display, window->getTitleWindow()); 
    XMapWindow(e->xany.display,window->getWindow()); 
    break;
  }
/*  case UnmapNotify:{
    printf("unmapnotify");
    RayMantaWindow *win = (RayMantaWindow *) 0;
    if ((win = search_window(e->xunmap.window, True)))
      {
	if (window_type == CLIENT || window_type == TITLE)
	  {
	    erase_window(win); //because mapNotify reinserts the window =>
	    //It seems to me that unmapped windows don't get many events 
	    win->unmap(dpy);
	    printf("unmap succeeded.\n");
	  }
      }
    break;
  }*/
  case MotionNotify:{
    if (pressed)
      {
	XMotionEvent xm = e->xmotion;
	if (!motion)
	  {
	    x = xm.x; 
	    y = xm.y;
	    printf("x,y=%d, %d\n",xm.x,xm.y);
	  }
	dx = xm.x_root;
	dy = xm.y_root;
	window->move(&(e->xany.display), dx, dy);
	//printf("x,y= %d, %d\n", xm.x,xm.y);
	//do some rectanglodroiding here if not opaque move
	//FIXMEif (window_type == TITLE)
	  {
	    window->move(&(e->xany.display), dx-x, dy-y);
	    //XMoveWindow(*dpy, window->getWindow(), dx-x, dy-y);moved to move()
	    //XDrawRectangle(e->xany.display, root_window, gc, dx-x, dy-y, window->getWidth(), window->getHeight());//doesnt get erased yet
	  }
	motion = True;
      }
    printf("motion\n");
    break;
  }
  case ButtonPress:{
    RayMantaWindow *win = window;//(RayMantaWindow *) 0;
    //test if titlebar of a window got pressed
    //printf("e->window %d\n", (e->xbutton.window == None));
    //if (win = search_window(e->xbutton.window, True)) 
      //searches for the titlewindow
	XButtonEvent xb = e->xbutton;
    if (xb.y < 20) 
      {
	//if (window_type == CLIENT || window_type == TITLE)
	// {
	XRaiseWindow(e->xany.display, win->getWindow());
	XRaiseWindow(e->xany.display, win->getTitleWindow());
	pressed = True;
	//window = win;
	//}
//FIXME	if(window_type == LOWERBORDER)
	  {
	    init_x_root = xb.x_root;
	    init_y_root = xb.y_root;
	  }
      }
    printf("buttonpress\n");
    break;
  }
  case ButtonRelease:{
    if (pressed) {
      
    printf("type = %d\n", window_type);
      pressed = False;
      if (motion) {
	motion = False;
	//XRaiseWindow(dpy, window->getWindow());
	  window->move(dpyb.get_display(), dx-x, dy-y);
	/*switch (window_type){
	//case TITLE:{
	  window->move(dpy, dx-x, dy-y);
	  //XMoveWindow(dpy, window->getWindow(), dx-x, dy-y);
	  //break;
	}
	case LOWERBORDER:{
	  window->resize(init_x_root-dx, init_y_root-dy);
	  //XResizeWindow(dpy, window->getWindow(), 
	  //init_x_root,init_y_root);
	  break;
	}
	default:
	  break;
	}
      }
      else if (window_type == DESTROY)
	{
	  printf("destroying window now..\n");
	  erase_window(window);
	  XDestroySubwindows(display, window->getWindow());
	  XDestroyWindow(display, window->getWindow());
	}
    */} 
    }
    printf("buttonrelease\n");
    break;
  }
/*  case EnterNotify:{
    break;
  }    
  case LeaveNotify:
  case Expose:{//Very dangerous if a resize op gets interrupted by a expose
    RayMantaWindow *win = window;//(RayMantaWindow *) 0;
    //if(win = search_window(e->xexpose.window, False))  //False !!!!
      {
	//if (window_type == TITLE) //!!!!
	//{
	    win->expose(e->xexpose);
	    //positionWindow(win); happens in PxieWindow
	    //}
      }
    
    
    printf("expose\n");
    break;
  }
  case ConfigureRequest:{
    RayMantaWindow *win = (RayMantaWindow *) 0;
    if (win = search_window(e->xconfigurerequest.window, True))
      {
	//resize the parent & window !
	win->configure(dpy, e->xconfigurerequest);
	printf("existing window configure request\n");
      }
    else 
      {
	//XGrabServer(display); to grab or not to grab that's the question
	XConfigureRequestEvent xcre = e->xconfigurerequest;
	XWindowChanges xwc;
	xwc.x = xcre.x;
	xwc.y = xcre.y;
	xwc.width = xcre.width;
	xwc.height = xcre.height;
	xwc.border_width = xcre.border_width;
	xwc.sibling = xcre.above;
	xwc.stack_mode = xcre.detail;
	XConfigureWindow(e->xany.display, xcre.window, xcre.value_mask, &xwc);
	//XUngrabServer(e->xany.display);
	printf("Configure\n");
      }
    break;
  }
 *//* case DestroyNotify:{
    RayMantaWindow *win = (RayMantaWindow *) 0;
    if (win = search_window(e->xdestroywindow.window, True))
      {
	if(window_type == CLIENT || window_type == TITLE)
	  {
	    printf("Found window to destroy in list\n");
	    //erase_window(win);
	    win->destroy(dpy);
	    //erase_window(win); //maybe this should happen later
	  }
      }
    printf("destroyed\n");
    break;
  }*/
  default:
    break;
  }
  return 1;
}
/*
void RayManta::insert_window (RayMantaWindow *win)
{
  //--tullaris windows.insert_after(windows.previous(windows.end()), win);
  windows.push_back(win);//insert(windows.previous(windows.end()), win);
  printf("Window managed.\n");
}

RayMantaWindow * RayManta::search_window(Window win, bool set_window_type)
{
  //remove the set_window_type flag, which is a bad hack !
  std::list<RayMantaWindow *>::iterator first = windows.begin();
  std::list<RayMantaWindow *>::iterator last = windows.end();
  while (first != last)
    {
      printf("testing\n");
      std::list<RayMantaWindow *>::iterator next = first;
      ++next;
      if (((*first)->getTitleWindow() == win)) //add getWindow() for button destroys !
	//maybe split up the tests
	{
	  //break;
	  if(set_window_type)
	    {window_type = TITLE;}
	  printf("Found titlewindow in list\n");
	  return *first;
	}
      if (((*first)->getClientWindow() == win))
	{
	  if (set_window_type)
	    {
	      window_type = CLIENT;
	    }
	  printf("Found ClientWindow in list\n");
	  return *first;
	}
      if (((*first)->getLowerborderWindow() == win))
	{
	  if (set_window_type)
	    {
	      window_type = LOWERBORDER;
	    }
	  printf("Found lowerborderwindow in list\n");
	  return *first;
	}
      if (((*first)->getWindow() == win))
	{
	  if (set_window_type)
	    {
	      window_type = TOPLEVEL;
	    }
	  printf("Found lowerborderwindow in list\n");
	  return *first;
	}
 */     /*if (((*first)->getDestroyWindow() == win))
	{
	  //if (set_window_type)
	  // {
	      window_type = DESTROY;
	      //}
	  printf("Found destroywindow in list\n");
	  return *first;
	}
	*/
   /*   first= next;
    }
  printf("Window not found in list\n");
  return NULL;
  *//*
  for (;;) //do .. hwile
    {
      if (window_iterator.getTitleWindow() == window)
	{
	  break;
	  return window_iterator;
	}
      if (window_iterator == windows.end())
	{ 
	  return NULL; 
	  break;
	}
	}
  */
/*}

void RayManta::erase_window(RayMantaWindow * win)
{
  std::list<RayMantaWindow *>::iterator first = windows.begin();
  std::list<RayMantaWindow *>::iterator last = windows.end();
  while (first != last)
    {
      printf("testing\n");
      std::list<RayMantaWindow *>::iterator next = first;
      ++next;
      if ((*first) == win)
	//maybe split up the tests
	{
	  printf("Found window to be erased in list\n");
	  windows.erase(first);
	  return;
	}
      first= next;
    }
  printf("Window not found in list\n");
  return;
}
*/
void RayManta::positionWindow(Display **dpy, RayMantaWindow *win)
{
  //1. get free rects 
  //2. position in the smallest free rect that's big enough
  if (!windows.empty())
    {
      
      struct rect *free_rects[512]; //calculate size here instaed of 512
      //free_recxts sould be redundant if you check immediatly if the win fits
      //otherwise you position it in the smallest free rect that's big enough
      struct rect *window_rects[windows.size()]; //was struct rect* but bugged could be that sorting doesnt work right
      
      int display_width = DisplayWidth(*(dpyb.get_display()),screen);
      int display_height = DisplayHeight(*(dpyb.get_display()), screen);
      int win_x = win->getx();
      int win_y = win->gety();
      int win_width = win->getWidth();
      int win_height = win->getHeight();
      
      std::list<RayMantaWindow *>::iterator first = windows.begin();
      std::list<RayMantaWindow *>::iterator last = windows.end();
      for (int i = 0; first != last; i++)
	{
	  std::list<RayMantaWindow *>::iterator next = first;
	  ++next;
	  window_rects[i] = (struct rect *) malloc(sizeof(struct rect));
	  window_rects[i]->x = (*first)->getx();
	  window_rects[i]->y = (*first)->gety();
	  window_rects[i]->w = (*first)->getWidth();
	  window_rects[i]->h = (*first)->getHeight();
	  window_rects[i]->x_right = window_rects[i]->x + window_rects[i]->w;
	  window_rects[i]->y_right = window_rects[i]->y + window_rects[i]->h;
	  window_rects[i]->surface = (*first)->getWidth()*(*first)->getHeight();
	  first= next;
	  printf("x=%d of %p  ",(int)window_rects[i]->x, &(window_rects[i]->x));
	}
      //sort the windows so that they appear from left to right
      qsort(&window_rects, windows.size(), sizeof(struct rect *), &compare_x);//maybe need also a y sort
      
      //get free rects ..      
      printf("\nsorted:");
      int j = 0;      
      free_rects[j] = (struct rect *) malloc(sizeof(struct rect));
      for(int k = 0; k < windows.size(); k++)
	{
	  printf("x=%d ",window_rects[k]->x);
	  //..left of the window
	  if (window_rects[k]->x != 0)
	    {
	      for (int l = 0; l < k; l++)
		{
		  if ( k == 0) //leftmost window
		    {
		      free_rects[j]->x = 0;
		      free_rects[j]->y = 0;
		      free_rects[j]->w = window_rects[k]->x;
		      free_rects[j]->h = display_height;
		      free_rects[j]->x_right = window_rects[k]->x;
		      free_rects[j]->y_right = display_height;
		      j +=1;
		      free_rects[j] = (struct rect *) malloc(sizeof(struct rect));
		     
		    }
		  /*
		  else if (overlap()) 
		    {
		    ..
		      continue;
		    }
		  */
		  else  // not overlapping
		    {
		      int rightmost_x = 0;
		      //doesnt' take into account yet: windows who have their m->y_right between k->y k->y_right which would create 2 free rects
		      for (int m = 0; m < k; m++) //what about <= ?
			{//check if there's a window to the left
			  if (window_rects[m]->x_right > rightmost_x  && 
			      window_rects[m]->x_right < window_rects[k]->x &&
			      window_rects[m]->y_right > window_rects[k]->y)
			    {rightmost_x = window_rects[m]->x_right; }
			}
		      free_rects[j]->x = rightmost_x; 
		      free_rects[j]->w = window_rects[k]->x - rightmost_x;
		      free_rects[j]->x_right = free_rects[j]->x + free_rects[j]->w;
		      int lowest_y = 0;
		      for (int m = 0; m < k; m++)
			{//check if there is any window in between above
			  if (window_rects[m]->x_right > rightmost_x &&
			      window_rects[m]->y_right < window_rects[k]->y)
			    {
			      lowest_y = window_rects[m]->y_right;
			    }
			}
		      free_rects[j]->y = lowest_y;
		      int height = display_height;
		      for (int m = 0; m < k; m++)
			{//check if there is any window in between below 
			  if (window_rects[m]->x_right > rightmost_x &&
			      window_rects[m]->y > window_rects[k]->y_right &&
			      window_rects[m]->y < height)
			    {
			      height = window_rects[m]->y;
			    }
			}
		      free_rects[j]->h = height;
		      free_rects[j]->y_right = free_rects[j]->y + free_rects[j]->h;
		    }
		  
		  }
	    }
	  //..above the window 
	  //..under the window
	  //..right of the window
	}
      // insert win in the first (make it smallest) free rectangle
      for (int m = 0; m <= j; m++)
	{
	  printf("h = %d w = %d ", free_rects[m]->h, free_rects[m]->w);
	  if (free_rects[m]->h >= win_height && free_rects[m]->w >= win_width)
	    {
	      win->move(dpyb.get_display(), free_rects[m]->x, free_rects[m]->y);
	      return;
	    }
	}
      
    }
}
/*
  void RayManta::setBackground()
  {
  ImlibData *id;
  ImlibImage *im;
  Pixmap p,m;
  int w,h;
  id = Imlib_init(dpyb.get_display());
  im = Imlib_load_image(id, BACKGROUNDIMAGE);
  w = im->rgb_width; 
  h = im->rgb_height;
  Imlib_render(id, im, w, h);
  p = Imlib_move_image(id, im);
  m = Imlib_move_mask(id, im);
  XSetWindowBackgroundPixmap(dpyb.get_display(), getRootWindow(), p);
  if (m)
    {XShapeCombineMask(display, root_window, ShapeBounding, 0,0,m,ShapeSet);}
  XClearWindow(display, root_window);
  }
*/
/*
  void RayManta::foregroundWindows()
  {

  ImlibData *id;
  ImlibImage *im;
  Pixmap p,m;
  int w,h;
  id = Imlib_init(dpyb.get_display());
  im = Imlib_load_image(id, FOREGROUNDIMAGE);
  w = im->rgb_width; 
  h = im->rgb_height;
  Imlib_render(id, im, w, h);
  p = Imlib_move_image(id, im);
  m = Imlib_move_mask(id, im);
  XSetWindowAttributes attrib_create;
  unsigned long create_mask = CWBorderPixel | CWBackPixmap|
    CWEventMask|CWColormap;
  attrib_create.colormap = DefaultColormap(display, screen);
  attrib_create.background_pixmap = None;
  attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
    ButtonMotionMask |ExposureMask|EnterWindowMask | LeaveWindowMask;

  Window win = XCreateWindow(*(dpyb.get_display()), root_window, 
			     0, 
			     DisplayHeight(display,screen)-70, 
			     DisplayWidth(display,screen), 70, 0,
			     getDepth(), InputOutput, getVisual(),
			     create_mask, &attrib_create);
  
  XSetWindowBackgroundPixmap(*(dpyb.get_display()), win, p);
  XMapWindow(display, win);
  
  char * test = "Loading..";
  XmbDrawString(display, win, fontset, gc, 20, 20, test, strlen(test));

  Button *button = new Button (root_window, DisplayWidth(display,screen)-40,
			       DisplayHeight(display,screen)-40);
  button->setBackgroundPic("/usr/share/enlightenment/themes/ShinyMetal/pix/btn_exec_terminal_normal.png");

  //XDrawRectangle(display, win, gc, 2,2, 70,70);
  //XReparentWindow(*(dpyb.get_display()), win, root_window, 0, 0);
  //if (m)
  //  {XShapeCombineMask(display, root_window, ShapeBounding, 0,0,m,ShapeSet);}
  //XClearWindow(display, win);
  //XClearWindow(display, root_window);
}
*/

Pixel RayManta::GetColor(Display **dpy, char *name)
{
  XColor color;
  XWindowAttributes attributes;

  XGetWindowAttributes(*(dpyb.get_display()),getRootWindow(),&attributes);
  color.pixel = 0;
   if (!XParseColor (*(dpyb.get_display()), attributes.colormap, name, &color)) 
     {
       printf("parse no color");
     }
   else if(!XAllocColor (*(dpyb.get_display()), attributes.colormap, &color)) 
     {
       printf("parse no color");
     }
  return color.pixel;
}

int compare_x(const void * a, const void * b)
{
  printf("compare_x a.x %d ",*((int *)((struct rect *)a)->x));
  
  if (*((int *)((struct rect *)a)->x) < *((int *)((struct rect *)b)->x))
    {return -1;}
  else if (*((int *)((struct rect *)a)->x) > *((int *)((struct rect *)b)->x))
    {return 1;}
  else
    {return 0;}
  
}

