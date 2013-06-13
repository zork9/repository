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
#import "Hex.h"
typedef int MACHINETYPE;

enum {
	HAVE_MACHINE_JAVA = 2,
	HAVE_MACHINE_ARMASM = 3,
	HAVE_MACHINE_6502ASM = 4,
	HAVE_MACHINE_ARMBYTE = 5,
	HAVE_MACHINE_6502BYTE = 6,
};

@interface ByteCodeMachine : NSObject {

	int _type;
	NSMutableArray* _bytecode;//strings
	int _freeaddycounter;//for storing variables
	int _freelabelcounter;
	int _freeregisternumber;
}

- (int)type;
- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2;
- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2 andRegisterNumber:(int)rn;
- (int)pushAssignment:(Hex*)hex with:(Hex*)hex2;
- (int)pushOperatorPlus:(Hex*)addr;
- (int)pushOperatorPlusPlus:(Hex*)addr;
- (int)pushOperatorPlusAssign:(Hex*)addr andAddress:(Hex*)addr2;
- (int)pushOperatorMinus:(Hex*)addr;
- (int)pushOperatorMinusMinus:(Hex*)addr;
- (int)pushOperatorMinusAssign:(Hex*)addr andAddress:(Hex*)addr2;
- (int)pushOperatorOr:(Hex*)addr;
- (int)pushOperatorBitwiseOr:(Hex*)addr;
- (int)pushOperatorAnd:(Hex*)addr;
- (int)pushOperatorBitwiseAnd:(Hex*)addr;
- (int)pushWhile:(Hex*)addr;
- (int)pushIf:(Hex*)addr;
- (int)pushElse:(Hex*)addr;
- (int)pushPreviousLabel;
- (int)pushNewLabel;

- (int)generateFreeAddress;
- (NSString*)generateFreeLabel;
- (NSString*)getLatestLabel;
- (int)generateFreeRegisterNumber;
@end
