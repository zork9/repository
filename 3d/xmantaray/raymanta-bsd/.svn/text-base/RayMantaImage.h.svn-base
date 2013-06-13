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
#ifndef RAYIMAGE_H
#define RAYIMAGE_H

#include<X11/Xlib.h>
#include<X11/xpm.h>
#include<string>

#include "RayMantaImageBase.h"

class RayMantaImage : public RayMantaImageBase 
{
 public:
  RayMantaImage(Display **dpy);
  int init() { /*XInitImage(image);*/ return 0;}
  virtual ~RayMantaImage() {}

  virtual int draw(Display **dpy, Window *w, int xx, int yy);
  virtual int putpixel(int xx, int yy, unsigned long value);

protected:
  XImage *shape;


}; //class RayMantaPixmapImage

#endif
