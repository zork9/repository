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
#ifndef _OSYSTEM_H_
#define _OSYSTEM_H_

#include <vector>
#include <cmath>
#include "RayManta.h"
#include "RayMantaGA.h"

typedef std::vector<double > Genes;
#define SCREENW 800
#define SCREENH 600

class RayMantaProducerSystem : public RayMantaGA, public RayManta  {
public:
  	RayMantaProducerSystem(RayMantaBase& rmb,DisplayBase<Display **>& dpyb2) : RayManta(rmb,dpyb2)
	{ 
		genes.reserve(SCREENW*SCREENH);
		for (int i = 0; i < SCREENW*SCREENH /*genes.size()*/; i++) {

			genes[i] = (::rand());

		}
	}
	virtual ~RayMantaProducerSystem() {}
	//run once and get_genes afterwards for screen plot
	virtual Genes initcrossovergenes(int n);
	virtual Genes mutate(int index);
	virtual Genes crossover(int index1, int index2);
  	virtual int draw(RayMantaBase const& rmb);
  	virtual void eventloop(XEvent *e); 

protected:
};

#endif
