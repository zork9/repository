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
#include "RayMantaProducerSystem.h"
#include <cstdlib>
#include <iostream>

Genes RayMantaProducerSystem::mutate(int index)
{
	genes[index] = ::rand();
	return genes;	
}
int RayMantaProducerSystem::draw(RayMantaBase const& rmb)
{
	Window w = window->getWindow(); 
//        GC gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);

	for (int i = 0; i < SCREENH; i++) {
	for (int j = 0; j < SCREENW; j++) {

	XGCValues values;
	unsigned long color = genes[j+i*SCREENW];
	values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*(dpyb.get_display()), w, valuemask, &values);
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)i,(int)j,(int)i,(int)j);

	}
	}
	return 0;
}
void RayMantaProducerSystem::eventloop(RayMantaBase& rmb, XEvent *e)
//int RayMantaProducerSystem::run(int ngenes)
{
	long int r = ::random();
	int index = r % genes.size();

	mutate(index);
	
	std::cout<<"fitness="<<fitness()<<std::endl;

  #define NIL (0)
  int events;
  GC gc;
  gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
  const char * test = "XMantaRay - Graphics producer system ";
  XmbDrawString(*(dpyb.get_display()), window->getTitleWindow(), fontset, gc, 20, 10, test, strlen(test));
  	draw(*this);
  
  for (int i = 0; i < 1000; i++) {//calibrator
    if (events = XPending(*(dpyb.get_display()))) { 
      //XEvent e;
      XNextEvent(*(dpyb.get_display()), e);
      printf("got event %d from number of events = %d\n", e->type, events);
	process_event(e);
    	//XSync(*dpy, 0);
	}
	
  }
	XFlush(*(dpyb.get_display()));
	return;
}
