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
#ifndef _MARKOVNET_H_
#define _MARKOVNET_H_

#include <map>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "RayMantaNet.h"
#include "RayMantaMatrix.h"
#include "Boltzman.h"

template <class S, class T>
class RayMantaNetMarkov : public RayMantaNet<S,T>
{
public:
	RayMantaNetMarkov() {}
	virtual ~RayMantaNetMarkov() {}
	
public:

	virtual int markovpropagate(Matrix const& m);
	virtual int markovtest(double d, pid_t pid);
	virtual Matrix generateboltzmanmatrix(Boltzman const& b, int cols, int rows);
};


#endif
