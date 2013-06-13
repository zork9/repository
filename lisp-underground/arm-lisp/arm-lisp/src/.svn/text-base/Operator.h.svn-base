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
#ifndef __OPERATOR_H_
#define __OPERATOR_H_
#import <Foundation/Foundation.h>
#import "Hex.h"

// These are basic types, SymbolName is for runtime object typing

@interface Operator : NSObject {
	NSString*_name;
	Hex *_address;
}

- (Operator*) definwWithName:(NSString*)name andAddress:(Hex*)address;
- (Hex*)address;
- (NSString*)name;
- (NSString*)string;

@end

#endif
