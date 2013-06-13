/*
 Copyright (C) Johan Ceuppens 2012
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
//
//  Created by link on 25/10/12.
//

#ifndef UTIL_H_
#define UTIL_H_

/*
 * This is a TypeName class as seen in libobjcgbarm
 */

#import "arm-lisp-config.h" 

void NSLOG(void*x) {
	#ifdef _DEBUG
	NSLog(x);
	#endif
};
void NSLOG2(void*x,void*y) {
	#ifdef _DEBUG
	NSLog(x,y);
	#endif
};
void NSLOG3(void*x,void*y,void*z) {
	#ifdef _DEBUG
	NSLog(x,y,z);
	#endif
};
void NSLOG4(void*x,void*y,void*z,void*xx) {
	#ifdef _DEBUG
	NSLog(x,y,z,xx);
	#endif
};
void NSLOG5(void*x,void*y,void*z,void*xx,void*yy) {
	#ifdef _DEBUG
	NSLog(x,y,z,xx,yy);
	#endif
};
void NSLOG6(void*x,void*y,void*z,void*xx,void*yy,void*zz) {
	#ifdef _DEBUG
	NSLog(x,y,z,xx,yy,zz);
	#endif
};
void NSLOG7(void*x,void*y,void*z,void*xx,void*yy,void*zz,void*xxx) {
	#ifdef _DEBUG
	NSLog(x,y,z,xx,yy,zz,xxx);
	#endif
};
#endif
