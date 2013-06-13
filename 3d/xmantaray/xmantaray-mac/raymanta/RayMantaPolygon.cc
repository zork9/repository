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
#include "RayMantaPolygon.h"

namespace ray3d {

int Polygon::draw(Display **dpy, Window *w)
{
	#define NIL (0)
	std::vector<Point>::iterator pi = _points.begin();
      	GC gc = XCreateGC(*dpy, *w, 0, NIL);
	for (std::vector<Point>::iterator vi = _points.begin()++; vi != _points.end(); vi++ ) {
		XDrawLine(*dpy, *w, gc, (*vi).get_x(),(*vi).get_y(),(*pi).get_x(),(*pi).get_y());
		pi = vi;
	}
	return 0;
}

}
