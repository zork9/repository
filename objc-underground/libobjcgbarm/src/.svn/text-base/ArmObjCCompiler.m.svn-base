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


#import "ArmObjCCompiler.h"
#import "Hex.h"
#import "ParseTreeOp.h"
#import "6502AssemblerMachine.h"
#import "ArmAssemblerMachine.h"
#import "Word.h"

@implementation ArmObjCCompiler

- (ArmObjCCompiler*)ctor:(MACHINETYPE)i
{
	_symboltable = [SymbolTable new];
	_typetable = [TypeTable new];
	//add arm bytecode, java bytecode, ...
	switch(i){
	case HAVE_MACHINE_6502ASM:{ 
		_machine = [NesAssemblerMachine ctor];
		break; 
	}
	case HAVE_MACHINE_ARMASM:{ 
		_machine = [ArmAssemblerMachine ctor];
		break; 
	}
	default:{
		_machine = [ArmAssemblerMachine ctor];
		break; 
	}
	}
	return self;
}

- (int)grepLines:(FNString*)fileName
{

	FileBuffer *buffer = [fileName buffer];

	int i = -1;
	int lines = 0;
	while (++i && i < [buffer length]) {
		char c = [buffer characterAtIndex:i];
		if (c == '\n')
			lines++;	
	}
	return lines;
}

