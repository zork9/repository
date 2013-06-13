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
#ifndef _RAYMANTA_MATRIX_4_H_
#define _RAYMANTA_MATRIX_4_H_

#include "RayMantaMatrix3.h"

namespace ray3d {

class Vector4
{
public:
	Vector4(){}
	Vector4(Vector3 const& v, double tt) : x11(const_cast<Vector3&>(v).get_x()), x12(const_cast<Vector3&>(v).get_y()), x13(const_cast<Vector3&>(v).get_z()), x14(tt) {}
	Vector4(double xx, double yy, double zz, double tt) : x11(xx), x12(yy), x13(zz), x14(tt) {}
	virtual ~Vector4() {}
	Vector4(Vector4 const& v) { 
		x11 = const_cast<Vector4&>(v).get_x(); x12 = const_cast<Vector4&>(v).get_y(); x13 = const_cast<Vector4&>(v).get_z(); x14 = const_cast<Vector4&>(v).get_t(); }

	double get_x() { return x11; }
	double get_y() { return x12; }
	double get_z() { return x13; }
	double get_t() { return x14; }

protected:
	double x11,x12,x13,x14;

public:
	Vector4 operator()(double t) { x11 *= t; x12 *= t; x13 *= t; x14 *= t; return *this; }
	double operator*(Vector4 const& v);
	Vector4 operator=(Vector4 const& v) { 
		x11 = const_cast<Vector4&>(v).get_x(); x12 = const_cast<Vector4&>(v).get_y(); x13 = const_cast<Vector4&>(v).get_z(); x14 = const_cast<Vector4&>(v).get_t(); return *this; }
};

class Matrix4 {

public:
	Matrix4() {}
	Matrix4(Vector4 const& row1, Vector4 const& row2, Vector4 const& row3, Vector4 const& row4); 
	virtual ~Matrix4() {}

	Matrix4(double xx11,double xx12,double xx13,double xx14,double xx21,double xx22,double xx23,double xx24,double xx31,double xx32, double xx33, double xx34, double xx41, double xx42, double xx43, double xx44) 
	{ 
	  x11 = xx11;
	  x12 = xx12;
	  x13 = xx13;
	  x14 = xx14;
	  x21 = xx21;
	  x22 = xx22;
	  x23 = xx23;
	  x24 = xx24;
	  x31 = xx31;
	  x32 = xx32;
	  x33 = xx33;
	  x34 = xx34;
	  x41 = xx41;
	  x42 = xx42;
	  x43 = xx43;
	  x44 = xx44;

	}

	double get_x11() { return x11; }
	double get_x12() { return x12; }
	double get_x13() { return x13; }
	double get_x14() { return x14; }
	double get_x21() { return x21; }
	double get_x22() { return x22; }
	double get_x23() { return x23; }
	double get_x24() { return x24; }
	double get_x31() { return x31; }
	double get_x32() { return x32; }
	double get_x33() { return x33; }
	double get_x34() { return x34; }
	double get_x41() { return x41; }
	double get_x42() { return x42; }
	double get_x43() { return x43; }
	double get_x44() { return x44; }

	Matrix4 project(double d) { return (Matrix4(1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,1/d,0)); }

protected:
	double x11,x12,x13,x14,x21,x22,x23,x24,x31,x32,x33,x34,x41,x42,x43,x44;
public:
	Matrix4 operator*(Matrix4 const& m);
	Vector4 operator*(Vector4 const& v);
};

} // namespace ray3d

#endif
