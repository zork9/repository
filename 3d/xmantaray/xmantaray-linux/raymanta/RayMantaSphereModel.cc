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

#include<fstream>
#include "RayMantaSphereModel.h"
#include<cstdlib>

namespace ray3d {	

int SphereModel::draw(Display **dpy, Window *w)
{
	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

	for (std::vector<Point>::iterator vi = _spherepoints.begin(); vi != _spherepoints.end(); vi++ ) {
		XDrawLine(*dpy, *w, gc, (*vi).get_x(),(*vi).get_y(),(*vi).get_x(),(*vi).get_y());

	}
	return 0;
}


int SphereModel::generatesphere(Display **dpy, Window *w)
{
#define NIL (0)
   GC gc = XCreateGC(*dpy, *w, 0, NIL);

  // sphere init
  double r = 100;
  Point center(100,100,100);
  int xx,yy,zz;
  //draw sphere
  for (zz = -1; zz< 1; zz++) {
  for (xx = -100; xx < 100; xx++) {
  for (yy = -100; yy < 100; yy++) {
	Point p(xx,yy,zz);
	if (xx*xx  + yy*yy + zz*zz <= r*r) {
		int txx = xx + center.get_x();
		int tyy = yy + center.get_y();
		int tzz = zz + center.get_z();
  		XDrawLine(*dpy, *w, gc, txx,tyy,txx,tyy);
		_spherepoints.push_back(p);
	}
  }
  }
  }

  //draw sphere
/*
  for (zz = -1; zz< 1; zz++) {
  for (xx = -100; xx < 100; xx++) {
  for (yy = -100; yy < 100; yy++) {
      	GC gc = XCreateGC(dpy, w, 0, NIL);
	Point p(xx,yy,zz);
	if (xx*xx  + yy*yy + zz*zz <= r*r) {
		int txx = xx + center.get_x();
		int tyy = yy + center.get_y();
		int tzz = zz + center.get_z();
  		XDrawLine(dpy, w, gc, txx,tyy,txx,tyy);
	}
  }
  }
  }
*/
}

int SphereModel::raycast(Display **dpy, Window *w)
{

  #define NIL (0)

  std::vector<Point> spherepoints;
  double r = 100;
  Point center(100,100,100);
  int xx, yy, zz;

  for (zz = -100; zz< 200; zz++) {
  for (xx = -100; xx < 800; xx++) {
  for (yy = -100; yy < 600; yy++) {

 	//Point s(xx*10,yy*10,zz*10);
  	Point s(xx,yy,zz);
  	Point v = s - center; 
  	Point d(1,1,0);
  	//double t = (2*v*d + std::sqrt(2*v*d-4(v*v-r*r))/2 
  	double discr = (v*d)*(v*d) - (v*v - r*r);
  	double t1 = - (v*d) - std::sqrt((v*d)*(v*d) - (v*v - r*r));
  	double t2 = - (v*d) + std::sqrt((v*d)*(v*d) - (v*v - r*r));

	_spherepoints.push_back(Point(t1,t2,1));
	_spherepoints.push_back(Point(t2,t1,1));
	//FIXME luminosity with proximity between t1 and t2
//  	if (discr >= 0) 
	{
      		GC gc = XCreateGC(*dpy, *w, 0, NIL);
  		XDrawLine(*dpy, *w, gc, 0,0,t1,t2);//FIXME t1 0
  		XDrawLine(*dpy, *w, gc, 0,0,t2,t1);//FIXME t1 0
	}

  }	
  }
  }
}

int SphereModel::raytrace(Display **dpy, Window *w, Point const& p)
{

  #define NIL (0)

  generatesphere(dpy,w); 
	
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
	int k = 0;
  for (std::vector<Point>::iterator vi = _spherepoints.begin(); vi != _spherepoints.end(); vi++,k++ ) {
	//normalize
	values.foreground = (1400*k)%65665;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = (2048*k)%65665;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
	Point N(0,const_cast<Point&>(p).get_y(),0);
	Point L(p);
	
	double d = 0.1;

	N.normalize();
	L.normalize();

	Point NL(N-L);	
	double A = NL.dist(N);
	double B = NL.dist(L);
	//now sin(alpha) ~= alpha
	double alpha = 0;
	alpha = B*1/A; 

	double inner = N*L;
	int convolution = inner * std::cos(alpha);

	XDrawLine(*dpy,*w, gc,
			const_cast<Point&>(p).get_x(),
			const_cast<Point&>(p).get_y(),
			const_cast<Point&>(p).get_x(),
			const_cast<Point&>(p).get_y());
	//FIXME modify color
  }	
	
}

int SphereModel::raytrace2(Display **dpy, Window *w, Point const& p)
{

  generatesphere(dpy,w); 
	
}
int SphereModel::dithersunray(Display **dpy, Window *w)
{
  int xx,yy,zz;
  double r = 100;
  Point center(100,100,100);
  for (zz = 0; zz< 200; zz++) {
  for (xx = 0; xx < 200; xx++) {
  for (yy = 0; yy < 200; yy++) {
  	//Point s(xx*10,yy*10,zz*10);
  	Point s(xx,yy,zz);
  	Point v = s - center; 
  	Point d(1,1,0);
  	//double t = (2*v*d + std::sqrt(2*v*d-4(v*v-r*r))/2 
  	double discr = (v*d)*(v*d) - (v*v - r*r);
  	double t1 = - (v*d) - std::sqrt((v*d)*(v*d) - (v*v - r*r));
  	double t2 = - (v*d) + std::sqrt((v*d)*(v*d) - (v*v - r*r));

	_spherepoints.push_back(Point(t1,t2,1));
	_spherepoints.push_back(Point(t2,t1,1));
	//FIXME luminosity with proximity between t1 and t2
  	//if (discr >= 0) 
	{
      		GC gc = XCreateGC(*dpy, *w, 0, NIL);
  		XDrawLine(*dpy, *w, gc, 0,0,t1,t2);//FIXME t1 0
  		XDrawLine(*dpy, *w, gc, 0,0,t2,t1);//FIXME t1 0
	}
}}}
//sleep(10);
}

int SphereModel::drawsunray(Display **dpy, Window *w)
{
  for (int i = 0; i < _spherepoints.size(); i++) {
  	//GC gc = XCreateGC(dpy, w, gc_mask, &values);
  	//GC gc2 = XCreateGC(dpy, w, gc_mask2, &values2);
      	GC gc = XCreateGC(*dpy, *w, 0, NIL);

	double d = Point(0,0,0).dist(_spherepoints[i]);
	int x1 = _spherepoints[i].get_x();
	int y1 = _spherepoints[i].get_y();
	int x2 = _spherepoints[i].get_x();
	int y2 = _spherepoints[i].get_y();
//	if (d < 10)
	XDrawLine(*dpy,*w,gc, x1,y1,x2,y2);	
//	else
//	XDrawLine(*dpy,*w,gc, x1,y1,x2,y2);	
  }
	return 0; 
}

} // namespace ray3d

