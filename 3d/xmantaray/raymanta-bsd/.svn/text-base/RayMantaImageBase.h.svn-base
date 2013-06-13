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
#ifndef RAYIMAGEBASE_H
#define RAYIMAGEBASE_H

#include<X11/Xlib.h>
#include<X11/xpm.h>
#include<string>
//interface
class RayMantaImageBase {
public:

  virtual int draw(Display **dpy, Window *w, int xx, int yy) = 0;
  virtual int putpixel(int xx, int yy, unsigned long value) = 0;

protected:
  XImage *image;


}; //class RayMantaImage

#endif
