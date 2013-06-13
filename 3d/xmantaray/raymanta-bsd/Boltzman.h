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
#ifndef _BOLTZMAN_H_
#define _BOLTZMAN_H_
#include <vector>
#include "RayMantaMatrix.h"
#include <cmath>

typedef std::vector<double> Energies;
class Boltzman {
public:
	Boltzman(double n, double t = 10) { k = std::pow(1.3806502,-23); T = t; N = n; epsilon = 0.5; Z = std::exp(epsilon/k*t); }
	virtual ~Boltzman() {}
	
	inline double frandomepsilon() { /*epsilon = std::rand(); return std::exp(-epsilon/k*T);*/ }
	inline double f() { return std::exp(-epsilon/k*T); }
	//Boltzman statistics (2 functions)
	inline double f2(double N, Energies egs, double eps, double t); 
	inline double fz(double N, int i, Energies egs, double eps, double t); 
	virtual Matrix generateboltzmanmatrix(Boltzman const& b, int cols, int rows);

protected:
	double N,Z,k,T,epsilon;
};

#endif
