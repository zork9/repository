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
#include "Boltzman.h"

double Boltzman::fz(double N, int i, Energies egs, double eps, double t) { 

	double Zresult = 0;

	for (int j = 0; j < egs.size(); j++) {
		Zresult += egs[j]*std::exp(-eps/k*t);
	}
	return Zresult;
}

double Boltzman::f2(double N, Energies egs, double eps, double t) 
{
	double result = 0;
 
	for (int j = 0; j < egs.size(); j++) {
		result += N*egs[j]*std::exp(-eps/k*T)/fz(N, j, egs, eps, t);
	}

	return result; 
}
	
Matrix Boltzman::generateboltzmanmatrix(Boltzman const& b, int cols, int rows)
{

	Matrix m;
	Energies egs;
/*
	for (int k = 0; k < rows*cols; k++)
		egs.push_back(std::rand());
*/

	for (int i = 0; i < rows; i++){
		Vector v;
	for (int j = 0; j < cols; j++){
		
		v.add(const_cast<Boltzman&>(b).f2(rows*cols,egs,0.5,10));
	}
		m.add(v.get_points());
	}

	return m;

}

