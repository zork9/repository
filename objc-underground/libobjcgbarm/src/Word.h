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

#import <Cocoa/Cocoa.h>
#import "WordBase.h"
#import "TupleInt.h"

@interface Word : WordBase {
}

- (int)isElseClause;
- (int)isWhile;
- (int)isWhileClause;
- (int)isIf;
- (int)isIfClause;
- (int)isElse;
- (int)isOpeningBrace;
- (int)isClosingBrace;

- (TupleInt*)skipWhiteSpace:(NSString*)word withIndex:(int)idx;

@end
