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

// NOTE put the word as a int in the back, little endian
- (Hex*) ctorString:(NSString*)word
{
	int i = [word length];
	char c = [word characterAtIndex: i];
	
	while (i-- < [word length])
		memcpy(&_hex-i+1+[word length],&c,1);

	return self;
}

- (Hex*) ctorInt:(int)word
{
	_hex = word;
	return self;
}

- (Hex*) ctor:(int)word
{
	_hex = word;
	return self;
}

//NOTE returns NSString
- (NSString*) hexnumberstring
{
	char buf[1024];
	sprintf(buf, "%X",_hex);
	return [NSString stringWithFormat:@"%@",buf];
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
