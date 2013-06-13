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
#ifndef _RAY_POLYGON_H_
#define _RAY_POLYGON_H_
#include <vector>
#include "RayMantaPoint.h"
#include <X11/Xlib.h>

namespace ray3d {

typedef std::vector<Point> PolygonPoints;

class Polygon {
public:
	Polygon() : _points() {}
	Polygon(PolygonPoints const& v) : _points(v) {}
	virtual ~Polygon() {}

	virtual int draw(Display **dpy, Window *w);
	virtual void add(Point const& p) { _points.push_back(p); }
	virtual int size() { return _points.size(); }
protected:
	PolygonPoints _points;

	

public:
	Polygon operator+(Point const& p) { _points.push_back(p); return *this; }
	Polygon operator+=(Point const& p) { _points.push_back(p); return *this; }
	void operator-(Point const& p) { for (PolygonPoints::iterator vi = _points.begin(); vi != _points.end(); vi++) { if ((*vi) == p) { _points.erase(vi); break; }  } }
	Polygon operator=(Point const& p) { _points.push_back(p); return *this; }
	Point operator[](int index) { return _points[index]; }

};
}
#endif
