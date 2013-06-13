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
#include "RayMantaTextureModel.h"
#include<cstdlib>

namespace ray3d {	

int TextureModel::draw(Display **dpy, Window *w)
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

	//NOTE: do not draw polygon lines, rather texture in between 
	for (std::vector<Point>::iterator vi = _points.begin(); vi != _points.end(); vi++ ) {
		XDrawLine(*dpy, *w, gc, (*vi).get_x(),(*vi).get_y(),(*vi).get_x(),(*vi).get_y());

	}
	return 0;
}



} // namespace ray3d