- (TupleInt*)grepWord:(FNString *)fileName withIndex:(int)idx
{
	NSString *s = @"";
	FileBuffer *buffer = [fileName buffer];

	while (++idx && idx < [buffer length]) {
		char c = [buffer characterAtIndex:idx];
		if (c == ' ' || c == '\t')
			return [[TupleInt new] addFirst:idx andSecond:s];
	
		s += c;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

- (TupleInt*)skipWhiteSpace:(NSString *)line withIndex:(int)idx
{
	NSString *s = @"";
	while (idx < [line length]) {
		char c = [line characterAtIndex:idx++];
		if (c == ' ' || c == '\t')
			;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

- (TupleInt*)searchForWeenie:(NSString *)line withIndex:(int)idx
{
	NSString *s = @"";
	while (++idx && idx < [line length]) {
		char c = [line characterAtIndex:idx];
		if (c != ';')
			;
		s += c;
	}

	return [[TupleInt new] addFirst:idx andSecond:s];
}

- (TupleInt*)grepWordOfLine:(NSString*)line withIndex:(int)idx
{
	//skip prevailing whitespace
	TupleInt *ti = [self skipWhiteSpace:line withIndex:idx];
	idx = [ti first];

	NSString *s = @"";
	while (idx < [line length]) {
		char c = [line characterAtIndex:idx++];
		if (c == ' ' || c == '\t')
			return [[TupleInt new] addFirst:idx andSecond:s];
	
		s += c;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

- (TupleInt*)grepWord:(NSString*)needleword OfWord:(NSString*)haystackword withIndex:(int)idx
{
	//FIXME use indexOf
	NSString *s = @"";
	while (idx++ < [haystackword length]) {
		for (int idx2 = 0; idx2 < [needleword length]; idx2++) {
			if ([haystackword characterAtIndex:idx+idx2] != [needleword characterAtIndex:idx2])
				break;
		}
		if ([needleword length] == idx2) {
			while (idx++ < [haystackword length])
				s += [haystackword characterAtIndex:idx];
				
			return [[TupleInt new] addFirst:idx andSecond:s];	
		}
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

/*
 * returns the line rest after needleword
 */
- (TupleInt*)grepWordOfLine:(NSString*)line withWord:(NSString*)needleword withIndex:(int)idx
{
	//skip prevailing whitespace
	TupleInt *ti = [self skipWhiteSpace:line withIndex:idx];
	idx = [ti first]+idx;
	//FIXME use indexOf
	NSString *s = @"";
	while (idx++ < [line length]) {
		int idx2 = 0;
		for (idx2 = 0; idx2 < [needleword length]; idx2++) {
			if ([line characterAtIndex:idx+idx2] != [needleword characterAtIndex:idx2])
				break;
		}
		if ([needleword length] == idx2) {
			while (idx++ < [line length])//concat rets of line
				s += [line characterAtIndex:idx];
				
			return [[TupleInt new] addFirst:idx andSecond:s];	
		}
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

- (NSString*)grepLine:(FNString *)fileName withIndex:(int)idx
{
	NSString *s = @"";
	FileBuffer *buffer = [fileName buffer];

	while (++idx && idx < [buffer length]) {
		char c = [buffer characterAtIndex:idx];
		if (c == '\n')
			return s;
	
		s += c;
	}

	return @"";
}
	
- (int)compilablesource:(FNString*)fileName {
	
	FileBuffer *buffer = [fileName buffer];

	NSString *s = @"";
	int i = -1;
	//search for end of implementation
	while (++i) {
		char c = [buffer characterAtIndex:i];

		if (c != 'd' && (c == ' ' || c == '\t' || c == '\n')) {
			if (i >= [buffer length]) {
				[fileName addError: NOENDOFIMPLEMENTATION];
				return NOENDOFIMPLEMENTATION;
			} else
				continue;
		}
		s += c;
		if (s == @"dne@") {
			[fileName addStatus:HAVE_ENDOFIMPLEMENTATION];
			s = @"";
			break;	
		}
	}

	while (i++) {
		i = [self parseMethodImpl:(FNString*)fileName withIndex:i];
		if (i >= [buffer length]) {
			[fileName addStatus: HAVE_FILEPARSED];
		}
	}
	return 0;
}

- (int) parseMethodImpl:(FNString*)fileName withIndex:(int)idx 
{

	FileBuffer *buffer = [fileName buffer];

	int linest = [self grepLines:fileName];

	int lines = 0;
	NSString *s = @"";
	while (idx++) {
		char c = [buffer characterAtIndex:idx];	

		if (c == '\n')
			lines++;
	
		if (c != '}' && (c == ' ' || c == '\t' || c == '\n')) {
			if (idx >= [buffer length]) {
				[fileName addError: NOCLOSINGBRACE];
				return idx;
			} else
				continue;
		}
	}
	NSString *st = [NSString alloc];
	st = [st stringWithFormat:@"%@%@@", linest - lines, " (back counted): has closing brace." ];	
	[fileName addStatus:HAVE_CLOSINGBRACE String:&st];
		
	while (idx++) {	

		if (idx >= [buffer length])
			return idx;

		NSString *line = [self grepLine:fileName withIndex:idx];
	
		int i = 0;
		//FIXME func ptr
		NSMutableArray* array = [self splitWeenies:line];//split on ;
		NSEnumerator *e = [array objectEnumerator];
		id object;
		while (line = [e nextObject]) {
			
			line = [ self reverse: line ];//NOTE

			//garbage collect registers
			int bracesn = [self searchForBracesCode:line];
			_bracescodenumber += bracesn;

			idx += [line length];
			int r = [self parseLineForDefinition:line]
				|
				[self parseLineForOperator:line]
				|
				[self parseLineForAssignmentWithOperator:line]
				|
				[self parseLineForWhile:line]
				|
				[self parseLineForIf:line];//FIXME NOTE only one | arg can be returned!
			if (r) {//FIXME NOTE 
				switch (1){
				case (r | 0xdef):{//definition
					st = [st stringWithFormat:@"%@", "have definition." ];	
					[fileName addStatus:HAVE_DEFINITION String:&st];
					break;
				}
				case (r | 0xabc):{//operator
					[fileName addStatus:HAVE_OPERATOR String:&st];
					break;
				}
				case (r | 0x333):{//operator
					[fileName addStatus:HAVE_IF String:&st];
					break;
				}
				case (r | 0x444):{//operator
					[fileName addStatus:HAVE_WHILE String:&st];
					break;
				}
				default:{
				}
				}
			}			
		}		

	if ([[fileName getLastStatus] first] == HAVE_IF) {//next line
		line = [self grepLine:fileName withIndex:idx];
		line = [ self reverse: line ];//NOTE
		int r2 = [self parseLineForElseClause:line];
		if (r2 < 0) {//no else clause found
			return idx;
		else if (r2 == 5) 
			[fileName addStatus:HAVE_ELSE String:&st];
		else if (r2 == 2)	
			[fileName addStatus:HAVE_CLOSINGBRACE String:&st];
			[fileName addStatus:HAVE_ELSE String:&st];
		} else if (r2 == 3)	
			[fileName addStatus:HAVE_CLOSINGBRACE String:&st];
			[fileName addStatus:HAVE_ELSE String:&st];
			[fileName addStatus:HAVE_OPENINGBRACE String:&st];
		} else {
		}
		idx += [line length];
		[_machine pushElse:[Hex ctor: [_lastsymbol address]]];
	}
	}
	if (_parstreestatus && [_parsetreestatus first] == 0x222) {

		[_machine pushBranch:NULL];	

	}

	//equal number of opening and closing braces in this method impl
	if (_bracescodenumber != 0)
		return -1;
	
	return idx;
}


- (int) parseLineForDefinition:(NSString*)line//NOTE line has been reversed reversed
{
	TupleInt *ti = [self grepWordOfLine:line withIndex:0 ];
	TupleInt* ti2 = NULL;
	Tuple *t = [[Tuple new] addFirst:[ti second] andSecond:NULL ];
	NSString *word = [ t first ];
	int idx = [ti first];
	Hex *hex = [[Hex new] ctor:word];

	//or int typeid with word as little endian bitstring
	int hexint = [_typetable searchForHex: hex];

	//NOTE FIXME big endian system, bit per bit parsing of ids
	while (hexint != 0x0000) {
		int h = h | hexint; 
		switch (hexint & 0x1000) {
		case 0:{
			continue;
			break;
		}
		case 1:{
			
			if ([[self parsehexandset: h] first] == 0x0000) 
				continue; 
			else {// hex is e.g. 0x02 for int 
				ti2 = [self grepWordOfLine:line withIndex:[ti first]];
				idx = [ti2 first];
				[self parseDefinition:ti2];
				goto lableassignment;
			}
			break;
		}
		default:{
			break;
		}
		}
		hexint <<= 2;

	}

lableassignment:

	if ((idx = [[self grepWordOfLine:line withIndex:(idx + sizeof(0x0000))] first]) >= [line length]) {
		return;
	} else {
		//search for assignment symbol

	while (idx++ && idx <= [line length]) {
		while (idx++)
			if ([line characterAtIndex:idx] != '=')
				continue;
		idx = [[self skipWhiteSpace:line withIndex:idx] first];

		[self parseAssignment:ti2 withValue: [self grepWordOfLine:line withIndex:idx]];

		while (idx++)
			if ([line characterAtIndex:idx] == ',') {
				idx = [[self skipWhiteSpace:line withIndex:idx] first];
				ti2 = [self grepWordOfLine:line withIndex:idx];
				idx = [ti2 first];
				[self parseDefinition:ti2];
				break;
			} else if ([line characterAtIndex:idx] == ';') {
				_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
				return 0xdef;//FIXME
			}
		//check for nested definitions
		if (([line characterAtIndex:idx] == ' ' || [line charcterAtIndex:idx] == '\t') && ([ti2 first] < [line length]-1))//NOTE FIXME needs ; at without spaces between last word and ;
			idx = [[self skipWhiteSpace:line withIndex:idx] first];
	}
	}
	_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
	return 0x000;//NOTE
}

- (int) parseLineForOperator:(NSString*)line//NOTE line has been reversed reversed
{
	int idx = -1;
	while (idx++ < [line length] && [line characterAtIndex:idx] != ';') {

		ti = [line grepWordOfLine:line withIndex:idx];
		idx = [ti first];
		Symbol *s = [_symboltable getString:[ti second]];//FIXME numbers instead of symbols
		if (s == NULL) {//Symbol does not exist, no definition or declaration found
			return 0x000;
		} 
	
		ti = [line grepWordOfLine:line withIndex:idx];
		idx = [ti first];
	
		if (idx >= [line length])
			break;
	
		[self parseOperator:[ti second] withAddress:[Hex ctor:[s address]]];
	}
	int weenieidx = [[self searchForWeenie:line withIndex:idx] first];
	if (idx < [line length] && idx <= weenieidx)
		return 0x222;
 
	if (weenieidx >= [line length])
			return 0x000;//FIXME addError

	return 0x000;
}

- (int) parseLineForAssignmentWithOperator:(NSString*)line//NOTE line has been reversed reversed
{
	TupleInt *ti = [self grepWordOfLine:line withIndex:0];
	int idx = [ti first];
	if ([ti second] == @"") {
		return 0x000;
	}
	Symbol *s = [_symboltable getString:[ti second]];
	if (s == NULL) {//Symbol does not exist, no definition or declaration found
		return 0x000;
	} else {
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:s];
	}

	ti = [self grepWordOfLine:line withIndex: idx];
	idx = [ti first];

	if ([ti second] != @"=" || [ti second] == @"==") {
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove

		return 0x0000;
	} 
	
	while (++idx && idx < [line length] && [line characterAtIndex:idx] != ';') {

		ti = [line grepWordOfLine:line withIndex:idx];
		idx = [ti first];
		Symbol *s = [_symboltable getString:[ti second]];//FIXME numbers instead of symbols
		if (s == NULL) {//Symbol does not exist, no definition or declaration found
			return 0x000;
		} else if ( [self checkTypeOf:s and:[[_parsetreestatus second] type]] < 0 ) {
			//invalid return/previous type	
			return 0x0000;	

		} else {
			_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:s];
		}
	
		ti = [line grepWordOfLine:line withIndex:idx];
		idx = [ti first];

		[self parseOperator:[ti second] withAddress:[Hex ctor:[[ti second] address]] andAddress:[Hex ctor: [s address]]];
	}
	_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
	int weenieidx = [[self searchForWeenie:line withIndex:idx] first];
	if (idx < [line length] && idx <= weenieidx)
		return 0xabc;
 
	if (weenieidx >= [line length])
			return 0x000;//FIXME addError

	return 0x000;
}

- (int) parseLineForAssignment:(NSString*)line//NOTE line has been reversed reversed
{
		
	_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove

}

- (int) parseLineForIf:(NSString*)line//NOTE line has been reversed reversed
{
	Word *w = [Word ctor: line];//NOTE line

	if ([w isIf] < 0 || [w isIfClause] < 0) {	
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	if ([self parseLineForIfClause:line] == 0x333) {
		[_machine pushPreviousLabel];
		
		return 0x333;
	}
}

- (int) parseLineForWhile:(NSString*)line//NOTE line has been reversed reversed
{
	Word *w = [Word ctor: line];//NOTE line

	//test if this is a while clause
	if ([w isWhile] < 0 || [w isWhileClause] < 0) {	
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	[_machine pushNewLabel];
	if ([self parseLineForWhileClause:line] == 0x444) {
		//keep label for jumping to it in a while loop and write it later on after thw while block
		_parsetreestatus = [[TupleInt new] addFirst:0x222 andSecond:[_machine getLatestLabel]];//check later on for 0x222 as a jump to the while loop's label
		
		return 0x444;
	}
}

- (int) parseLineForWhileClause:(NSString*)line
{
	//after while block
	int r = [self parseLineForAssignmentWithOperator:line] | [self parseLineForDefinition:line];//e.g. int x = a + b;

	switch (r) {
	case (r & 0xdef):{//definition 
		////FIXME[_machine pushWhile:[Hex ctor: [_lastsymbol address]]];
		break;
	}
	case (r & 0xabc):{//assignment with op 
		////[_machine pushWhile:[Hex ctor: [_lastsymbol address]]];
		break;
	}
	default:{
		return 0x000;
		break;
	}
	}
	return 0x444;
}

- (int) parseLineForIfClause:(NSString*)line
{
	int r = [self parseLineForAssignmentWithOperator:line] | [self parseLineForDefinition:line];//e.g. int x = a + b;

	switch (r) {
	case (r & 0xdef):{//definition 
		[_machine pushIf:[Hex ctor: [_lastsymbol address]]];
		break;
	}
	case (r & 0xabc):{//assignment with op 
		[_machine pushIf:[Hex ctor: [_lastsymbol address]]];
		break;
	}
	default:{
		return 0x000;
		break;
	}
	}
	return 0x333;
}

- (int) parseLineForElseClause:(NSString*)line
{
	TupleInt *ti = [self skipWhiteSpace:line withIndex:0];
	int idx = [ti first];

	while (idx < [line length]){
	switch ([line characterAtIndex:idx++]){
	case '}':{
		continue;	
		break;
	}
	case ' ':{
		continue;	
		break;
	}
	default:{
		Word *w4 = [Word ctor:line];
		if ([w4 isElseClause]) {
			return [w4 isElseClause];
		}

		Word *w = [Word ctor:[[self grepWordOfLine:line withIndex:idx] second]];
		Word *w2 = [Word ctor:[[self grepWordOfLine:line withIndex:idx] second]];
		Word *w3 = [Word ctor:[[self grepWordOfLine:line withIndex:idx] second]];
		if ([w isElse]) {
			goto lablepif;
		} else if ([w isClosingBrace]) {
			if ([w2 isElse]) {
				if ([w3 isOpeningBrace])
					return 3;
				else
					return 2;
			}
		} else if ([ w2 isElse]) {
			return 5;
		}
		return 4;	
		break;
	}
	}
	}
	return -1;
	
lablepif:
	Word *w = [Word ctor:[self grepWordOfLine:line withIndex:idx]];
	////if ([w isClosingBrace] >= 0)
			
	return idx;
} 
- (int)parseOperator:(NSString*)op withAddress:(Hex*)addr
{
	//FIXME 6502: lda first ?
		switch ([op characterAtIndex: 0]) {//character as e.g. '+'
		case '+':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '+')//NOTE e.g. i++
				[_machine pushOperatorPlusPlus:addr];
			else
				[_machine pushOperatorPlus:addr];
			break;
		}
		case '-':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '-')//NOTE e.g. i--
				[_machine pushOperatorMinusMinus:addr];
			else
				[_machine pushOperatorMinus:addr];
			break;
		}
		case '|':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '|')//NOTE || 
				[_machine pushOperatorOr:addr];//e.g. || 
			else
				[_machine pushOperatorBitwiseOr:addr];
			break;
		}
		case '&':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '&')//NOTE || 
				[_machine pushOperatorAnd:addr];//e.g. || 
			else
				[_machine pushOperatorBitwiseAnd:addr];
			break;
		}
		case '^':{
			[_machine pushOperatorBitwiseExclusiveOr:addr];
		}
		default:{
			break;
		}
		}
	return 0;
}

- (int)parseOperator:(NSString*)op withAddress:(int)addr andAddress:(int)addr2
{
		switch ([op characterAtIndex: 0]) {//character as e.g. '+'
		case '+':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '+')//NOTE e.g. i++
				[_machine pushOperatorPlusPlus:addr];
			else if ([op length] > 1 && [op characterAtIndex: 1] == '=')//NOTE e.g. i++
				[_machine pushOperatorPlusAssign:addr andAddress:addr2];//e.g. addr += addr2
			else
				[_machine pushOperatorPlus:addr];
			break;
		}
		case '-':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '-')//NOTE e.g. i--
				[_machine pushOperatorMinusMinus:addr];
			else if ([op length] > 1 && [op characterAtIndex: 1] == '=')//NOTE e.g. i++
				[_machine pushOperatorMinusAssign:addr andAddress:addr2];//e.g. addr += addr2
			else
				[_machine pushOperatorMinus:addr];
			break;
		}
		case '|':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '|')//NOTE e.g. i++
				[_machine pushOperatorOr:addr];
			else if ([op length] > 1 && [op characterAtIndex: 1] == '=')//NOTE e.g. i++
				[_machine pushOperatorBitwiseOrAssign:addr andAddress:addr2];//e.g. addr |= addr2
			else
				[_machine pushOperatorBitwiseOr:addr];
			break;
		}
		case '&':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '&')//NOTE e.g. i++
				[_machine pushOperatorAnd:addr];
			else if ([op length] > 1 && [op characterAtIndex: 1] == '=')//NOTE e.g. i++
				[_machine pushOperatorBitwiseAndAssign:addr andAddress:addr2];//e.g. addr |= addr2
			else
				[_machine pushOperatorBitwiseAnd:addr];
			break;
		}
		case '^':{
			if ([op length] > 1 && [op characterAtIndex: 1] == '=')//NOTE e.g. i++
				[_machine pushOperatorBitwiseExclusiveOrAssign:addr andAddress:addr2];//e.g. addr |= addr2
			else
				[_machine pushOperatorBitwiseExclusiveOr:addr];
			break;
		}
		default:{
			break;
		}
		}
	return 0;
}

