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
#include "RayMantaTexture.h"
#include "RayMantaPolygon.h"
#include<cstdlib>

namespace ray3d {	

int Texture::draw(Display **dpy, Window *w)
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
	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

	const std::string filename("./post.xpm");
	//NOTE: do not draw polygon lines, rather texture in between 
	//NOTE: polygons are fixed at 4 points
	ray3d::Polygon poly;
	poly += ray3d::Point(200,200,200);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(20,20,20);
	poly += ray3d::Point(2,2,2);
	_polygons.push_back(poly);
	for (PolygonVector::iterator vi = _polygons.begin(); vi != _polygons.end(); vi++ ) {
			for (int i = 1; i < 5; i++) {
				Point p1((*vi)[i-1]);
				Point p2((*vi)[i]);
			
				Point p3(p1.scalex(_alpha));	
				unsigned long color = _xpmimage.getpixel(p3.get_x(), p3.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				XDrawLine(*dpy, *w, gc, p3.get_x(),p3.get_y(),p2.get_x(),p2.get_y());
			}
		}
*/		
	return 0;
}



} // namespace ray3d

