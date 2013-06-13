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

#include "RayMantaRayTracer.h"
#include "Xmanager.h"
#include "RayMantaWindow.h"
#include "RayMantaEngine.h"
#include "RayMantaMatrix3.h"
#include "RayMantaSphereModel.h"

static double theta1 = 1.5;
static double theta12 = 2.5;
static double theta13 = 3.5;
int RayMantaRayTracer::draw(RayMantaBase const& rmb)
{
	Window w = window->getWindow(); 
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
	//3D rotation code
        ray3d::SphereModel sm(dpyb.get_display(),&w,&gc);

	sm.generatesphere(dpyb.get_display(), &w);
	sm.draw(dpyb.get_display(),&w);
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
        //XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,0,0,100,100);
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)v1.get_x(),(int)v1.get_y(),(int)v2.get_x(),(int)v2.get_y());
*/
	return 0;
}


int RayMantaRayTracer::draw2(Display **dpy, int const& k)
{
	Window w = window->getWindow(); 
        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
	//3D rotation code
        ray3d::SphereModel sm(dpy,&w,&gc);

	sm.generatesphere(dpy, &w);
//	sm.draw(dpy,&w);
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

void RayMantaRayTracer::eventloop(RayMantaBase& rmb, XEvent *e) 
{
  #define NIL (0)
  int events;
  GC gc;
  gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
  const char * test = "XMantaRay - raytracer";
  XmbDrawString(*(dpyb.get_display()), window->getTitleWindow(), fontset, gc, 20, 10, test, strlen(test));
	//if (RayMantaRayTracer* rm = dynamic_cast<RayMantaRayTracer*>(&rmb)) {
  	draw(*this);
	//} else if (RayManta* rm = dynamic_cast<RayManta*>(&rmb)) {
  	//	rm->draw(*this);
	//}
  
  for (int i = 0; i < 1000; i++) {//calibrator
    if (events = XPending(*(dpyb.get_display()))) { 
      //XEvent e;
      XNextEvent(*(dpyb.get_display()), e);
      printf("got event %d from number of events = %d\n", e->type, events);
	process_event(e);
    	//XSync(*dpy, 0);
	}
	
  }
	XFlush(*(dpyb.get_display()));
}

