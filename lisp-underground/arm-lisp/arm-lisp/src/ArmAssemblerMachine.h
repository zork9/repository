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

#import <Foundation/Foundation.h>
#import "ByteCodeMachine.h"
#import "Hex.h"

@interface ArmAssemblerMachine : ByteCodeMachine {

}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2;
- (int)pushOperatorPlusConstant:(NSString*)val;
- (int)pushOperatorPlusSymbol:(Hex*)addr;
- (int)pushOperatorMinusConstant:(NSString*)val;
- (int)pushOperatorMinusSymbol:(Hex*)addr;
- (int)pushOperatorMulConstant:(NSString*)val;
- (int)pushOperatorMulSymbol:(Hex*)addr;
- (int)pushIf:(Hex*)hex;
- (int)pushLoopDefaultRegister;

@end
