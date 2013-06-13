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
#ifndef _XLUA_H_
#define _XLUA_H_
#include <string>
#include "../include/lua.h"
#include "../include/llex.h"
#include "../include/lauxlib.h"
//#include <lua.h>//FIXME1

namespace XLUA {

template <class S, class T>
class Xlua {
public:
	explicit Xlua() { L = NULL; init(); }
	virtual ~Xlua() { lua_close(L); }

	virtual int load();

protected:
	//lua interpreting load and call functions
	virtual int init();
	virtual int loadfile(S const& filename) { 
		luaL_loadfile(L,filename.c_str());
		return 0;
	}
	virtual int loadstring(S const& s) { 
		luaL_loadfile(L,s.c_str());
		return 0;
	}
protected:
	lua_State *L;
};

}
#endif
