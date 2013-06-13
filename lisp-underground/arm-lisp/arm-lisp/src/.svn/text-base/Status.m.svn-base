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

#import "Status.h"



@implementation Status

-(void) addStatus:(int)si {
	
	switch (si) {
		case 0:{
			break;
		}
		case NOMETHODSDECLAREDINCLASS:{
			[_statusstrs addObject: @"No methods declared in class interface."];
			break;
		}
		default:{
		}
	}
	
}

- (void) addStatusTuple:(TupleInt*)ti {
	[_statusstrs addObject:[[TupleInt new] addFirstInt:[ti first] andSecond:[ti second]]];
}

- (void) addStatus:(int)si withObject:(NSObject*)oi {
	[_statusstrs addObject:[[TupleInt new] addFirstInt:si andSecond:oi]];
}

- (Tuple*)getObject:(int)si
{
	Tuple *ti = [Tuple new];

	NSEnumerator *e = [_statusstrs objectEnumerator];
        id object;
        while (object = [e nextObject]) {
		if ([object first] == si) {
			[ti addFirstInt:e andSecond:[TupleInt new]];	
		}
        }	
	return ti; 
}

- (int)size
{
	return [_statusstrs length];
}

- (int)length
{
	return [_statusstrs length];
}

@end
