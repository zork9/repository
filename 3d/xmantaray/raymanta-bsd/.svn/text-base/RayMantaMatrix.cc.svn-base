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
#include "RayMantaMatrix.h"

//no test for equal rows/columns	
double Vector::operator*(Vector const& v)
{
	double result = 0;

	for (PointsVector::iterator vi = const_cast<Vector&>(v).get_points().begin(), pi = points.begin(); pi != points.end(); pi++, vi++)
		result += (*pi)*(*vi);

	return result;

}

//no test for equal rows/columns	
Matrix Matrix::operator*(Matrix const& m)
{
//	if (m == *this)
//		return *this;

	PointsMatrix pms;
	PointsVector pvs;	

	for (PointsMatrix::iterator pi = const_cast<Matrix&>(m).get_points().begin(), qi = points.begin(); qi != points.end(); pi++, qi++)
		for (PointsVector::iterator vi = const_cast<PointsVector&>(*pi).begin(), wi = const_cast<PointsVector&>(*qi).begin(); vi != const_cast<PointsVector&>(*pi).end(); wi++, vi++)
			//FIXME transpose
			pvs.push_back((*vi)*(*wi));
		pms.push_back(pvs);
		pvs = PointsVector();	

	return Matrix(pms);
}

Vector Matrix::operator*(Vector const& v)
{
	PointsVector pvs;	

	for (PointsMatrix::iterator pi = get_points().begin(); pi != points.end(); pi++)
		pvs.push_back(const_cast<Vector&>(v) * (*pi));

	return Vector(pvs);	
}

