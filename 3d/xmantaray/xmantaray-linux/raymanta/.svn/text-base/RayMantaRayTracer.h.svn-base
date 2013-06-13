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
#ifndef RAYMANTARYTR_H
#define RAYMANTARAYTR_H
// libc 
#include <stdio.h>
#include <stdlib.h>
// X
#include <X11/Xlib.h>
//#include <Imlib.h>
//local
#include "RayManta.h"
#include "RayManta.rc"

class RayMantaRayTracer : public RayManta 
{
 private:
 public:
  RayMantaRayTracer(RayMantaBase& rmb,DisplayBase<Display **>& dpyb2) : RayManta(rmb,dpyb2) {}
 // RayMantaRayTracer(Display **dpy, RayMantaWindow *rayw) : RayManta(dpy) { init(rayw); }
  virtual ~RayMantaRayTracer() {};
  virtual int draw(RayMantaBase const& rmb);
  virtual int draw2(Display **dpy, int const& k);
  virtual void eventloop(RayMantaBase& rmb, XEvent *e); 
}; // class RayManta 

#endif
