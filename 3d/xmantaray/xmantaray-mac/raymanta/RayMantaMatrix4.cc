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
#include "RayMantaMatrix4.h"
#include <iostream>

namespace ray3d {
	
double Vector4::operator*(Vector4 const& v)
{

	return (const_cast<Vector4&>(v).get_x()*get_x() + const_cast<Vector4&>(v).get_y()*get_y()+const_cast<Vector4&>(v).get_z()*get_z()+const_cast<Vector4&>(v).get_t());

}

Matrix4::Matrix4(Vector4 const& row1, Vector4 const& row2, Vector4 const& row3, Vector4 const& row4)
{
	x11 = const_cast<Vector4&>(row1).get_x();
	x12 = const_cast<Vector4&>(row1).get_y();
	x13 = const_cast<Vector4&>(row1).get_z();
	x14 = const_cast<Vector4&>(row1).get_t();
	x21 = const_cast<Vector4&>(row2).get_x();
	x22 = const_cast<Vector4&>(row2).get_y();
	x23 = const_cast<Vector4&>(row2).get_z();
	x24 = const_cast<Vector4&>(row2).get_t();
	x31 = const_cast<Vector4&>(row3).get_x();
	x32 = const_cast<Vector4&>(row3).get_y();
	x33 = const_cast<Vector4&>(row3).get_z();
	x34 = const_cast<Vector4&>(row3).get_t();
	x41 = const_cast<Vector4&>(row4).get_x();
	x42 = const_cast<Vector4&>(row4).get_y();
	x43 = const_cast<Vector4&>(row4).get_z();
	x44 = const_cast<Vector4&>(row4).get_t();
}

Matrix4 Matrix4::operator*(Matrix4 const& m)
{
//	if (m == *this)
//		return *this;
	
	return Matrix4(const_cast<Matrix4&>(m).get_x11()*get_x11()+
			const_cast<Matrix4&>(m).get_x12()*get_x21()+
			const_cast<Matrix4&>(m).get_x13()*get_x31()+
			const_cast<Matrix4&>(m).get_x14()*get_x41(),
			const_cast<Matrix4&>(m).get_x11()*get_x21()+
			const_cast<Matrix4&>(m).get_x12()*get_x22()+
			const_cast<Matrix4&>(m).get_x13()*get_x23()+
			const_cast<Matrix4&>(m).get_x14()*get_x24(),
			const_cast<Matrix4&>(m).get_x11()*get_x31()+
			const_cast<Matrix4&>(m).get_x12()*get_x32()+
			const_cast<Matrix4&>(m).get_x13()*get_x33()+
			const_cast<Matrix4&>(m).get_x14()*get_x34(),
			const_cast<Matrix4&>(m).get_x11()*get_x41()+
			const_cast<Matrix4&>(m).get_x12()*get_x42()+
			const_cast<Matrix4&>(m).get_x13()*get_x43()+
			const_cast<Matrix4&>(m).get_x14()*get_x44(),
			const_cast<Matrix4&>(m).get_x21()*get_x11()+
			const_cast<Matrix4&>(m).get_x22()*get_x21()+
			const_cast<Matrix4&>(m).get_x23()*get_x31()+
			const_cast<Matrix4&>(m).get_x24()*get_x41(),
			const_cast<Matrix4&>(m).get_x21()*get_x21()+
			const_cast<Matrix4&>(m).get_x22()*get_x22()+
			const_cast<Matrix4&>(m).get_x23()*get_x23()+
			const_cast<Matrix4&>(m).get_x24()*get_x24(),
			const_cast<Matrix4&>(m).get_x21()*get_x31()+
			const_cast<Matrix4&>(m).get_x22()*get_x32()+
			const_cast<Matrix4&>(m).get_x23()*get_x33()+
			const_cast<Matrix4&>(m).get_x24()*get_x34(),
			const_cast<Matrix4&>(m).get_x21()*get_x41()+
			const_cast<Matrix4&>(m).get_x22()*get_x42()+
			const_cast<Matrix4&>(m).get_x23()*get_x43()+
			const_cast<Matrix4&>(m).get_x24()*get_x44(),
			const_cast<Matrix4&>(m).get_x31()*get_x11()+
			const_cast<Matrix4&>(m).get_x32()*get_x21()+
			const_cast<Matrix4&>(m).get_x33()*get_x31()+
			const_cast<Matrix4&>(m).get_x34()*get_x41(),
			const_cast<Matrix4&>(m).get_x31()*get_x21()+
			const_cast<Matrix4&>(m).get_x32()*get_x22()+
			const_cast<Matrix4&>(m).get_x33()*get_x23()+
			const_cast<Matrix4&>(m).get_x34()*get_x24(),
			const_cast<Matrix4&>(m).get_x31()*get_x31()+
			const_cast<Matrix4&>(m).get_x32()*get_x32()+
			const_cast<Matrix4&>(m).get_x33()*get_x33()+
			const_cast<Matrix4&>(m).get_x34()*get_x34(),
			const_cast<Matrix4&>(m).get_x31()*get_x41()+
			const_cast<Matrix4&>(m).get_x32()*get_x42()+
			const_cast<Matrix4&>(m).get_x33()*get_x43()+
			const_cast<Matrix4&>(m).get_x34()*get_x44(),
			
			const_cast<Matrix4&>(m).get_x41()*get_x11()+
			const_cast<Matrix4&>(m).get_x42()*get_x21()+
			const_cast<Matrix4&>(m).get_x43()*get_x31()+
			const_cast<Matrix4&>(m).get_x44()*get_x41(),
			const_cast<Matrix4&>(m).get_x41()*get_x21()+
			const_cast<Matrix4&>(m).get_x42()*get_x22()+
			const_cast<Matrix4&>(m).get_x43()*get_x23()+
			const_cast<Matrix4&>(m).get_x44()*get_x24(),
			const_cast<Matrix4&>(m).get_x41()*get_x31()+
			const_cast<Matrix4&>(m).get_x42()*get_x32()+
			const_cast<Matrix4&>(m).get_x43()*get_x33()+
			const_cast<Matrix4&>(m).get_x44()*get_x34(),
			const_cast<Matrix4&>(m).get_x41()*get_x41()+
			const_cast<Matrix4&>(m).get_x42()*get_x42()+
			const_cast<Matrix4&>(m).get_x43()*get_x43()+
			const_cast<Matrix4&>(m).get_x44()*get_x44()
					
	);
}

Vector4 Matrix4::operator*(Vector4 const& v)
{

	return Vector4(get_x11()*const_cast<Vector4&>(v).get_x()+
			get_x12()*const_cast<Vector4&>(v).get_y()+
			get_x13()*const_cast<Vector4&>(v).get_z()+
			get_x14()*const_cast<Vector4&>(v).get_t(),
			get_x21()*const_cast<Vector4&>(v).get_x()+
			get_x22()*const_cast<Vector4&>(v).get_y()+
			get_x23()*const_cast<Vector4&>(v).get_z()+
			get_x24()*const_cast<Vector4&>(v).get_t(),
			get_x31()*const_cast<Vector4&>(v).get_x()+
			get_x32()*const_cast<Vector4&>(v).get_y()+
			get_x33()*const_cast<Vector4&>(v).get_z()+
			get_x34()*const_cast<Vector4&>(v).get_t(),
			get_x41()*const_cast<Vector4&>(v).get_x()+
			get_x42()*const_cast<Vector4&>(v).get_y()+
			get_x43()*const_cast<Vector4&>(v).get_z()+
			get_x44()*const_cast<Vector4&>(v).get_t());

}
} //namespace ray3d
