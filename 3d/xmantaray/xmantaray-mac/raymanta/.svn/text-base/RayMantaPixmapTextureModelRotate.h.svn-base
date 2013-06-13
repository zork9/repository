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
#ifndef _RAYPIXMAPTEXTUREMODELROT_H_
#define _RAYPIXMAPTEXTUREMODELROT_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaEngine.h"
#include "RayMantaPixmapTextureModel.h"
#include "RayMantaPixmapTexture.h"
#include "RayMantaTexture.h"

namespace ray3d {
class PixmapTextureModelRotate : public PixmapTextureModel {
public:
	PixmapTextureModelRotate (Display **dpy, Window *w, GC *gc1, std::string const& filename,int ww, int hh) : PixmapTextureModel(dpy,w,gc1,filename,ww,hh) { _pixmaptexture.initdraw(*this); }
	virtual ~PixmapTextureModelRotate() {}

	virtual int draw(Display **dpy, Window *w, int offsetx, int offsety);

};

}

#endif
