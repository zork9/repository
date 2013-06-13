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
#include "RayMantaImage.h"
#include "RayManta.h"

RayMantaImage::RayMantaImage (Display **dpy) 
{
//	init();
  
	int depth = DefaultDepth(*dpy, DefaultScreen(*dpy));
  	Visual *visual = DefaultVisual(*dpy, DefaultScreen(*dpy));
//	image = XCreateImage(*dpy, visual, depth, XYPixmap,0,(char *)post_xpm,24,24,8,1); 
}

int RayMantaImage::draw(Display **dpy, Window *w, int destxx, int destyy)
{
#define NIL (0)
  GC gc = XCreateGC(*dpy, *w, 0, NIL);
  XPutImage(*dpy, *w, gc, image, 0,0,destxx,destyy,500,500);

	return 0;
}

int RayMantaImage::putpixel(int xx, int yy, unsigned long value)
{
	XPutPixel(image, xx,yy,value);

}


