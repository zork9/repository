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
#ifndef __SYMBOLARM_H_
#define __SYMBOLARM_H_
#import <Foundation/Foundation.h>
#import "Symbol.h"

@interface SymbolArm : Symbol {
	NSString* _registernumber;
	int _bracedepth;
}

- (int) defineWithId:(int)typeid andName:(NSString*)name;
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andValue:(NSString*)val andAddress:(int)addy andRegisterNumber:(int)rn;
- (int)getRegisterNumber;

@end

#endif
