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
#import "ByteCodeMachine.h"
#import "Hex.h"

@interface NesAssemblerMachine : ByteCodeMachine {

}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2;
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
- (int)pushIf:(Hex*)addr;
- (int)pushElse:(Hex*)addr;
- (int)pushLatestLabel;

@end
