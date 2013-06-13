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
#ifndef _RAYNET_H_
#define _RAYNET_H_

#include <map>
#include <iostream>
#include <unistd.h>
#include "RayMantaNetBase.h"

template <class S, class T>
class RayMantaNet : public RayMantaNetBase
{
public:
	RayMantaNet() { _pgid = 256; }
	RayMantaNet(RayMantaNet const& n) { _scheduler = n._scheduler; _pgid = n._pgid; }
	virtual ~RayMantaNet() {}

	inline virtual int lock(pid_t pid) { _scheduler[pid] = -1; return 0; }
	inline virtual int get_status(pid_t pid) { return _scheduler[pid]; }
	inline virtual void set_status(pid_t pid, int s) { _scheduler[pid] = s; }

	
protected:
	//The following map can be used in reverse at the same time of the
	//transverse, you can search for pids
	//or your own process integer i.e. you can put pids in it.
	//You can also put in pids multiple times for fast lookups and
	//extra process data, you will then have to search the whole map
	//for your pids/ints.
	static std::map<int, pid_t> _scheduler;
	pid_t _pgid;
public:

	virtual int fork();
	virtual int fork(S const& loadfilename, S const& parsefilename, int const& wordid);
	virtual int waitforall();

	virtual int markovpropagate();

public:
	RayMantaNet &operator=(RayMantaNet const& n) { _scheduler = n._scheduler; _pgid = n._pgid; return *this; }
};

template <class S, class T>
typename
std::map<int, pid_t> RayMantaNet<S,T>::_scheduler = std::map<int,pid_t>(); 

#endif
