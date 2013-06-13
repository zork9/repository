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
#ifndef _RAYSPHEREMODEL_H_
#define _RAYSPHEREMODEL_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaEngine.h"
#include "RayMantaModel.h"

namespace ray3d {

//S = string class
//F = modelreader class
class SphereModel : public Model {
public:
	SphereModel (Display **dpy, Window *w, GC *gc1) : Model(dpy,w,gc1) {}
	virtual ~SphereModel() {}

	int generatesphere(Display **dpy, Window *w);
	virtual int raycast(Display **dpy, Window *w);
	virtual int raytrace(Display **dpy, Window *w, Point const& p);
	virtual int raytrace2(Display **dpy, Window *w, Point const& p);
	virtual int dithersunray(Display **dpy, Window *w);
	virtual int drawsunray(Display **dpy, Window *w);

	virtual int draw(Display **dpy, Window *w);

protected: 
	//NOTE : The base class contains identical _points vector
	// Thisi e.g. is for circumference and Volume 
	std::vector<Point> _spherepoints;
};

}

#endif
