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
#ifndef _RAYMODEL_H_
#define _RAYMODEL_H_
#include<string>
#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaEngine.h"

namespace ray3d {
// Model mixin class
//S = string class
//F = modelreader class
class Model {
public:
	#define NIL (0)
	Model (Display **dpy1, Window *w1, GC *gc1) { if (gc1 == NULL) gc = XCreateGC(*dpy1, *w, 0, NIL); else gc = *gc1; dpy = dpy1; w = w1;}
	virtual ~Model() {}

	virtual int filein(std::string const& filename);
	virtual int fileout(std::string const& filename);

	int rotatex(Engine const& engine, double t);
	int rotatey(Engine const& engine, double t);
	int rotatez(Engine const& engine, double t);
	int rotate(Engine const& engine, double t1, double t2, double t3);

	virtual int draw(Display **dpy, Window *w);
	virtual Display **get_dpy() { return dpy; }
	virtual Display **get_display() { return dpy; }
	virtual std::vector<Point> get_points() { return _points; }
	virtual Window *get_window() { return w; }
	virtual void addpoint(Point const& p) { _points.push_back(p); }
	virtual void empty_points() { _points = std::vector<Point>(1); }
	virtual void set_points(std::vector<Point> v) { _points = v; }
protected:
	std::vector<Point> _points;
	GC gc;
	Display **dpy;
	Window *w;
};

}

#endif
