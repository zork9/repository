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

#import "SymbolArm.h"

@implementation SymbolArm

- (int) defineWithId:(int)typeid andName:(NSString*)name andRegisterNumber:(int) rn{

	_id = typeid;
	_name = (char *)[name UTF8String];
	_registernumber = rn;

	return 0;
	
}
- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andValue:(NSString*)val andAddress:(int)addy andRegisterNumber:(int)rn
{
	[super init];

	_id = i;
	_name = (char *)[n UTF8String];
	_address = [[Hex new]ctor:addy];
	_value = val;
	_registernumber = rn;

	//_bracedepth = bn;

	return self;
}

- (int)getRegisterNumber
{
	return _registernumber;
}

@end
