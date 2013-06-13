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
#ifndef _RAYTEXTUREMODEL_H_
#define _RAYTEXTUREMODEL_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaEngine.h"
#include "RayMantaPolygonModel.h"

namespace ray3d {

class TextureModel : public PolygonModel {
public:
	TextureModel (Display **dpy, Window *w, GC *gc1) : PolygonModel(dpy,w,gc1) {}
	virtual ~TextureModel() {}

	virtual int draw(Display **dpy, Window *w);

};

}

#endif
