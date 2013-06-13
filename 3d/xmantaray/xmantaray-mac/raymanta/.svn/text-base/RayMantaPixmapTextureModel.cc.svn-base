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
#include "RayMantaPixmapTextureModel.h"
#include<cstdlib>
#include<iostream>

namespace ray3d {	
int PixmapTextureModel::draw(Display **dpy, Window *w, int offsetx, int offsety)
{
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/
	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);

	//if (_points.empty())
	//NOTE init points
	_pixmaptexture.rotatemodel(*this);

	for (std::vector<Point>::iterator vi = _points.begin(); vi != _points.end(); vi++) {
		values.foreground = (*vi).get_color();
        	gc = XCreateGC(*dpy, *w, valuemask, &values);
		
		XDrawLine(*dpy,*w,gc,(*vi).get_x()+offsetx,(*vi).get_y()+offsety,(*vi).get_x()+offsetx,(*vi).get_y()+offsety);
	}
	return 0;
}

int PixmapTextureModel::draw2(Display **dpy, Window *w)
{
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
/*	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

	const std::string filename("./post.xpm");
	//NOTE: do not draw polygon lines, rather texture in between 
	//NOTE: polygons are fixed at 4 points
	ray3d::Polygon poly;
	poly += ray3d::Point(20,20,20);
	poly += ray3d::Point(102,102,102);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(20,20,20);
	_polygons.push_back(poly);
	//for (PolygonVector::iterator vi = _polygons.begin(); vi != _polygons.end(); vi++ ) {
			//for (int i = 0; i < 4; i++) {
			for (int xx = 0; xx < _pixmaptexture.get_w(); xx++) { 
			for (int yy = 0; yy < _pixmaptexture.get_h(); yy++) {
				//Point p1((*vi)[i-1]);
				//Point p2((*vi)[i]);
				Point p1(_polygons[0][0].get_x(),_polygons[0][0].get_y(),1);
				Point p2(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				//pt = pt.scaley(angle);//_pixmaptexture.get_alpha());
				_alpha -= 0.001;
				Point pt(xx*(angle),yy*(angle),1);
				//unsigned long color = 65000;//_pixmaptexture.get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				unsigned long color = _pixmaptexture.get_xpmimage().getpixel((int)pt.get_x()%24, (int)pt.get_y()%24);
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				/////XDrawLine(*dpy, *w, gc, p1.get_x()+(int)pt.get_x(),p1.get_y()+(int)pt.get_y(),p1.get_x()+(int)pt.get_x(),p1.get_y()+(int)pt.get_y());
				XDrawLine(*dpy, *w, gc,20+(int)pt.get_x(),20+(int)pt.get_y(),20+(int)pt.get_x(),20+(int)pt.get_y());
			}
			}
			//}
//		}
*/		
	return 0;
}



} // namespace ray3d

