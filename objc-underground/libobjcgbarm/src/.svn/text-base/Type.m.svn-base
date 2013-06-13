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

#import "Type.h"

@implementation Type

// bogus
- (int) defineWithId:(long int)typeid andName:(NSString*)name {

	_id = typeid;
	_name = (char *)[name UTF8String];
	return 0;
	
}

- (Type*)ctor:(long int)i withTypeName:(NSString *)n {
	[super init];

	_id = i;
	_name = (char *)[n UTF8String];
	
	return self;
}

- (NSString *)string {
	return (NSString*)_name;
}

- (int)type {
	return _id;
}

@end
