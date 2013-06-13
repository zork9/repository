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
#ifndef _RAYENGINE_H_
#define _RAYENGINE_H_
#include "RayMantaMatrix3.h"
#include<cmath>
#include<iostream>

namespace ray3d {

inline Matrix3 rotatex(double t1) {
	return (Matrix3(1,0,0,0,std::cos(t1),-std::sin(t1),0,std::sin(t1),std::cos(t1)));
}
inline Matrix3 rotatey(double t2) {
	return (Matrix3(std::cos(t2),0,std::sin(t2),0,1,0,-std::sin(t2),0,std::cos(t2)));
}
inline Matrix3 rotatez(double t3) {
	return (Matrix3(std::cos(t3),-std::sin(t3),0,std::sin(t3),std::cos(t3),0,0,0,1));
}
	
class Engine {
public:

	Engine() {}
	Engine(double t1, double t2, double t3) 
		: vtr(Vector3(1,1,1)),
		  mx(ray3d::rotatex(t1)),
		  my(ray3d::rotatey(t2)),
		  mz(ray3d::rotatez(t3)),
		  mtotal(mx*my*mz) {}
	virtual ~Engine() {}

	inline Matrix3 rotatex(double t) { theta1 = t; return ray3d::rotatex(t); }	
	inline Matrix3 rotatey(double t) { theta2 = t; return ray3d::rotatey(t); }	
	inline Matrix3 rotatez(double t) { theta3 = t; return ray3d::rotatez(t); }


	inline Vector3 translate(double t) { return vtr(t); }

	inline Matrix3 rotate (double t1,double t2,double t3) { 
		if (t1==theta1 && t2 == theta2 && t3 == theta3) 
			return mtotal;
		mtotal = initrotatex(t1)*initrotatey(t2)*initrotatez(t3); 
		return mtotal;
	}	
	inline Matrix3 rotate2(double t1,double t2,double t3) { 
		if (t1==theta1 && t2 == theta2 && t3 == theta3) 
			return mtotal;
		if (t1==theta1 && t2 == theta2) 
			return (mtotal = mx*my*initrotatez(t3)); 
		if (t1==theta1 && t3 == theta3) 
			return (mtotal = mx*initrotatey(t2)*mz); 
		if (t2==theta2 && t3 == theta3) 
			return (mtotal = initrotatex(t1)*my*mz); 
		if (t1==theta1) 
			return (mtotal = mx*initrotatey(t2)*initrotatez(t3)); 
		if (t2==theta2) 
			return (mtotal = initrotatex(t1)*my*initrotatez(t3)); 
		if (t3==theta3) 
			return (mtotal = initrotatex(t1)*initrotatey(t2)*mz); 
			
		return (mtotal = mx*my*mz);
		}
private:
	inline Matrix3 initrotatex(double t) { theta1 = t; return ray3d::rotatex(t); }	
	inline Matrix3 initrotatey(double t) { theta2 = t; return ray3d::rotatey(t); }	
	inline Matrix3 initrotatez(double t) { theta3 = t; return ray3d::rotatez(t); }

protected:	

	Vector3 vtr;
	double theta1,theta2,theta3;
	Matrix3 mx,my,mz,mtotal;
};
}
#endif
