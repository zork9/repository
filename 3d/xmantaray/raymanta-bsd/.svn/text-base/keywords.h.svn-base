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
#ifndef _KEYW_H_
#define _KEYW_H_

#include <vector>

template <class S, class T>
class KeyWords {
public:
	static std::vector<T> keywords;

public:
	//FIXME T& operator[](int index) { return keywords[index]; }
	T operator[](int index) { return keywords[index]; }
	int add(T t) { keywords.push_back(t); return 0; }
	int size() { return keywords.size(); }
};
template <class S, class T>
typename
std::vector<T> KeyWords<S,T>::keywords = std::vector<T>(); 

#endif
