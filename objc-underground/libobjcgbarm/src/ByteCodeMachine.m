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
- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2 andRegisterNumber:(int)rn {return -1; }
- (int)pushAssignment:(Hex*)hex {return -1;}
- (int)pushOperatorPlus:(Hex*)addr { return 1; }
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
- (int)pushIf:(Hex*)addr { return -1; }
- (int)pushElse:(Hex*)addr { return -1; }
- (int)pushPreviousLabel { return -1; }

- (int)generateFreeAddress {_freeaddycounter += 256*4; return _freeaddycounter;}
- (NSString*)generateFreeLabel {_freelabelcounter += 4; return [NSString stringWithFormat: @"label%@:",_freelabelcounter]; }
- (NSString*)getLatestLabel
{
	return [NSString stringWithFormat:@"label%@:", _freelabelcounter];
}

- (int)generateFreeRegisterNumber
{
	_freeregisternumber++;
	if (_freeregisternumber >= 32 && _freeregisternumber > 0)
		_freeregisternumber = -1;

	return _freeregisternumber;	
}
@end
