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

#import "Hex.h"

@implementation Hex 

/*
 * Table address scription
 */
- (Hex*) ctorString:(NSString*)word
{
	int i = [word length];
	//NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	if (i == 0)
		return nil;

	_hex = 0;
	while (--i >= 0) {
		char c = [word characterAtIndex: i];
		_hex |= c;//NOTE address transcription ! 
		//[s appendFormat:@"%c",c];
	}
	//memcpy(&_hex,[s UTF8String],[word length]);//NOTE little endian !

	return self;
}

- (Hex*) ctorInt:(int)h
{
	_hex = h;
	return self;
}

- (Hex*) ctor:(Hex*)h
{
	_hex = [h address];
	return self;
}

//NOTE returns NSString
- (NSString*) hexnumberstring
{
	return [NSString stringWithFormat:@"%d",_hex];
}	

- (int) number {
	return _hex;
}

- (int) getNumber {
	return _hex;
}

- (Hex*) setNumber:(int)h
{
	_hex = h;
}

@end
