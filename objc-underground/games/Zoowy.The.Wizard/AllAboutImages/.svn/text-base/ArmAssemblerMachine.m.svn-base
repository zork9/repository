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

#import "ArmAssemblerMachine.h"

@implementation ArmAssemblerMachine

- (ArmAssemblerMachine*)ctor
{
	_type = HAVE_MACHINE_ARMASM;
	_freeaddycounter = 0;
	return self;
}

- (int)pushLoadSymbol:(Hex*)hex
{
	NSString *s = [NSString stringWithFormat:@"%@, #0x%@", @"ldr r0", [hex hexnumberstring]];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed load symbol with ldr r0, #0x%@",[hex hexnumberstring]);
	return 0;
}

- (int)pushLoadConstant:(Hex*)hex
{
	NSString *s = [NSString stringWithFormat:@"%@, =%@", @"ldr r0", [hex hexnumberstring]];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed load constant with ldr r0, =%@",[hex hexnumberstring]);
	return 0;
}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2
{
	NSString *s2 = [NSString stringWithFormat:@"%@, 0x%@", @"str r1", [hex hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@, =%@", @"ldr r1", [hex2 hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed definition with ldr r1, =%@ ; str r1,#0x%@ ; ",[hex2 hexnumberstring],[hex hexnumberstring]);
	return 0;
}

- (int)pushOperatorPlus:(Hex*)hex
{
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"add ", [hex hexnumberstring]];
	[_bytecode addObject: s];
	NSLOG3(@"arm assembler : pushed plus r1,=%@ and str r0,=%@",[hex hexnumberstring],[hex hexnumberstring]);
	return 0;
}

- (int)pushOperatorPlusConstant:(NSString*)val
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"add "];
	NSString *s = [NSString stringWithFormat:@"%@, =%@", @"ldr r1", val];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed plus constant ldr r1,=%@ and add r0,r0,r1", val);
	return 0;
}

- (int)pushOperatorPlusSymbol:(Hex*)hex
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"add "];
	NSString *s = [NSString stringWithFormat:@"%@, #0x%@", @"ldr r1", [hex hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed plus symbol ldr r1,#0x%@ and add r0,r0,r1", [hex hexnumberstring]);
	return 0;
}

- (int)pushOperatorMinusConstant:(NSString*)val
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"sub "];
	NSString *s = [NSString stringWithFormat:@"%@, =%@", @"ldr r1", val];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed minus constant ldr r1,=%@ and sub r0,r0,r1", val);
	return 0;
}

- (int)pushOperatorMinusSymbol:(Hex*)hex
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"sub "];
	NSString *s = [NSString stringWithFormat:@"%@, #0x%@", @"ldr r1", [hex hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed minus symbol ldr r1,#0x%@ and sub r0,r0,r1", [hex hexnumberstring]);
	return 0;
}

- (int)pushOperatorMulConstant:(NSString*)val
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"mul "];
	NSString *s = [NSString stringWithFormat:@"%@, =%@", @"ldr r1", val];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed multiply constant ldr r1,=%@ and mul r0,r0,r1", val);
	return 0;
}

- (int)pushOperatorMulSymbol:(Hex*)hex
{
	NSString *s2 = [NSString stringWithFormat:@"%@ r0,r0,r1", @"mul "];
	NSString *s = [NSString stringWithFormat:@"%@, #0x%@", @"ldr r1", [hex hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	NSLOG3(@"arm assembler : pushed multiply symbol ldr r1,#0x%@ and mul r0,r0,r1", [hex hexnumberstring]);
	return 0;
}

- (int)pushIf:(Hex*)hex
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"bne ", [self generateFreeLabel]];
	//NOTE major results are in r0 register (throughout this ArmAssemblerMachine.m file)
	NSString *s2 = [NSString stringWithFormat:@"%@", @"cmp r0,r1"];
	NSString *s3 = [NSString stringWithFormat:@"%@ #0x%@", @"ldr r1,", [hex hexnumberstring]];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed if ldr r1,#0x%@ ; cmp r0,r1 ; bne labelX", [hex hexnumberstring]);
	return 0;
}

- (int)pushIfConstant:(int)i
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"bne ", [self generateFreeLabel]];
	//NOTE major results are in r0 register (throughout this ArmAssemblerMachine.m file)
	NSString *s2 = [NSString stringWithFormat:@"%@", @"cmp r0,r1"];
	NSString *s3 = [NSString stringWithFormat:@"%@ =%d", @"ldr r1,", i];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	NSLOG3(@"arm assembler : pushed if constant ldr r1,=%d ; cmp r0,r1 ; bne label%d", i, _freelabelcounter);
	return 0;
}

- (int)pushIfDefaultRegister
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"bne ", [self generateFreeLabel]];
	//NOTE major results are in r0 register (throughout this ArmAssemblerMachine.m file)
	NSString *s2 = [NSString stringWithFormat:@"%@", @"cmp r0,r1"];
	NSString *s3 = [NSString stringWithFormat:@"%@", @"ldr r1,r0"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed if ldr r1,r0 ; cmp r0,r1 ; bne label%d",_freelabelcounter);
	return 0;
}

- (int)pushLoopDefaultRegister
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"bne ", [self generateFreeLabel]];
	//NOTE major results are in r0 register (throughout this ArmAssemblerMachine.m file)
	NSString *s2 = [NSString stringWithFormat:@"%@", @"cmp r0,r1"];
	NSString *s3 = [NSString stringWithFormat:@"%@", @"ldr r1,r0"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed loop condition ldr r1,r0 ; cmp r0,r1 ; bne label%d",_freelabelcounter);
	return 0;

}
- (int)pushLoopGoto:(NSString*)l
{

	NSString *s = [NSString stringWithFormat:@"goto %@", l];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed goto %@",l);
	return 0;

}

- (int)pushPreviousLabel
{

	NSString *s = [NSString stringWithFormat:@"label%d:",_freelabelcounter];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed previous label%d:",_freelabelcounter);
	return 0;
}

- (int)pushNewLabel
{

	NSString *s = [NSString stringWithFormat:@"label%@:",[self generateFreeLabel]];
	[_bytecode addObject: s];
	NSLOG2(@"arm assembler : pushed new label%d:",_freelabelcounter);
	return 0;
}

- (NSString*)getLastLabel 
{
	NSString *s = [NSString stringWithFormat:@"label%d:",_freelabelcounter];
	return s;
} 

@end
