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

#import "TypeTable.h"

@implementation TypeTable

- (TypeTable*)ctor
{
	_array = [NSMutableArray new]; 
	return self;
}

- (Type*) getObjectWithIndex:(int)si
{
	int i = 0;
	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if (i++ == si)
			return object;
	}

	return NULL;
}

- (Type*) getObject:(Type*)ti
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if (object == ti)
			return object;
	}

	return NULL;
}

- (int) searchForHex:(Hex*)hex
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ([object isKindOfClass:[Type class]]) {
			if ([[[[Hex alloc] ctorString:[object name]] hexnumberstring] compare: [hex hexnumberstring]] == 0)
				return (int) [object type];/*** | (int)[hex getNumber];***///FIXME
		}
	}

	return -1;	

}

- (int)hasType:(NSString*)typenamestring 
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ([object string] == typenamestring)
			return (int)0;
	}

	return -1;	

}

- (int)addType:(long int)typeid withName:(NSString*)name
{
	if ([self hasType:name] == 0) {//type already exists

		[_array removeObject:name];
		return 0;
	} else {

		[_array addObject:[[Type alloc] defineWithId:typeid andName:name]];
		return 0;
	}
	return -1;
}
@end