- (int)checkTypeOf:(Symbol*)s and:(TYPE)t
{

	if ([s type] == t)
		return 0;

	if (([s type] == ctype && t == itype) 
		|| 
		(t == ctype && [s type] == itype)) 
		return 0;

	return -1;
}

- (TupleInt*) parsehexandset:(int)h 
{
	//big endian system
	switch (h) {
	case 0x00:{
		return 0;
	}
	case ctype:{
		_parsetreestatus = [[TupleInt new] addFirst:ctype andSecond:@"char"]; 	
		break;
	}
	case itype:{
		_parsetreestatus = [[TupleInt new] addFirst:itype andSecond:@"integer"]; 	
		break;
	}
	case vtype:{
		_parsetreestatus = [[TupleInt new] addFirst:vtype andSecond:@"void"]; 	
		break;
	}
	default:{
	}
	}	
	return _parsetreestatus;
}

- (int) parseDefinition:(TupleInt*)status
{
	int val = NULL;
	int addy = [_machine generateFreeAddress];
	Symbol *s;

#ifdef HAVE_MACHINE_ARMASM

	s = [[SymbolArm new] ctor:[status first] withSymbolName:[status second] andValue:val andAddress:addy andRegisterNumber:[_machine generateFreeRegisterNumber]];
	if ([s getRegisterNumber] < 0) {
		s = [[Symbol new] ctor:[status first] withSymbolName:[status second] andValue:val andAddress:addy];
		[self setLastSymbol:s];
		[_machine pushDefinition:[[Hex new]setNumber:addy] with:[[Hex new]setNumber:val andRegisterNumber:[s getRegisterNumber]]];//FIXME value NSString to number
	} else {
		[_symboltable addObject:s];
		[self setLastSymbol:s];
		[_machine pushDefinition:[[Hex new]setNumber:addy] with:[[Hex new]setNumber:val];//FIXME value NSString to number
	}
#else

	Symbol *s = [[Symbol new] ctor:[status first] withSymbolName:[status second] andValue:val andAddress:addy];
	[_symboltable addObject:s];
	[self setLastSymbol:s];
	[_machine pushDefinition:[[Hex new]setNumber:addy] with:[[Hex new]setNumber:val]];//FIXME value NSString to number

#endif	

	return 0;
}

- (int) parseAssignment:(TupleInt*)status withValue:(TupleInt*)value
{

	[_symboltable set:[status second] value:[value second]];
	[_machine pushAssignment:[[Hex new] setNumber:[status second]] with:[[Hex new] setNumber:[value second]]];//FIXME value NSString etc to number	
	return 0;
}


- (int) setLastSymbol:(Symbol*)s
{

	_lastsymbol = s;
	return 0;

}

- (NSMutableArray*)splitWeenies:(NSString*)line
{
	//NOTE reversed line
	NSMutableArray *array = [NSMutableArray new];
	int idx = 0;
	NSString *s = @"";
	char c;
	while (idx < [line length]) {
		while ((c = [line characterAtIndex:idx++]) != ';' && s += c)
			;
		[array addObject:s];
		s = @"";
	 }

	return array;
}

- (TupleInt)searchForBracesCode:(NSString*)line
{
	int n = 0;

	int i = 0;

	//if at all times n < 0 there are extra closing braces leftover
	while (i < [line length]) {
		if ([line characterAtIndex:i] == '{')
			n++;
		if ([line characterAtIndex:i] == '}')
			n--;
	}
	
	return n;
}

- (int)searchForClosingBraces
{

	return 0;
}
@end
