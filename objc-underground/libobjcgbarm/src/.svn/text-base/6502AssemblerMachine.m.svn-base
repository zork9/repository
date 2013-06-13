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

#import "6502AssemblerMachine.h"

@implementation NesAssemblerMachine

- (NesAssemblerMachine*)ctor
{
	_type = HAVE_MACHINE_6502ASM;
	_freeaddycounter = 0;
	return self;
}

- (int)pushDefinition:(Hex*)hex with:(Hex*)hex2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"sta ", [hex hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"lda ", [hex2 hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushAssignment:(Hex*)hex with:(Hex*)hex2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"sta ", [hex2 hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"lda ", [hex hexnumberstring]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;
}

- (int)pushOperatorPlus:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"adc ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;
}


- (int)pushOperatorMinus:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"sbc ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorPlusPlus:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"inc ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorMinusMinus:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"dec ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorPlusAssign:(Hex*)addr andAddress:(Hex*)addr2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"lda ", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"adc ", [addr2 hexnumberstring]];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorMinusAssign:(Hex*)addr andAddress:(Hex*)addr2
{
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"lda ", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"sbc ", [addr2 hexnumberstring]];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;
}

- (int)pushOperatorOr:(Hex*)addr
{
	//lda reg
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ora ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseOr:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ora ", [addr hexnumberstring]];
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

	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"lda ", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"ora ", [addr2 hexnumberstring]];//FIXME ORA ?
	[_bytecode addObject: s2];
	[_bytecode addObject: s];

}

- (int)pushOperatorBitwiseExclusiveOrAssign:(int)addr andAddress:(int)addr2
{

	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"lda ", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"eor ", [addr2 hexnumberstring]];//FIXME ORA ?
	[_bytecode addObject: s2];
	[_bytecode addObject: s];

}

- (int)pushOperatorAnd:(int)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"and ", [addr hexnumberstring]];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushOperatorBitwiseAndAssign:(int)addr andAddress:(int)addr2
{

	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"lda ", [addr hexnumberstring]];
	NSString *s = [NSString stringWithFormat:@"%@ %@", @"and ", [addr2 hexnumberstring]];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushIf:(Hex*)addr
{

	NSString *s = [NSString stringWithFormat:@"%@ %@", @"bne ", [self generateLabel]];
	NSString *s2 = [NSString stringWithFormat:@"%@ %@", @"cmp ", [addr hexnumberstring]];
	[_bytecode addObject: s2];
	[_bytecode addObject: s];
	return 0;

}

- (int)pushElse:(Hex*)addr
{

	NSString *s2 = [NSString stringWithFormat:@"bcc label%@:", _freelabelcounter];//if before jump over else clause, FIXME bcc ?
	NSString *s = [NSString stringWithFormat:@"label%@:", [self generateLabel]];
	[_bytecode addObject: s];
	[_bytecode addObject: s2];
	return 0;

}

- (int)pushWhile:(Hex*)addr
{

	NSString *s2 = [NSString stringWithFormat:@"bcc label%@", _freelabelcounter];//branch after while block code, FIXME bcc ?
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

	NSString *s = [NSString stringWithFormat:@"bcc label%@",_freelabelcounter];//FIXME bcc
	[_bytecode addObject: s];
	return 0;
}

@end
