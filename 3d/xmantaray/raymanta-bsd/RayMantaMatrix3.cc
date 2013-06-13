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
#include "RayMantaMatrix3.h"
#include <iostream>

namespace ray3d {
	
double Vector3::operator*(Vector3 const& v)
{

	return (const_cast<Vector3&>(v).get_x()*get_x() + const_cast<Vector3&>(v).get_y()*get_y()+const_cast<Vector3&>(v).get_z()*get_z());

}

Matrix3::Matrix3(Vector3 const& row1, Vector3 const& row2, Vector3 const& row3)
{
	x11 = const_cast<Vector3&>(row1).get_x();
	x12 = const_cast<Vector3&>(row1).get_y();
	x13 = const_cast<Vector3&>(row1).get_z();
	x21 = const_cast<Vector3&>(row2).get_x();
	x22 = const_cast<Vector3&>(row2).get_y();
	x23 = const_cast<Vector3&>(row2).get_z();
	x31 = const_cast<Vector3&>(row3).get_x();
	x32 = const_cast<Vector3&>(row3).get_y();
	x33 = const_cast<Vector3&>(row3).get_z();
}

Matrix3 Matrix3::operator*(Matrix3 const& m)
{
//	if (m == *this)
//		return *this;
	//compiler optimized	
	return Matrix3(const_cast<Matrix3&>(m).get_x11()*get_x11()+
			const_cast<Matrix3&>(m).get_x12()*get_x21()+
			const_cast<Matrix3&>(m).get_x13()*get_x31(),
			const_cast<Matrix3&>(m).get_x11()*get_x21()+
			const_cast<Matrix3&>(m).get_x12()*get_x22()+
			const_cast<Matrix3&>(m).get_x13()*get_x23(),
			const_cast<Matrix3&>(m).get_x11()*get_x31()+
			const_cast<Matrix3&>(m).get_x12()*get_x32()+
			const_cast<Matrix3&>(m).get_x13()*get_x33(),
			const_cast<Matrix3&>(m).get_x21()*get_x11()+
			const_cast<Matrix3&>(m).get_x22()*get_x21()+
			const_cast<Matrix3&>(m).get_x23()*get_x31(),
			const_cast<Matrix3&>(m).get_x21()*get_x21()+
			const_cast<Matrix3&>(m).get_x22()*get_x22()+
			const_cast<Matrix3&>(m).get_x23()*get_x23(),
			const_cast<Matrix3&>(m).get_x21()*get_x31()+
			const_cast<Matrix3&>(m).get_x22()*get_x32()+
			const_cast<Matrix3&>(m).get_x23()*get_x33(),
			const_cast<Matrix3&>(m).get_x31()*get_x11()+
			const_cast<Matrix3&>(m).get_x32()*get_x21()+
			const_cast<Matrix3&>(m).get_x33()*get_x31(),
			const_cast<Matrix3&>(m).get_x31()*get_x21()+
			const_cast<Matrix3&>(m).get_x32()*get_x22()+
			const_cast<Matrix3&>(m).get_x33()*get_x23(),
			const_cast<Matrix3&>(m).get_x31()*get_x31()+
			const_cast<Matrix3&>(m).get_x32()*get_x32()+
			const_cast<Matrix3&>(m).get_x33()*get_x33());
}

Vector3 Matrix3::operator*(Vector3 const& v)
{
	return Vector3(get_x11()*const_cast<Vector3&>(v).get_x()+
			get_x12()*const_cast<Vector3&>(v).get_y()+
			get_x13()*const_cast<Vector3&>(v).get_z(),
			get_x21()*const_cast<Vector3&>(v).get_x()+
			get_x22()*const_cast<Vector3&>(v).get_y()+
			get_x23()*const_cast<Vector3&>(v).get_z(),
			get_x31()*const_cast<Vector3&>(v).get_x()+
			get_x32()*const_cast<Vector3&>(v).get_y()+
			get_x33()*const_cast<Vector3&>(v).get_z());

}
} //namespace ray3d
