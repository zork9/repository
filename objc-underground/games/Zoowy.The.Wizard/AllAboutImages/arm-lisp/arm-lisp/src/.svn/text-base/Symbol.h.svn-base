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
#ifndef __SYMBOL_H_
#define __SYMBOL_H_
#import <Foundation/Foundation.h>
#import "Hex.h"
#import "Form.h"

// These are basic types, SymbolName is for runtime object typing

typedef int TYPEID;
typedef long int TYPE;

//NOTE : do not make a type 0
/*static const TYPE ctype = 1;//character type
static const TYPE itype = 2;//integer type
static const TYPE vtype = 4;//vector type
static const TYPE stype = 8;//string type
static const TYPE ftype = 16;//float type
static const TYPE symtype = 32;//string type
static const TYPE formtype = 64;//string type
static const TYPE ltype = 128;//string type
*/

enum {
	ctype = 1,
	itype = 2,
	vtype = 4,
	stype = 8,
	ftype = 16,
	symtype = 32,
	formtype = 64,
	ltype = 128,
	functype = 256,
};

@interface Symbol : NSObject {
		//type of symbol
		TYPE _id;
		//ascii name of symbol
		NSString *_name;
		//value of symbol, can be a Lisp form
		Form* _value;
		//address
		Hex*_address;
		//documentation string
		struct documentation { NSString *string; } *_documentation;
}

- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n form:(NSString*)form;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andAddress:(Hex*)addy;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andValue:(NSString*)val andAddress:(Hex*)addy;
- (Symbol*)ctorName:(NSString*)symname form:(Form*)form;

- (NSString *)string;
- (NSString *)name;
- (NSString *)value;
- (Hex*)address;
- (TYPE)type;

- (void)initDocString;
@end

#endif
