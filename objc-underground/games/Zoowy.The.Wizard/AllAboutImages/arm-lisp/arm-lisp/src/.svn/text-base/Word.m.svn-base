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

#import "Word.h"
#import "TupleInt.h"

//TODO substring
@implementation Word

- (int)isWhile
{
	return [self isWord:@"while"];	
}

- (int)isIf
{
	return [self isWord:@"if"];	
}

- (int)isParensDefun
{
	return [self isWord:@"(defun"];	
}

- (int)isParensLoop
{
	return [self isWord:@"(loop"];	
}

- (int)isParensIf
{
	return [self isWord:@"(if"];	
}

- (int)isElse
{
	return [self isWord:@"else"];	
}

- (int)isOpeningBrace
{
	return [self isWord:@"{"];	
}

- (int)isClosingBrace
{
	return [self isWord:@"}"];	
}

- (int)isElseClause
{

	TupleInt *ti = [self skipWhiteSpace:_word withIndex:0];
	int idx = [ti first];
	int idx2;
	if ([_word characterAtIndex:idx++] == '}') {

		if ([_word characterAtIndex:idx] == ' ') {
			ti = [self skipWhiteSpace:_word withIndex:idx];
		}
		if ((ti = [self subString:@"else"]) && [ti first] >= 0) {

			if (ti = [[ti second] subString:@"{"] || [ti first] >= [_word length])
				return 0;

		} 	 
	}	
	return -1;
}

- (int)isWhileClause
{

	TupleInt *ti = [self skipWhiteSpace:_word withIndex:0];
	int idx = [ti first];
	if ((ti = [_word subString:@"while"]) && [ti first] > 0) {

		if (((ti = [[ti second] subString:@"("]) || [ti first] > idx) && [ti first] < [_word length])
			return 0;

	}	
	return -1;
}

- (int)isIfClause
{

	TupleInt *ti = [self skipWhiteSpace:_word withIndex:0];
	int idx = [ti first];
	if ((ti = [self subString:@"(if"]) && [ti first] > 0)
			return 0;
	return -1;
}

- (TupleInt*)subString:(NSString*)s
{
	int idx = 0;
	for ( ; idx < [_word length] ; ) {
		int r2 = 0;
		for ( ; [_word characterAtIndex:idx] == [s characterAtIndex: r2] ; ) {
			if (r2 >= [s length]-1) {
				idx++;
				NSString *s2 = [[NSString alloc] initWithString:s];
				for ( ; idx < [_word length]; ) {//concat rest of word 
					s2 += [_word characterAtIndex:idx];
					idx++;
				}
				
				return [[TupleInt new] addFirstInt:idx andSecond:[[NSString alloc] initWithString: s2]];
			}
			r2++;
			idx++;
		}
		idx++;	
	}
	return [[TupleInt new] addFirstInt:-1 andSecond:@""];
}

- (TupleInt*)skipWhiteSpace:(NSString*)word withIndex:(int)idx
{
	NSString *s = @"";
	while (idx < [word length]) {
		char c = [word characterAtIndex:idx++];
		if (c == ' ' || c == '\t')
			;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

@end
