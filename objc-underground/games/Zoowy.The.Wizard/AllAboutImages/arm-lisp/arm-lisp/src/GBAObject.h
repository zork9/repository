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
#import <Foundation/Foundation.h>
#import "TypeNameArray.h"
#import "MethodNameArray.h"

@interface GBAObject : NSObject {

	NSString *name;

	//types and methods of object
	TypeNameArray *typenamearray;
	MethodNameArray *methodnamearray;
}

- (NSString *)string;
- (int)isaid:(int)typenamei;
- (int)hasaid:(int)methodnamei;

- (int)isa:(TypeName*)typename;
- (int)hasa:(MethodName*)methodname;

@end
