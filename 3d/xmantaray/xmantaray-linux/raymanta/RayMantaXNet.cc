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
#include <iostream> 
#include <unistd.h> 
#include <signal.h> 
#include <cstdlib> 
#include <cstring> 
#include "RayMantaXNet.h"

inline void signalforkfunc(int) {

	//auto unpause
}

template <class S,class T>
int RayMantaXNet<S,T>::fork(S const& loadfilename, S const& parsefilename, int const& wordid)
{

	std::map<int , T> m;
	loadXkeywords(KeyWords<S,T>());
	T buf;
	
	std::cout<<"parsing...(*empty*)"<<std::endl;
}

template <class S, class T>
int RayMantaXNet<S,T>::loadXkeywords(KeyWords<S,T> const& kw)
{
        const_cast<KeyWords<S,T>& >(kw).add(::strdup("p:creat"));

        keywords = kw;

        return 0;
}



template class RayMantaXNet<std::string, void *>;
