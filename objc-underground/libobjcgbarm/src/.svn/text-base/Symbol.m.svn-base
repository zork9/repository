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

#import "Symbol.h"

@implementation Symbol

- (int) defineWithId:(int)typeid andName:(NSString*)name {

	_id = typeid;
	_name = (char *)[name UTF8String];
	return 0;
	
}

- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n {
	[super init];

	_id = i;
	_name = (char *)[n UTF8String];
	
	return self;
}

- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andAddress:(int)addy
{
	[super init];

	_id = i;
	_name = (char *)[n UTF8String];
	_address = [[Hex new]ctor:addy];
	return self;
}

- (Symbol*)ctor:(int)i withSymbolName:(NSString *)n andValue:(NSString*)val andAddress:(int)addy
{
	[super init];

	_id = i;
	_name = (char *)[n UTF8String];
	_address = [[Hex new]ctor:addy];
	_value = val;
	return self;
}

- (NSString *)string {
	return (NSString*)_name;
}

- (NSString *)value {
	return (NSString*)_value;
}

- (int)type {
	return _id;
}

- (Hex*)addresss {
	return _address;
}

- (int)getRegisterNumber
{
	return -1;
}
@end
