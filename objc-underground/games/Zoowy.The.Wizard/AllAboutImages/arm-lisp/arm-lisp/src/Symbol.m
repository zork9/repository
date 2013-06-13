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

- (Symbol*)ctor:(int)i withSymbolName:(Form *)n {

	[self initDocString];
	_id = i;
	_name = n;
	[self initDocString];	
	return self;
}

- (Symbol*)ctor:(int)i withSymbolName:(Form *)n andAddress:(int)addy
{
	[self initDocString];
	_id = i;
	_name = n;
	_address = [[Hex new]ctor:addy];
	return self;
}

- (Symbol*)ctor:(int)i withSymbolName:(Form *)n form:(Form*)form
{
	[self initDocString];
	_id = i;
	_name = n;
	return self;
}

- (Symbol*)ctor:(int)i withSymbolName:(Form *)n andValue:(Form*)val andAddress:(int)addy
{
	[self initDocString];
	_id = i;
	_name = n;
	_address = [[Hex new]ctorInt:addy];
	_value = val;
	return self;
}

- (Symbol*)ctorName:(NSString*)symname form:(Form*)form
{
	[self initDocString];
	_name = symname;
	_address = [[Hex alloc] ctorString:symname];
	_value = form;
	_id = formtype;
	return self;
}

- (Symbol*)ctorName:(NSString*)symname form:(Form*)form type:(TYPE)t
{
	[self initDocString];
	_name = symname;
	_address = [[Hex alloc] ctorString:symname];
	_value = form;
	_id = t;
	return self;
}

- (NSString *)string {
	return _name;
}

- (NSString *)name {
	return _name;
}

- (Form *)value {
	return _value;
}

- (int)type {
	return _id;
}

- (Hex*)address {
	return _address;
}

- (NSString*)documentation
{
	if (_documentation != nil)
		return _documentation->string;
	return nil;
}

- (void)initDocString
{
	_documentation = (struct documentation*)malloc(sizeof(struct documentation));
	_documentation->string = [[NSString alloc] initWithString:@""];
}

@end
