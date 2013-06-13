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
#ifndef _RAYPOLYGONMODEL_H_
#define _RAYPOLYGONMODEL_H_

#include<X11/Xlib.h>
#include<vector>
#include<string>
#include "RayMantaPoint.h"
#include "RayMantaModel.h"
#include "RayMantaPolygon.h"

namespace ray3d {
// Model mixin class
typedef std::vector<Polygon> PolygonVector;
typedef std::vector<Point> PointVector;
class PolygonModel : public Model {
public:
	PolygonModel (Display **dpy, Window *w, GC *gc1) : Model(dpy,w,gc1) {}
	virtual ~PolygonModel() {}

	virtual int draw(Display **dpy, Window *w);
	virtual int raytrace(Display **dpy, Window *w);
	virtual int dithersunray(Display **dpy, Window *w);
	virtual void add(Polygon const& p) { _polygons.push_back(p); }

	virtual int filein(std::string const& filename);
	virtual int fileout(std::string const& filename);

protected:
	//NOTE: there is a _points vector in the base class
	PolygonVector _polygons;
public:
	Polygon operator+(Polygon p) { _polygons.push_back(p); return p; }
	PolygonModel operator+=(Polygon p) { _polygons.push_back(p); return *this; }
};

}

#endif
