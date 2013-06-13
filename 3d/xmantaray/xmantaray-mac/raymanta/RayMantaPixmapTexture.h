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

	virtual int initdraw(PixmapTextureModel& model);
	virtual int rotatemodel(PixmapTextureModel& model);

	virtual int drawsmaller(Display **dpy, Window *w, int offsetx, int offsety, double a, double b);
	virtual int draw3(Display **dpy, Window *w);
	virtual int draw2(Display **dpy, Window *w);
	virtual int drawmain(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawcurved(Display **dpy, Window *w,int offsetx, int offsety);
	virtual int drawcurved2(Display **dpy, Window *w,int offsetx, int offsety);
	virtual int drawcurved3(Display **dpy, Window *w,int offsetx, int offsety);
	virtual int drawbig(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawbigger(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawbiggerandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	//virtual int drawbiggerandrotatemodel(PixmapTextureModel& model);
	virtual int drawenlargeandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawenlargeandrotate2(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawsmall(Display **dpy, Window *w, int offsetx, int offsety);
	virtual int drawsmallandrotate(Display **dpy, Window *w, int offsetx, int offsety);
	virtual RayMantaPixmapImage get_xpmimage() { return _xpmimage; }
	virtual int get_w() { return _w; }
	virtual int get_h() { return _h; }
protected:

	virtual int initdraw1(PixmapTextureModel& model);

	RayMantaPixmapImage _xpmimage;
	int _w,_h;	
	int _enlargew,_enlargeh;

	double thetax,thetay,thetaz;
};

}

#endif
