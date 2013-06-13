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
#include "RayMantaNet.h"

inline void signalforkfunc(int) {

	//auto unpause
}

template <class S, class T>
int RayMantaNet<S,T>::markovpropagate() 
{
	/*
	* FIXME NOTE :
	* You have to propagate the processes for running
	* Use the RayMantaMatrix classes for matrix propagation
	*/


	for (std::map<int, pid_t>::iterator vi = _scheduler.begin();
		vi != _scheduler.end(); vi++) {

		(*vi);	

	} 
	return 0;
}

template <class S, class T>
int RayMantaNet<S,T>::waitforall() 
{

	killpg(_pgid, 30); //SIGUSR1
	return 0;
}

template <class S, class T>
int RayMantaNet<S,T>::fork()
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


			markovpropagate();
	
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

template <class S,class T>
int RayMantaNet<S,T>::fork(S const& loadfilename, S const& parsefilename, int const& wordid)
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
			signal(30,signalforkfunc);

			//wait for root window to be initialized
			if (pid != _scheduler[0])
				pause();
		} else { /* parent 2 */ }
		std::exit(0);
	} else { //parent
		std::exit(0);
	}

	return 0;
}
template class RayMantaNet<std::string, void *>;
