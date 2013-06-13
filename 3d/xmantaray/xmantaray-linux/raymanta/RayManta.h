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
#ifndef RAYMANTA_H
#define RAYMANTA_H
// libc 
#include <stdio.h>
#include <stdlib.h>
// X
#include <X11/Xlib.h>
//#include <Imlib.h>
//local
#include "Xmanager.h"
#include "WindowManager.h"
#include "RayMantaWindow.h"
#include "RayMantaImage.h"
#include "RayManta.rc"
#include "RayMantaBaseVisit.h"


class RayManta : public Xmanager , public WindowManager, public RayMantaBaseVisit
{
 private:
  RayMantaImage *background;
  
  //  void setBackground();
  //void foregroundWindows();
  void insert_window(RayMantaWindow *);
  RayMantaWindow *search_window(Window, bool);
  void erase_window(RayMantaWindow * win);
  bool pressed, motion;
  int dx, dy ,x ,y, init_x_root, init_y_root;
  short int window_type; //type of window that got event
 public:
  RayManta(RayMantaBase& rmb, DisplayBase<Display **>& dpyb2);
  virtual ~RayManta();
  virtual void init(DisplayBase<Display **>& dpyb2);
  virtual void initwindow(RayMantaWindow *);
  virtual Pixel GetColor(Display **dpy, char *name);
  virtual void eventloop(RayMantaBase& rmb,XEvent *e);
  virtual int process_event(XEvent *);
  virtual void positionWindow(Display **dpy, RayMantaWindow *);
  virtual int drawdish(Display **dpy, int const& k);
  virtual int draw(RayMantaBase& rmb);
  virtual int draw2(Display **dpy, int const& k);
  virtual int draw3(Display **dpy, int const& k);
  virtual int drawsphere(Display **dpy, int const& k);

protected: 
  RayMantaWindow *window; //window which got last event
  /*static*/ DisplayBase<Display **> dpyb;
}; // class RayManta 

//DisplayBase<Display *> RayManta::dpyb = DisplayBase<Display *>();

struct rect {int x,y,x_right,y_right,w,h,surface;};
int compare_x(const void *, const void *);
#endif
