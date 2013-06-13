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

#ifndef _FORM_H_
#define _FORM_H_

#import <Foundation/Foundation.h>
#import "Error.h"
#import "Status.h"
@class ByteCodeMachine;

@interface Form : NSObject {
	NSMutableString *_formstring;
	Error *_errorobj;
	Status *_statusobj;

	struct machine { ByteCodeMachine *machine ; } _machine;
	
}

- (Form*)initWithString:(NSString*)s;
- (NSString*)string;
- (void)setString:(NSString*)s;

- (int)skipWhiteSpace:(NSString*)buffer atIndex:(int)idx;
- (int)skipWhiteSpaceBackwards:(NSString*)buffer atIndex:(int)idx;
//- (int)compile:(ByteCodeMachine*)machine withIndex:(int)index;
- (int)formatLisp;

- (void) addStatus:(int)s;//FIXME obj instead of int
- (void) addError:(int)e;

- (void) reverse;

@end

#endif
