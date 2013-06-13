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

#import <Cocoa/Cocoa.h>
#import "Hex.h"
// These are basic types, SymbolName is for runtime object typing

typedef int TYPEID;
typedef int TYPE;

TYPE ctype = 0x01;
TYPE itype = 0x02;
TYPE vtype = 0x03;

@interface Symbol : NSObject {
		//type of symbol
		TYPE _id;
		//ascii name of symbol
		char *_name;
		//value of symbol
		NSString* _value;
		//address
		Hex*_address;
}

- (int) defineWithId:(int)typeid andName:(NSString*)name;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andAddress:(Hex*)addy;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andValue:(NSString*)val andAddress:(Hex*)addy;
- (NSString *)string;
- (NSString *)value;
- (Hex*)address;
- (TYPE)type;
- (int)getRegisterNumber;
@end
