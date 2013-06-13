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
#ifndef _RAYPIXMAPTEXTUREMODEL_H_
#define _RAYPIXMAPTEXTUREMODEL_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaEngine.h"
#include "RayMantaTextureModel.h"
#include "RayMantaPixmapTexture.h"
#include "RayMantaTexture.h"

namespace ray3d {
class PixmapTextureModel : public TextureModel {
public:
	PixmapTextureModel (Display **dpy, Window *w, GC *gc1, std::string const& filename,int ww, int hh) : TextureModel(dpy,w,gc1), _pixmaptexture(dpy, filename,1,1,1,ww,hh) {}
	virtual ~PixmapTextureModel() {}

	virtual int draw(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int draw2(Display **dpy, Window *w);

protected:
	PixmapTexture _pixmaptexture;
	
};

}

#endif
