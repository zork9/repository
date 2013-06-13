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


#import "Form.h"
#import "TupleIterator.h"

@implementation Form

- (Form*)initWithString:(NSString*)fs
{
	_formstring = [[NSMutableString alloc] initWithString:@""];
	[_formstring appendFormat:@"%@",fs];
	//_formstring = fs;
	//printf("formstring = %s\n", [fs UTF8String]);
	if ([self formatLisp] < 0)
		return nil;

	return self;
}

- (NSString*)string
{
	return _formstring;
}
- (void)setString:(NSString*)s
{
	_formstring = s;
}

/*
 * Lisp Form Compilation methods
 */ 
/*- (int)compile:(ByteCodeMachine*)machine
{
	_machine.machine = machine;

	[self formatLisp];

	return 0;
}
*/
/*
 * Lisp Form Internal Compilation methods
 */

- (int)skipWhiteSpace:(NSString*)buffer atIndex:(int)idx
{
	while ([buffer characterAtIndex:idx] == ' ' ||
		[buffer characterAtIndex:idx] == '\t')
		idx++;

	return idx;
}

- (int)skipWhiteSpaceBackwards:(NSString*)buffer atIndex:(int)idx
{
	while ([buffer characterAtIndex:idx] == ' ' ||
		[buffer characterAtIndex:idx] == '\t')
		idx--;

	return idx;
}

// NOTE form is reversed string !
//TODO better catenation
- (int)formatLisp
{
	//do not format if there are no parenses
	if ([self isForm] < 0)
		return 0;

	if (_formstring == nil)
		return -1;

	if ([_formstring length] <= 0)
		return -1;

	NSMutableString *returnbuffer1 = [[NSMutableString alloc] initWithString:@""];
	NSMutableString *returnbuffer2 = [[NSMutableString alloc] initWithString:@""];
	int idx = [_formstring length]-1;
	while (idx >= 0) {//NOTE idx<0 gives truth for character index access in NSString _formstring	
		//NSString *st;
		//st = [NSString stringWithFormat:"st=%@",idx];
		//NSLog(st);
		if ([_formstring characterAtIndex:idx] == '(') {
			idx = [self skipWhiteSpaceBackwards:_formstring atIndex:idx];
		}
		[returnbuffer1 appendFormat:@"%c",[_formstring characterAtIndex:idx]];
		//returnbuffer1 += [_formstring characterAtIndex:idx];
		idx--;
	}
	idx = [returnbuffer1 length]-1;
	while (idx >= 0) {
		if ([returnbuffer1 characterAtIndex:idx] == ')') {
			idx = [self skipWhiteSpaceBackwards:returnbuffer1 atIndex:idx];
		}
		[returnbuffer2 appendFormat:@"%c",[returnbuffer1 characterAtIndex:idx]];
		//returnbuffer2 += [returnbuffer1 characterAtIndex:idx];
		idx--;
	}

	_formstring = returnbuffer2;
	return 0;
} 

- (void) addStatus:(int)s {
	
	[_statusobj addStatus:s ];

}

- (void) addError:(int)e {
	
	[_errorobj addError:e ];
	
}

- (void) reverse
{
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	[s appendFormat:@"%@",_formstring];
	NSMutableString *rets = [[NSMutableString alloc] initWithString:@""];
	int idx = [s length]-1;
	while (idx >= 0) {
		[rets appendFormat:@"%c",[s characterAtIndex:idx]];
		idx--;
	}

	_formstring = (NSString*)rets;
}

- (int)isForm
{
	//coolness : a word is short in length,
	// a form always has index:0 as a parens,
	//thus this returns after 1 loop :-)
	int i = 0;
	while (i < [_formstring length]) {//TODO maybe check for format
		if ([_formstring characterAtIndex:i] == '(')
			return 0;
		i++;
	}
	NSLOG2(@"LOOP=%d",i);
	return -1;
}

@end
