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

#import "ByteCodeMachine.h"

@implementation ByteCodeMachine

- (int) type
{
	return _type;
}

- (int)pushDefinition:(Hex*)hex {return -1;}
- (int)pushAssignment:(Hex*)hex {return -1;}
- (int)pushOperatorPlus:(Hex*)addr { return 1; }
- (int)pushOperatorPlusConstant:(NSString*)addr { return 1; }
- (int)pushOperatorPlusSymbol:(Hex*)hex { return -1; }
- (int)pushOperatorMinusConstant:(NSString*)addr { return 1; }
- (int)pushOperatorMinusSymbol:(Hex*)hex { return -1; }
- (int)pushOperatorPlusPlus:(Hex*)addr { return -1; }
- (int)pushOperatorPlusAssign:(Hex*)addr { return -1; }
- (int)pushOperatorMinus:(Hex*)addr { return -1; }
- (int)pushOperatorMinusMinus:(Hex*)addr { return -1; }
- (int)pushOperatorMinusAssign:(Hex*)addr { return -1; }
- (int)pushOperatorOr:(Hex*)addr { return -1; }
- (int)pushOperatorBitwiseOr:(Hex*)addr { return -1; }
- (int)pushOperatorExclusiveOr:(Hex*)addr { return -1; }
- (int)pushOperatorBitwiseExclusiveOr:(Hex*)addr { return -1; }
- (int)pushWhile:(Hex*)addr { return -1; }
- (int)pushLoopDefaultRegister { return -1; }
- (int)pushLoopGoto:(NSString*)l { return -1; }
- (int)pushReturnFromLinkedBranch { return -1; }
- (int)pushIf:(Hex*)addr { return -1; }
- (int)pushLoadSymbol:(Hex*)hex { return -1; }
- (int)pushLoadConstant:(Hex*)hex { return -1; }
- (int)pushIfConstant:(int)addr { return -1; }
- (int)pushIfDefaultRegister { return -1; }
- (int)pushElse:(Hex*)addr { return -1; }
- (int)pushPreviousLabel { return -1; }
- (int)pushNewLabel { return -1; }
- (int)pushNewLabel:(NSString*)l { return -1; }
- (int)getLastLabel { return -1; }
- (int)generateFreeAddress {_freeaddycounter += 256*4; return _freeaddycounter;}
- (NSString*)generateFreeLabel {_freelabelcounter += 4; 
				NSMutableString *rs = [[NSMutableString alloc] initWithString:@"label"];
				[rs appendFormat: @"%d",_freelabelcounter];
				return rs; }
@end
