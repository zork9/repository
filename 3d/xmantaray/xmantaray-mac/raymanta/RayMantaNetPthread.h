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
#ifndef _NETPTHREAD_H_
#define _NETPTHREAD_H_

#include <map>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "RayMantaNetBase.h"

template <class S, class T>
class RayMantaNetPthread : public RayMantaNetBase
{
public:
	RayMantaNetPthread() {}
	RayMantaNetPthread(RayMantaNetPthread const& n) { this->_scheduler = n._scheduler; }
	virtual ~RayMantaNetPthread() {}

	inline virtual int lock(pthread_t pid) { return 0; }
	inline virtual int get_status(int pid) { return 0; }
	inline virtual void set_status(int pid, int s) {}

	
private:
	static std::map<int, pthread_t> _scheduler;

public:

	virtual int fork(S const& loadfilename, S const& parsefilename, int const& wordid);
//	virtual int parse(Parser<S,T> parser);
	virtual int waitforall();
public:
	RayMantaNetPthread &operator=(RayMantaNetPthread const& n) { _scheduler = n._scheduler; return *this; }
};

template <class S, class T>
typename
std::map<int, pthread_t> RayMantaNetPthread<S,T>::_scheduler = std::map<int, pthread_t>(); 

#endif
