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
#include <pthread.h> 
#include <cstdlib> 
#include "RayMantaNetPthread.h"

void *forkfunc(void *arg)
{
	return NULL;

}

template <class S, class T>
int RayMantaNetPthread<S,T>::waitforall() 
{

	return 0;

}

template <class S, class T>
int RayMantaNetPthread<S,T>::fork(S const& loadfilename, S const& parsefilename, int const& wordid)
{
	pthread_t pid;
	//	void *arg = new Parser<S,T>(loadfilename, parsefilename,wordid); //NOTE : use & Parser for warning;
	pthread_create(&pid,NULL,&forkfunc,NULL);
	if (pid < 0)
		return -1;
 	_scheduler[(int)_scheduler.size()] = pid;	
	return 0;
}
/*
template <class S, class T>
int RayMantaNetPthread<S,T>::parse(Parser<S,T> parser)
{

	return parser.parse();

}
*/


template class RayMantaNetPthread<std::string, void * >;

