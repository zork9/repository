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
#ifndef _POINT_H_
#define _POINT_H_
#include<cmath>
#include<iostream>
namespace ray3d {

class Point
{
public:
	Point(){}
	Point(double xx, double yy, double zz, unsigned long color) : x(xx),y(yy),z(zz),c(color) {}
	Point(double xx, double yy, double zz) : x(xx),y(yy),z(zz) {}
	virtual ~Point(){}

	double operator*(Point const&p) { return (const_cast<Point&>(p).x*x+const_cast<Point&>(p).y*y+const_cast<Point&>(p).z*z); }
	//double operator*(int const&p) { return (const_cast<Point&>(p).x*+const_cast<Point&>(p).y*y+const_cast<Point&>(p).z*z); }
	Point operator-(Point const&p) { return Point(const_cast<Point&>(p).x-x,const_cast<Point&>(p).y-y,const_cast<Point&>(p).z-z); }
	Point operator+(Point const&p) { return Point(const_cast<Point&>(p).x+x,const_cast<Point&>(p).y+y,const_cast<Point&>(p).z+z); }
	bool operator==(Point const&p) { return (x==const_cast<Point&>(p).x&&y==const_cast<Point&>(p).y&&z==const_cast<Point&>(p).z); }
	Point scale(int i) { x*=i; y*=i; z*=i; return *this; }
	Point scalex(int i) { x*=i; return *this; }
	Point scaley(int i) { y*=i; return *this; }
	Point scalez(int i) { z*=i; return *this; }
	Point operator=(Point const&p) { return Point(const_cast<Point&>(p).x+x,const_cast<Point&>(p).y+y,const_cast<Point&>(p).z+z); }
	double operator[](int index) { if (index == 0) return x; if (index == 1) return y; if (index == 2) return z; if (index == 3) return c; if (index > 3) return -1;  }

	Point operator()(double const& t) { x *= t; y *= t; z *= t; return *this; }
	double get_x() {return x;}
	double get_y() {return y;}
	double get_z() {return z;}
	double get_c() {return c;}//return color
	double get_color() {return c;}//return color
	double dist(Point const& p)
	{
		return (std::sqrt((get_x()-const_cast<Point&>(p).get_x()) * 
				(get_x()-const_cast<Point&>(p).get_x()) +
				(get_y()-const_cast<Point&>(p).get_y()) *
				(get_z()-const_cast<Point&>(p).get_z()) +
				(get_z()-const_cast<Point&>(p).get_z())));
	}
	int sqr(Point const& p)
	{
		x = get_x()*const_cast<Point&>(p).get_x(); y = get_y()*const_cast<Point&>(p).get_y(); z = get_z()*const_cast<Point&>(p).get_z();
		return 0;
	}
	Point normalize() { 
		double xx = x; 
		xx /= x*x+y*y+z*z;
		double yy = y; 
		yy /= x*x+y*y+z*z;
		double zz = z; 
		zz /= x*x+y*y+z*z;
		x = xx; y = yy; z = zz;
	}
protected:
	double x,y,z;
	unsigned long c;//color
};
}
#endif

