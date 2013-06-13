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

#import "OperatorTable.h"

@implementation OperatorTable

- (OperatorTable*)ctor
{
	_array = [NSMutableArray new]; 
	return self;
}

- (Operator*) getObjectWithIndex:(int)si
{
	int i = 0;
	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if (i++ == si)
			return object;
	}

	return nil;
}

- (Operator*) getObject:(Operator*)ti
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if (object == ti)
			return object;
	}

	return nil;
}

- (Operator*) getOperator:(NSString*)s
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ([[object string] compare:s] == 0)
			return object;
	}

	return nil;
}

- (int) searchForHex:(Hex*)hex
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ([[Hex new] ctor:[object string]] == hex)
			return (int)[ object type ];// | (int)[hex getNumber];FIXME
	}

	return -1;	

}

- (void) addObject:(Operator*)s
{
	[_array addObject: s];
}
/*
- (int) set:(NSString*)s1 value:(NSString*)s2
{
	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ( s1 == [object string] ) {
			[object setValue:s2];
			return;//NOTE only set first come value (queue)
		}
	}

	return NULL;	

}
*/
@end
