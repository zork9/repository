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
#include "xluacode.h"
#include<string>
#include<cstdio>

#include "../raymanta/RayMantaNet.h"
#include "../raymanta/RayMantaNetMarkov2.h"
#include "../raymanta/RayMantaXNet.h"

namespace XLUA {

int luanetfork(lua_State *L)
{
	std::string loadfilename, parsefilename;
	int kwl;
	int n = lua_gettop(L);
	if (n == 1 || n != 3) std::fprintf(stdout, "Do not fork.\t");
	if (lua_isstring(L,1)) loadfilename = lua_tostring(L,1);
	if (lua_isstring(L,2)) parsefilename = lua_tostring(L,2);
	if (lua_isnumber(L,3)) kwl = lua_tonumber(L,3);

	RayMantaNet<std::string,std::string> net;

	for (int i = 0; i < kwl; i++) {	
		///net.fork(std::string(loadfilename.c_str()), std::string(parsefilename.c_str()), i);
		net.fork();
	}

	return 0;

}

int luamarkovnetfork(lua_State *L)
{ 
	/*FIXME : 
	 * include RayMantaNetMarkov net; and do net.fork as above in
	 * the luanetfork procedure. 
	 * You can also coroutine the markovpropagate function code in lua's
	 * syntax : coroutine.create
	 */ 
	std::string loadfilename, parsefilename;
	int kwl;
	int n = lua_gettop(L);
	if (n == 1 || n != 3) fprintf(stdout, "Do not fork.\t");
	if (lua_isstring(L,1)) loadfilename = lua_tostring(L,1);
	if (lua_isstring(L,2)) parsefilename = lua_tostring(L,2);
	if (lua_isnumber(L,3)) kwl = lua_tonumber(L,3);

	RayMantaNetMarkov2<std::string,std::string> net;

	for (int i = 0; i < kwl; i++) {	
		///net.fork(std::string(loadfilename.c_str()), std::string(parsefilename.c_str()), i);
		net.fork();
	}


	return 0; 
}

int luaxnetfork(lua_State *L)
{ 
	/*FIXME : 
	 * include RayMantaNetMarkov net; and do net.fork as above in
	 * the luanetfork procedure. 
	 * You can also coroutine the markovpropagate function code in lua's
	 * syntax : coroutine.create
	 */ 
	std::string loadfilename("./loadfile"), parsefilename("./parsefile");
	int kwl;
	int n = lua_gettop(L);
	if (n == 1 || n != 3) fprintf(stdout, "Do not fork.\t");
	if (lua_isstring(L,1)) loadfilename = lua_tostring(L,1);
	if (lua_isstring(L,2)) parsefilename = lua_tostring(L,2);
	if (lua_isnumber(L,3)) kwl = lua_tonumber(L,3);

	RayMantaXNet<std::string,std::string> net;

	fprintf(stdout, "Forking for keywords in %s...\n",  parsefilename.c_str());
	for (int i = 0; i < kwl; i++) {	
		net.fork(std::string(loadfilename.c_str()), std::string(parsefilename.c_str()), i);
	}


	return 0; 
}

}

