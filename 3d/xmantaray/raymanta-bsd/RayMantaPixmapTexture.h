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
#ifndef _RAYPIXMAPTEXTURE_H_
#define _RAYPIXMAPTEXTURE_H_

#include<X11/Xlib.h>
#include<vector>
#include "RayMantaPoint.h"
#include "RayMantaPixmapImage.h"
#include "RayMantaEngine.h"
#include "RayMantaTexture.h"

namespace ray3d {

typedef std::vector<Texture> TextureVector;
class PixmapTextureModel;

class PixmapTexture : public Texture {
public:
	PixmapTexture (Display **dpy, std::string const& filename, double alpha, double beta, double gamma, int w, int h) : Texture(alpha,beta,gamma), _xpmimage(dpy, filename),_w(w),_h(h),_enlargew(w+w*h*alpha),_enlargeh(h+w*h*beta) {}
	virtual ~PixmapTexture() {}

	int initdraw(PixmapTextureModel& model);
	int rotatemodel(PixmapTextureModel& model);

	int drawsmaller(Display **dpy, Window *w, int offsetx, int offsety, double a, double b);
	int draw3(Display **dpy, Window *w);
	int draw2(Display **dpy, Window *w);
	int drawmain(Display **dpy, Window *w, int offsetx, int offsety);
	int drawcurved(Display **dpy, Window *w,int offsetx, int offsety);
	int drawcurved2(Display **dpy, Window *w,int offsetx, int offsety);
	int drawcurved3(Display **dpy, Window *w,int offsetx, int offsety);
	int drawbig(Display **dpy, Window *w, int offsetx, int offsety);
	int drawbigger(Display **dpy, Window *w, int offsetx, int offsety);
	int drawbiggerandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	//virtual int drawbiggerandrotatemodel(PixmapTextureModel& model);
	int drawenlargeandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	int drawenlargeandrotate2(Display **dpy, Window *w, int offsetx, int offsety);
	int drawsmall(Display **dpy, Window *w, int offsetx, int offsety);
	int drawsmallandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	RayMantaPixmapImage get_xpmimage() { return _xpmimage; }
	int get_w() { return _w; }
	int get_h() { return _h; }
protected:

	int initdraw1(PixmapTextureModel& model);

	RayMantaPixmapImage _xpmimage;
	int _w,_h;	
	int _enlargew,_enlargeh;

	double thetax,thetay,thetaz;
};

}

#endif
