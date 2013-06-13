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

#import "SymbolTable.h"

@implementation SymbolTable

- (SymbolTable*)ctor
{
	_array = [NSMutableArray new]; 
	return self;
}

- (Symbol*) getObjectWithIndex:(int)si
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

- (Symbol*) getObject:(Symbol*)ti
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if (object == ti)
			return object;
	}

	return NULL;
}

- (Symbol*) getString:(NSString*)s
{

	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		if ([object string] == s)
			return object;
	}

	return NULL;
}

- (Symbol*) searchForHex:(Hex*)hex
{


	NSEnumerator *e = [_array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		//skip null hex
		if ([[[Hex alloc] ctorString:[object name]] hexnumberstring] == nil)
			return nil;
		NSLOG3(@"%@ = %@", [[[Hex alloc] ctorString:[object name]] hexnumberstring], [hex hexnumberstring]);
		if ([[[[Hex alloc] ctorString:[object name]] hexnumberstring] compare: [hex hexnumberstring]] == 0)
			return object;/*** | (int)[hex getNumber];***///FIXME
	}

	return nil;	

}

- (void) addObject:(Symbol*)s
{
	[_array addObject: s];
}

- (int) addObjectExists:(Hex*)h form:(Form*)f type:(TYPE)t
{
	NSEnumerator *e = [_array objectEnumerator];
	id object;
	Symbol *s;
	while (object = [e nextObject]) {
		if ([[object address] number] == [h number]) {
			s = [[Symbol alloc] ctorName:[object name] form:f type:t];
			[_array removeObject:object];
			[_array addObject:s];
			return 0;
		}
	}
	return -1;
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

}*/

@end
