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
#ifndef _RAYSPIDERTEXTURE_H_
#define _RAYSPIDERTEXTURE_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaEngine.h"
#include "RayMantaPixmapTexture.h"

namespace ray3d {

class SpiderModel;

class SpiderTexture : public PixmapTexture {
public:
	SpiderTexture (Display **dpy, std::string const& filename, double alpha, double beta, double gamma, int w, int h) : PixmapTexture(dpy,filename,alpha,beta,gamma,w,h),_legw(80),_legh(60),_legz(10) {}
	virtual ~SpiderTexture() {}

	virtual int initdraw(SpiderModel& model);
	//diagonal spider leg (can be filed out)
	virtual int initspiderleg(SpiderModel& model);

	//clyndrical primitives and ditherings
	virtual int initclover(SpiderModel& model);
	//virtual int initconeorcylinderY(SpiderModel& model);
	virtual int initconeorcylindergrowY(SpiderModel& model);
	virtual int initconeorcylinderditherY(SpiderModel& model);
	virtual int initconeorcylinderdither2Y(SpiderModel& model);
	virtual int initconeorcylindersmallpatternY(SpiderModel& model);
	virtual int initconeorcylindersinkY(SpiderModel& model);
	virtual int initconeorcylindercurvedY(SpiderModel& model);
	virtual int rotatemodel(SpiderModel& model);

protected:

	virtual int initdraw1(SpiderModel& model);
	int _legw, _legh,_legz;
};

}

#endif
