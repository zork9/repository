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

	int i = 0;
	//init all regs as empty
	while (i < 32) 
		[_registernumbers addObject: 0];

	return self;
}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"str r0,=", [hex hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"mov r0,", [hex2 hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2 andRegisterNumber:(int)rn
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@ %@ %@", @"str r",rn,",=", [hex hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"mov r0,", [hex2 hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushAssignment:(Hex*)hex with:(Hex*)hex2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"str r0,=", [hex2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"mov r0,", [hex hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushOperatorPlus:(Hex*)addr
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"add r0,r0,r1", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}


- (int)pushOperatorMinus:(Hex*)addr
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"sub r0,r0,r1", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushOperatorPlusPlus:(Hex*)addr
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"add r0,r1,1", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ldr r1,="];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushOperatorMinusMinus:(Hex*)addr
{
	//lda reg
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"sub r0,r1,1", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ldr r1,="];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushOperatorPlusAssign:(Hex*)addr andAddress:(Hex*)addr2
{
	NSString *s3 = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"ldr r2,=", [addr2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"add r0,r1,r2"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorMinusAssign:(Hex*)addr andAddress:(Hex*)addr2
{
	NSString *s3 = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"ldr r2,=", [addr2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"sub r0,r1,r2"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorOr:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"orr ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseOr:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"orr ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseExclusiveOr:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"eor ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseAnd:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"and ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseOrAssign:(Hex*)addr andAddress:(Hex*)addr2
{

	NSString *s3 = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"ldr r2,=", [addr2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"orr r0,r1,r2"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];

	return 0;
}

- (int)pushOperatorBitwiseExclusiveOrAssign:(int)addr andAddress:(int)addr2
{

	NSString *s3 = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"ldr r2,=", [addr2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"eor r0,r1,r2"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorAnd:(int)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"and ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseAndAssign:(int)addr andAddress:(int)addr2
{

	NSString *s3 = [NSString stringWithFormat:@"%@ %@", @"ldr r1,=", [addr hexnumberstring]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"ldr r2,=", [addr2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"eor r0,r1,r2"];
	[_bytecode addObject: s3];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushIf:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"beq ", [self generateLabel]];
	NSString *s2 = [NSString stringWithFormat:@"%@ r0, %@", @"cmp ", [addr hexnumberstring]];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushElse:(Hex*)addr
{

	NSString *s2 = [NSString stringWithFormat:@"blt label%@:", _freelabelcounter];//if before jump over else clause, FIXME bcc ?
	NSString *s = [NSString stringWithFormat:@"label%@:", [self generateLabel]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;

}

- (int)pushWhile:(Hex*)addr
{

	NSString *s2 = [NSString stringWithFormat:@"blt label%@", _freelabelcounter];//branch after while block code, FIXME bcc ?
	NSString *s = [NSString stringWithFormat:@"label%@:", [self generateLabel]];//loop; label
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;

}

- (int)pushPreviousLabel
{

	NSString *s = [NSString stringWithFormat:@"label%@:",_freelabelcounter];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushNewLabel
{

	NSString *s = [NSString stringWithFormat:@"label%@:",[self generateFreeLabel]];
	[_bytecode addObject: s];
	return 0;
}



- (int)pushBranch:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"blt label%@",_freelabelcounter];//FIXME bcc
	[_bytecode addObject: s];
	return 0;
}

- (int)generateFreeRegisterNumber
{

	int i = 0;
	while ( i < 32) {
		if ([_registernumbers objectAtIndex:i] == 0)
			return i;
	}

	return -1;
}
@end
