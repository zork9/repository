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
#include <unistd.h> 
#include <signal.h> 
#include <cstdlib> 
#include "RayMantaNetMarkov2.h"
#include "Boltzman.h"

inline void signalforkfunc(int) {

	//auto unpause
}

template <class S, class T>
int RayMantaNetMarkov2<S,T>::markovpropagate(Matrix const& m) 
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

/*
	for (std::map<int, pid_t>::iterator vi = _scheduler.begin();
		vi != _scheduler.end(); vi++) {

		(*vi);	

	} 
*/	return 0;
}

template <class S, class T>
int RayMantaNetMarkov2<S,T>::waitforall() 
{

	killpg(_pgid, 30); //SIGUSR1
	return 0;
}

template <class S, class T>
int RayMantaNetMarkov2<S,T>::fork()
{
	pid_t pid, pid2 = -1;
	if ((pid = ::fork()) < 0)
		return -1;
	else if (pid2 == 0) { //child
		if ((pid = ::fork()) < 0)
			return -1;
		else if (pid == 0) { //child
			setpgid(pid, _pgid);
			_scheduler[_scheduler.size()] = pid;//FIXME -1 

			Boltzman b(10,10);
			Matrix m = b.generateboltzmanmatrix(b,10,10); //FIXME1 fill in matrix points
			markovpropagate(m);
	
			signal(30,signalforkfunc);

			//pause process 
			//if (pid != _scheduler[0])
			//	pause();
		} else { /* parent 2 */ }
		std::exit(0);
	} else { //parent
		std::exit(0);
	}

	return 0;
}

template<class S, class T>	
int RayMantaNetMarkov2<S,T>::markovtest(double d, pid_t pid)
{

	/*
	* You have to measure here for managing the Drawing process
	* i.e. from fork networks
	*/

	/*empty*/
} 

template class RayMantaNetMarkov2<std::string, void *>;
