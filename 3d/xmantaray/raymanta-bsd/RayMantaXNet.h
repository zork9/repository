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
#ifndef _RAYXNET_H_
#define _RAYXNET_H_

#include <map>
#include <iostream>
#include <unistd.h>
#include "RayMantaNet.h"
#include "keywords.h"

template <class S, class T>
class RayMantaXNet : public RayMantaNet<S,T>
{
public:
	RayMantaXNet() : RayMantaNet<S,T>() { }
	virtual ~RayMantaXNet() {}

protected:
	KeyWords<S,T> keywords;
	virtual int loadXkeywords(KeyWords<S,T> const& kw);
public:

	virtual int addkeyword(T const& keyword) { keywords.add(keyword); return 0; }
	virtual int fork(S const& loadfilename, S const& parsefilename, int const& wordid);

};

#endif
