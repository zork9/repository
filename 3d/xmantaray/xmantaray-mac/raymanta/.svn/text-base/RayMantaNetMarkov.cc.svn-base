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
#include <functional> 
#include <cstdlib> 
#include "RayMantaMatrix.h"
#include "RayMantaNetMarkov.h"
#include <map>

template<class S, class T>	
Matrix RayMantaNetMarkov<S,T>::generateboltzmanmatrix(Boltzman const& b, int cols, int rows)
{

	Matrix m;
	Energies egs;

	for (int k = 0; k < rows*cols; k++)
		egs.push_back(std::rand());


	for (int i = 0; i < rows; i++){
		Vector v;
	for (int j = 0; j < cols; j++){
		
		v.add(const_cast<Boltzman&>(b).f2(rows*cols,egs,0.5,10));
	}
		m.add(v.get_points());
	}

	return m;

}

template<class S, class T>	
int RayMantaNetMarkov<S,T>::markovpropagate(Matrix const& m) 
{
	/*
	* FIXME NOTE :
	* You have to propagate the processes for running
	* Use the RayMantaMatrix classes for matrix propagation
	*/
	std::cout<<"Entering critical section..."<<std::endl;
	int mindex = 0, mindex2 = 0;
	for (std::map<int, pid_t>::iterator vi = static_cast<std::map<int, pid_t> >(_scheduler).begin(); vi != static_cast<std::map<int, pid_t> >(_scheduler).end(); vi++, mindex++) {
		
		for (mindex2 = 0; mindex2 < ((const_cast<Matrix&>(m).get_points())[mindex])[mindex2]; mindex2++) { 
			double d = const_cast<Matrix&>(m).get_points()[mindex][mindex2];
			markovtest(d, (*vi).second);
		}
	} 
	return 0;
}

template<class S, class T>	
int RayMantaNetMarkov<S,T>::markovtest(double d, pid_t pid)
{

	/*
	* You have to measure here for managing the Drawing process
	* i.e. from fork networks
	*/

	/*empty*/
} 

