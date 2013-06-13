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

Genes RayMantaProducerSystem::initcrossovergenes(int n) 
{

	Genes cg(n);

	for (int i = 0; i < n; i++) {

		cg[i] = (::rand());

	}
	
	return cg;
}

Genes RayMantaProducerSystem::mutate(int index)
{

	for (int i = 0; i < genes.size(); i++) {

		genes[i] = ::rand();

	}
	return genes;	
}
Genes RayMantaProducerSystem::crossover(int index1, int index2)
{
	crossovergenes = initcrossovergenes(index2-index1);
	//crossover from index1 to index2

	if (index1 > crossovergenes.size() || index2 > crossovergenes.size())
		return genes;

	for (int i = index1; i < index2; i++) {
		genes[i] = crossovergenes[i];
	}
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
	values.background = color;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*(dpyb.get_display()), w, valuemask, &values);
        XDrawLine(*(dpyb.get_display()),window->getWindow(),gc,(int)i,(int)j,(int)i,(int)j);

	}
	}
	return 0;
}
void RayMantaProducerSystem::eventloop(XEvent *e)
//int RayMantaProducerSystem::run(int ngenes)
{
	long int r = ::random();
	int index = r % genes.size();
	long int r2 = ::random();
	int index2 = r2 % genes.size();

	//do mutation or crossover for fitness eval
	mutate(index);
	//crossover(index,index2);
	std::cout<<"fitness="<<fitness()<<std::endl;
  #define NIL (0)
  int events;
  GC gc;
  gc = XCreateGC(*(dpyb.get_display()), window->getWindow(), 0, NIL);
  const char * test = "XMantaRay - Graphics Producer framework";
  XmbDrawString(*(dpyb.get_display()), window->getTitleWindow(), fontset, gc, 20, 10, test, strlen(test));
  draw(*this);
  
  for (int i = 0; i < 1000; i++) {//calibrator
    if (events = XPending(*(dpyb.get_display()))) { 
      //XEvent e;
      XNextEvent(*(dpyb.get_display()), e);
      printf("got event %d from number of events = %d\n", e->type, events);
	process_event(e);
	XFillRectangle(*(dpyb.get_display()), window->getTitleWindow(), gc,0,0,800,20);
	XFillRectangle(*(dpyb.get_display()), window->getWindow(), gc,0,0,800,600);
    	//XSync(*dpy, 0);
	}
	
  }
	XFlush(*(dpyb.get_display()));
/*
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
*/	return;
}
