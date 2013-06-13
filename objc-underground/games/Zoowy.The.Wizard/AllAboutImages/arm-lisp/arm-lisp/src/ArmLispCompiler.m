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


#import "ArmLispCompiler.h"
#import "Hex.h"
#import "ParseTreeOp.h"
#import "6502AssemblerMachine.h"
#import "ArmAssemblerMachine.h"
#import "Word.h"

@implementation ArmLispCompiler

- (ArmLispCompiler*)ctor:(MACHINETYPE)i
{
	_symboltable = [[SymbolTable new] ctor];
	_typetable = [[TypeTable new] ctor];
	NSLOG(@"constructing...");
	_operatortable = [[OperatorTable new] ctor];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"+" andAddress:[[Hex alloc] ctorString:@"+"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"++" andAddress:[[Hex alloc] ctorString:@"++"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"1+" andAddress:[[Hex alloc] ctorString:@"1+"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"-" andAddress:[[Hex alloc] ctorString:@"-"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"1-" andAddress:[[Hex alloc] ctorString:@"1-"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"--" andAddress:[[Hex alloc] ctorString:@"--"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"*" andAddress:[[Hex alloc] ctorString:@"*"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"**" andAddress:[[Hex alloc] ctorString:@"**"]]];
	[_operatortable addObject:[[Operator alloc] defineWithName:@"/" andAddress:[[Hex alloc] ctorString:@"/"]]];
	//TODO add other operators
	//add arm bytecode, java bytecode, ...
	switch(i){
	case HAVE_MACHINE_6502ASM:{
		_machine = [[NesAssemblerMachine alloc] ctor];
		break; 
	}
	case HAVE_MACHINE_ARMASM:{ 
		_machine = [[ArmAssemblerMachine alloc] ctor];
		break; 
	}
	default:{
		_machine = [[ArmAssemblerMachine alloc] ctor];
		break; 
	}
	}
	NSLOG(@"done.");
	return self;
}

- (int)grepLines:(NSString*)buffer
{

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
		char c = [line characterAtIndex:idx];
		if (c == ' ' || c == '\t')
			;
		else
			break;
		idx++;
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
	//idx--;

	NSString *s = @"";
	while (idx < [line length]) {
		char c = [line characterAtIndex:idx++];
		if (c == ' ' || c == '\t')
			return [[TupleInt new] addFirst:idx andSecond:s];
	
		s += c;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

/*
 * 1. grep word until parens encounterd '(' or ')'
 * 2. grep word starting with parens '('
 */
- (TupleInt*)grepWordOfLineParens:(NSString*)line withIndex:(int)idx
{
//	NSLOG2(@"parens s=%@",line);
//	NSLOG2(@"parens1 idx=%d",idx);
	//skip prevailing whitespace
	//int idx2 = idx; 
	TupleInt *ti = [self skipWhiteSpace:line withIndex:idx];
	//idx = [ti first];
	//if (idx2 != idx)
	//	idx--;
//	NSLOG2(@"parens2 idx=%d",idx);

	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	while (idx < [line length]) {
		char c = [line characterAtIndex:idx];
//		NSLOG2(@"parens c=%c",c);
		if (c == ' ' || c == '\t') 
			return [[TupleInt new] addFirst:idx andSecond:s];

		if ((c == '(' || c == ')') && idx > 0) {
			//s += c;
			[s appendFormat:@"%c",c];
			idx++;
			return [[TupleInt new] addFirst:idx andSecond:s];
		}
		[s appendFormat:@"%c",c];
		//s += c;
		idx++;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

/*
 * This gets a single word or form from formstring (non reversed form!) 
 */
- (NSString*)grepFormOrWord:(NSString*)formstring withIndex:(int)idx
{
	//skip prevailing whitespace
	int nopen = 0;
	int nclosed = 0;
	TupleInt *ti = [self skipWhiteSpace:formstring withIndex:idx];
	idx = [ti first];
	//Form *form = [[Form alloc] initWithString:@""];
	NSLOG3(@"grepping for wordorform in = %@ idx=%d",formstring,idx);
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	while (idx < [formstring length]) {
		char c = [formstring characterAtIndex:idx];
		if ((c = [formstring characterAtIndex:idx]) == '(') {
			nopen++;//NOTE formstring is reversed
			[s appendFormat:@"%c",c];
		} else if ((c = [formstring characterAtIndex:idx]) == ')') {
			nclosed++;//NOTE formstring is reversed
			if (nopen == nclosed && nopen != 0 && nclosed != 0) {
				[s appendFormat:@"%c",c];
				//[form setString:s];
				//Form get formatted inherently with fomatLisp
				//in the above ctor
				NSLOG2(@"*** grepped form = %@",s);
				//return form;
				return s;
			}
		} else if (nopen == 0 && (c == ' ' || c == '\t')) { 
			//[form setString:s];
			//Form get formatted inherently with fomatLisp
			//in the above ctor
			NSLOG2(@"*** grepped word = %@",s);
			return s;
		} else {
			[s appendFormat:@"%c",c];
		}
		//s += c;
		idx++;
	}

	NSLOG2(@"*** no word or form = %@ - raise error",s);
	//Form get formatted inherently with fomatLisp
	return s;
}

- (TupleInt*)grepWordOfLineParensAndChomp:(NSString*)line withIndex:(int)idx
{
//	NSLOG2(@"parens s=%@",line);
//	NSLOG2(@"parens1 idx=%d",idx);
	//skip prevailing whitespace
	//int idx2 = idx; 
	TupleInt *ti = [self skipWhiteSpace:line withIndex:idx];
	idx = [ti first];
	//if (idx2 != idx)
	//	idx--;
//	NSLOG2(@"parens2 idx=%d",idx);

	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	while (idx < [line length]) {
		char c = [line characterAtIndex:idx];
//		NSLOG2(@"parens c=%c",c);
		if (c == ' ' || c == '\t') 
			return [[TupleInt new] addFirst:idx andSecond:s];

		if ((c == '(' || c == ')') && idx > 0)
			return [[TupleInt new] addFirst:idx andSecond:s];
		[s appendFormat:@"%c",c];
		//s += c;
		idx++;
	}

	return [[TupleInt new] addFirst:idx andSecond:@""];
}

- (TupleInt*)getRestOfForm:(NSString*)formstring withIndex:(int)idx
{
	//FIXME ?
	//TupleInt *ti = [self skipWhiteSpace:formstring withIndex:idx];
	//idx = [ti first];
	//skip prevailing whitespace
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	while (idx < [formstring length]) {
		char c = [formstring characterAtIndex:idx++];
		[s appendFormat:@"%c",c];
	}

	return [[TupleInt new] addFirst:idx andSecond:s];
}

- (TupleInt*)getRestOfFormAndChomp:(NSString*)formstring withIndex:(int)idx
{
	//skip prevailing whitespace
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	while (idx < [formstring length]-1) {
		char c = [formstring characterAtIndex:idx++];
		[s appendFormat:@"%c",c];
	}

	return [[TupleInt new] addFirst:idx andSecond:s];
}

- (TupleInt*)grepWord:(NSString*)needleword OfWord:(NSString*)haystackword withIndex:(int)idx
{
	//FIXME use indexOf
	NSString *s = @"";
	while (idx++ < [haystackword length]) {
		int idx2;
		for (idx2 = 0; idx2 < [needleword length]; idx2++) {
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
	//int idx2 = idx; 
	TupleInt *ti = [self skipWhiteSpace:line withIndex:idx];
	idx = [ti first];
	//if (idx2 != idx)
	//	idx--;
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
	
- (int)compilablesource:(NSString*)filename {
	
	//FileBuffer *buffer = [fileName buffer];

	//int i = -1;
	//while (++i < [buffer length]) {
	//i = [self parseFile:fileName withIndex:i];
	FNString *fn = [[FNString alloc] ctor:filename];
	[fn readInFile];
	[self parseFile:fn withIndex:0];
	//}

	return 0;
}

- (int) parseFile:(FNString*)fn withIndex:(int)idx 
{
	NSString *str = [fn bufferstring];
	
//	NSString *st;
//	st = [NSString stringWithFormat:@"str=%@", str];
//	NSLOG(st);	
	Form *f	= [[Form alloc] initWithString:str];
	if (f == nil)
		return 0;//NOTE nil form or @"" formstring
	[self parseForms:f withIndex:idx];

	return 0;
}

/*
 * This is a Lisp file's form parser, if forms
 * are encountered which can be put into the symbol or
 * type table they are transferred there with a symbol's
 * value equal to the form's code
 *
 * If the forms are to be executed they need another loop
 * through the form parser so they get executed
 * 
 * example 1 :
 * 
 * (defvar x 1 "This is the documentation of 1")
 * 
 * The form "1 "This is the documemntation of 1"" is
 * put into the symbol's name x with address [[Hex alloc] ctorString:"x"]
 * in the _symboltable of this parser. It gets immediately translated to 
 * e.g. 6502 assembly with "sta 1"
 * 
 * example 2 :
 * 
 * (defun y () (return-from "123"))
 * 
 * The only thing that happens with this is that it gets set
 * in the _symboltable with [[Hex alloc] ctorString:"y"] as an address
 */
- (int) parseForms:(Form*)form withIndex:(int)idx 
{
	NSLOG(@"parsing Forms...");
	NSString *formstring = [form string];

	int linest = [self grepLines:formstring];

	int lines = 0;
	NSString *s = [[NSString alloc] initWithString:@""];
	while (idx < [formstring length]) {
		char c = [formstring characterAtIndex:idx];	

		if (c == '\n')
			lines++;
		idx++;
	}
	Form *subform;	
	int i = 0;
	//init the top-level environment of this file's forms
	NSMutableArray* array;// = [NSMutableArray new];
	array = [self splitForms:formstring];//split
	if (array == nil /*|| [array length] == 0*/) { 
		NSLOG(@"Form array is nil@");
		return -1;
	}
	NSEnumerator *iter = [array objectEnumerator];
	//set below idx += [form length];//NOTE
	while (subform = [iter nextObject]/* && subform != nil*/) {
		[subform reverse];//NOTE
		NSLOG3(@"%@ %@", @"Processing Form",[subform string]);
		int r = [self parseFormForDefinition:subform];

		/* a definition gets added to the symbol or typetable
		 * defvar, deftype respectively
		 * deftype only generates a type in the typetable
		 * There is no machine instruction for type definitions
		 * on an ARM, 6502 etc.
                 */
		if (r == 0xdef) {//definition
			NSString *st;
			st = [NSString stringWithFormat:@"%@", @"have definition." ];	
			//[form addStatus:HAVE_DEFINITION String:st];
			NSLOG(st);
			continue;
		} else {
			r = [self parseFormForOperator:subform];
			if (r == 0xabc) {//operator
				NSString *st;
				st = [NSString stringWithFormat:@"%@", @"have operator." ];	
				//[form addStatus:HAVE_OPERATOR String:st];	
				NSLOG(st);
				continue;
			} else {
				r = [self parseFormForIf:subform];
				if (r == 0x333) {//if
					NSString *st;
					st = [NSString stringWithFormat:@"%@", @"have if." ];	
					//[form addStatus:HAVE_IF String:st];	
					NSLOG(st);
					continue;
				} else {
					r = [self parseFormForDefun:subform];
					if (r == 0xabba) {//if
						NSString *st;
						st = [NSString stringWithFormat:@"%@", @"have function definition." ];	
						//[form addStatus:HAVE_LOOP String:st];	
						NSLOG(st);
						continue;
					} else {
						r = [self parseFormForFuncall:subform];
						if (r == 0xfaa) {//if
							NSString *st;
							st = [NSString stringWithFormat:@"%@", @"have function call." ];	
							//[form addStatus:HAVE_LOOP String:st];	
							NSLOG(st);
							continue;
						}
					}
				}
			}
		}
	}
/* TODO
	if ([[fileName getLastStatus] first] == HAVE_IF) {//next subform
		subform = [self grepLine:fileName withIndex:idx];
		subform = [ self reverse: subform ];//NOTE
		int r2 = [self parseLineForElseClause:subform];
		if (r2 < 0) //no else clause found
			return idx;
		else if (r2 == 5) 
			[fileName addStatus:HAVE_ELSE String:&st];
		else if (r2 == 2) {	
			[fileName addStatus:HAVE_CLOSINGBRACE String:&st];
			[fileName addStatus:HAVE_ELSE String:&st];
		} else if (r2 == 3) {	
			[fileName addStatus:HAVE_CLOSINGBRACE String:&st];
			[fileName addStatus:HAVE_ELSE String:&st];
			[fileName addStatus:HAVE_OPENINGBRACE String:&st];
		} else {
		}
		idx += [subform length];
		[_machine pushElse:[Hex ctor: [_lastsymbol address]]];
	}
	}*/
	
	NSLOG(@"Reached end of form.");
	return 0;
}

- (int) parseAtom:(Form*)form withIndex:(int)idx 
{
	NSLOG(@"parsing Atom...");
	NSString *formstring = [form string];
		//[subform reverse];//NOTE
	NSLOG3(@"%@ %@", @"Processing Atom",[form string]);

	switch((TYPE)[self getTypeOfString:formstring]) {
	case (const TYPE)itype:
		[_machine pushLoadConstant:[[Hex alloc] ctorInt: atoi([formstring UTF8String])]];
		break;	
	case (const TYPE)symtype:
	default:{
		Hex *varhex = [[Hex new] ctorString:[form string]];
		Symbol *s2 = [_symboltable searchForHex: varhex ];
		int address;
		if (s2 == nil) 
			address = -1;
		else
			address = [[s2 address] number];
	
		//check if variable's address exists
		if (address < 0) {
			//TODO raise error
			NSLOG(@"Syntax Error (parseAtom) : unknown value of variable");
			return -1;
		} else {
			//compare address in if clause for true or false
			[_machine pushLoadSymbol:varhex];	
		}
		break;
	}
	}

/*	int r = [self parseFormForDefinition:form];
	if (r == 0xdef) {//definition
		NSString *st;
		st = [NSString stringWithFormat:@"%@", @"have definition." ];	
		//[form addStatus:HAVE_DEFINITION String:st];
		NSLOG(st);
	} else {
		r = [self parseFormForOperator:form];
		if (r == 0xabc) {//operator
			NSString *st;
			st = [NSString stringWithFormat:@"%@", @"have operator." ];	
			//[form addStatus:HAVE_OPERATOR String:st];	
			NSLOG(st);
		} else {
			r = [self parseFormForIf:form];
			if (r == 0x333) {//if
				NSString *st;
				st = [NSString stringWithFormat:@"%@", @"have if." ];	
				//[form addStatus:HAVE_IF String:st];	
				NSLOG(st);
			}
		}
	}
*/	return 0;
}

- (int) parseFormForDefinition:(Form*)form//NOTE form has been reversed reversed (human readable code string)
{

	NSLOG(@"parse for definition...");
	NSString *formstring = [form string];
	TupleInt *ti = [self grepWordOfLineParens:formstring withIndex:0 ];


	//NSLOG(@"word=%@", (NSString*)[ti second]);
	NSString *sti;
	sti = [NSString stringWithFormat:@"%@", (NSString*)[ti second]];
	//NSLOG(@"stiword=%@", sti);
	//check for type definition
	if ([sti compare: @"(deftype"] == 0) {
		NSLOG(@"deftype definition");
		//construct hex out of NSString*word which is the type after deftype
		TupleInt* ti2 = NULL;
		Tuple *t = [[Tuple new] addFirst:[ti second] andSecond:NULL ];
		NSString *word = [ t first ];
		int idx = [ti first];
		Hex *hex = [[Hex new] ctor:word];

		//check if word is already defined
		int hexint = [_typetable searchForHex: hex];//TODO return Type* instead of hexint

		//NOTE FIXME big endian system, bit per bit parsing of ids
		//check if hex needs updating

		//NOTE do not forget Lisp changes its native types, so type in typetable needs to be overwritten
		while (hexint != 0x0000) {
			int h = h | hexint;
			//switch on Native Lisp type (integer, char, ...) 
			switch (hexint & 0x1000) {
			case (const TYPE)ctype:{//ctype, character type
				continue;
				break;
			}
			case (const TYPE)itype:{//itype const, integer
				
				if ([[self parsehexandset: h] first] == 0x0000) 
					continue; 
				else {// hex is e.g. 0x02 for int (itype) 
					ti2 = [self grepWordOfLineParens:formstring withIndex:[ti first]];
					idx = [ti2 first];
					[self parseDefinitionOfdeftype:ti2];
					//goto lableassignment;
				}
				break;
			}
			//FIXME vtype 4 and other types
			default:{
				break;
			}
			}
			hexint <<= 2;
	
		}
		return 0xdef;
	} else if ([sti compare: @"(defvar"] == 0) {
		NSLOG(@"defvar definition");
		//NSLOG2(@"1--->%@",[ti second]);

		TupleInt* ti2;
		TupleInt* ti3;
		TupleInt* ti4;
		
		//example : (defvar x 1)
		//get name of free variable (x)
		ti2 = [self grepWordOfLineParens:formstring withIndex:[ti first]];
		//NSLOG3(@"2--->%@ idx=%d",[ti2 second],[ti2 first]);
		ti4 = [self getRestOfForm:formstring withIndex:[ti2 first]];
		//get value of free variable (1)
		//NSLOG2(@"rest of form--->%@",[ti4 second]);
		TupleInt *ti5 = [self hasSubForms:[ti4 second]];
		if ([ti5 first] < 0) {
			ti3 = [self grepWordOfLineParensAndChomp:formstring withIndex:[ti2 first]];
			//NSLOG2(@"5--->%@",[ti3 second]);
			[self parseDefinitionOfdefvar:ti2 and:ti3];//evals to formstring or simple statement
		} else {
			ti3 = [self getRestOfFormAndChomp:formstring withIndex:[ti2 first]];
			//NSLOG2(@"5--->%@",[ti3 second]);
			[self parseDefinitionOfdefvarWithForm:ti2 and:ti3];//evals to formstring or simple statement
		} 
		return 0xdef;
	} else if ([sti compare: @"(setq"] == 0 || [sti compare: @"(setf"] == 0) {
		NSLOG(@"setq or setf definition");

		TupleInt* ti2;
		TupleInt* ti3;
		TupleInt* ti4;
		TupleInt* ti5;
		
		ti3 = [self skipWhiteSpace:formstring withIndex:[ti first]];
		//example : (setq x 1)
		//get name of free variable (x)
		ti2 = [self grepWordOfLineParens:formstring withIndex:[ti3 first]];
		NSLOG2(@"definition sym=%@ ",[ti2 second]);
		ti4 = [self getRestOfFormAndChomp:formstring withIndex:[ti2 first]];
		//get value of free variable (1)
		//evals to formstring or simple statement
		//ti5 = [self hasSubForms:[ti4 second]];
		NSString *s5 = [self grepFormOrWord:formstring withIndex:[ti2 first]];
		NSLOG2(@"definition sym5=%@ ",s5);
		if ([s5 characterAtIndex:0] != '(') {
			//ti3 = [self grepWordOfLineParensAndChomp:formstring withIndex:[ti2 first]];
			NSLOG3(@"def sym=%@ val=%@",[ti2 second],[ti4 second]);
			[self parseDefinitionOfsetfq:ti2 and:ti4];
		} else {
			ti3 = [self getRestOfFormAndChomp:formstring withIndex:[ti2 first]];
			[self parseDefinitionOfsetfqWithForm:ti2 and:ti4];//evals to formstring or simple statement
		} 

		return 0xdef;
	} else {
		NSLOG(@"No definition");
		return 0x000;//NOTE
	}
	return 0x000;//NOTE
}

- (int) parseFormForOperator:(Form*)form//NOTE line has been reversed reversed
{
	NSLOG(@"parsing for operator...");
	NSString *formstring = [form string];
	int idx = 0;

	while (idx++ < [formstring length]) {

		TupleInt *ti = [self grepWordOfLineParens:[form string] withIndex:1];//NOTE 1
		idx = [ti first];
		Operator *op = [_operatortable getOperator:[ti second]];
		if (op == nil) {//Operator does not exist, no definition or declaration found
			NSLOG(@"no matching operator not found");
			return 0x000;
		} 

		//NOTE rest of form is even parensed by splitForms: above
		ti = [self getRestOfForm:formstring withIndex:idx];
		//idx = [ti first];
		NSLOG2(@"rest of form=%@", [ti second]);	

	
		return [self parseOperator:[op string] form:[[Form alloc] initWithString:[ti second]]];
	}
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

- (int) parseFormForDefun:(Form*)form//NOTE line has been reversed reversed
{
	TupleInt* ti = [self grepWordOfLineParens:[form string] withIndex:0];
	Word *w = [[Word alloc] ctor: [ti second]];//NOTE form
	NSLOG3(@"-------------->%@ is=%d", [w string],[w isParensDefun]);
	//if ([w isParensDefun] < 0) {	
	if ([[w string] compare: @"(defun"] != 0) {
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	if ([self parseFormForDefunClause:[[Form alloc] initWithString:[form string]]] == 0xabba) {
		//[_machine pushPreviousLabel];
		NSString *l = [_machine getLastLabel];//FIXMENOTETODO!!
		[_machine pushLoopGoto:l];
		
		return 0xabba;
	}
}

- (int) parseFormForIf:(Form*)form//NOTE line has been reversed reversed
{
	TupleInt* ti = [self grepWordOfLineParens:[form string] withIndex:0];
	Word *w = [[Word alloc] ctor: [ti second]];//NOTE form

	if ([w isParensIf] < 0 || [w isIfClause] < 0) {	
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	if ([self parseFormForIfClause:[[Form alloc] initWithString:[form string]]] == 0x333) {
		//[_machine pushPreviousLabel];
		
		return 0x333;
	}
}

- (int) parseFormForLoop:(Form*)form//NOTE line has been reversed reversed
{
	TupleInt* ti = [self grepWordOfLineParens:[form string] withIndex:0];
	Word *w = [[Word alloc] ctor: [ti second]];//NOTE form

	if ([w isParensLoop] < 0 /*|| [w isIfClause] < 0*/) {	
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	if ([self parseFormForLoopClause:[[Form alloc] initWithString:[form string]]] == 0x444) {
		//[_machine pushPreviousLabel];
		
		return 0x444;
	}
}

- (int) parseLineForWhile:(NSString*)line//NOTE line has been reversed reversed
{
	Word *w = [Word ctor: line];//NOTE line

	if ([w isWhile] < 0 || [w isWhileClause] < 0) {	
		_parsetreestatus = [[TupleInt new] addFirst:0 andSecond:NULL];//FIXME remove
		return 0x000;
	}

	[_machine pushNewLabel];
	if ([self parseLineForWhileClause:line] == 0x444) {
		[_machine pushBranch:[Hex ctor: [_lastsymbol address]]];
		
		return 0x444;
	}
}

- (int) parseFormForFuncall:(Form*)form
{
	NSLOG(@"Parsing Funcall");
	//skip leading '(', idx = 1 here
	Form *f = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:1]];
	//int idx = [self skipWordAndWhiteSpace:form withIndex:0];
	//TupleInt* ti = [self grepWordOfLineParens:[f string] withIndex:0];
	
	Hex *varhex = [[Hex new] ctorString:[f string]];
	Symbol *s = [_symboltable searchForHex: varhex ];
	//Symbol *s = [_symboltable getString:[f string]];

	//generate loop label and push it
	//[_machine pushNewLabel];
	//NSString *looplabel = [_machine getLastLabel];
	NSLOG2(@"func symbol found=%@",[s string]);
	//Form *f = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];

	if ([s type] == (TYPE)functype) {
		NSLOG(@"got function symbol");

		Form *argsandbody = [s value];
		NSLOG2(@"argsandbody = %@", [s value]);
		// index 1, skip '('
		NSString *args = [self grepFormOrWord:argsandbody withIndex:0];

		int idx = 1;
		int idx2 = [self skipWordAndWhiteSpace:form withIndex:0];
		while (idx2 < [[form string] length]-1) {//-1 index for last ')'

			//argument symbol name
			TupleInt *ti = [self grepWordOfLineParensAndChomp:args withIndex:idx];//TODO AndChomp for several args
			idx = [ti first];
			//argument value
			NSString *argvalue = [self grepFormOrWord:[form string] withIndex:idx2];
			//idx = [self skipFormAndWhiteSpace:form withIndex:idx];
			NSLOG2(@"symvalue = %@", [ti second]);
			NSLOG2(@"argvalue = %@", argvalue);
			//Hex *vargulf = [[Hex new] ctorString:[s2 string]];

			[self parseDefinitionOfdefvar:[[TupleInt alloc] addFirst:-1 andSecond:[ti second]] and:[[TupleInt alloc] addFirst:-1 andSecond:argvalue]];
			//[_machine pushDefinition:varhex with:vargulf];

			idx2 = [self skipWordAndWhiteSpace:form withIndex:idx2];
		}
		//push label to go to function call
		NSString *newl = [_machine generateFreeLabel];
		NSString *functionlabel = [NSString stringWithFormat:@"label%@",[s name]];
		[_machine pushLoopGoto:functionlabel];

		[_machine pushNewLabel:newl];

		return 0xfaa;
	}

	return 0x000;
}

- (int) parseFormForLoopClause:(Form*)form
{
	//generate loop label and push it
	[_machine pushNewLabel];
	NSString *looplabel = [_machine getLastLabel];
	
	int idx = [self skipWordAndWhiteSpace:form withIndex:0];
	NSLOG2(@"P=%d",idx);
	Form *f = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];

	if ([[f string] compare: @"while"] == 0) {

		NSLOG(@"got Loop while");

		//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		//loop condition is atom
		//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		NSLOG3(@"form string=%@ idx=%d",[form string], idx);
		idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		Form *f2 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
		if ([[f2 string] characterAtIndex:0] != '(') {
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			//Form *f2 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			[self parseAtom:f2 withIndex:0];	

			[_machine pushLoopDefaultRegister];

			idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			NSLOG2(@"W=%d",idx);
			TupleInt* ti = [self grepWordOfLine:[form string] withIndex:idx];
			NSLOG2(@"W=%d",[ti first]);
			//if ([[ti second] compare: @"do"] == 0) {
				//TODO != '(', isForm
				NSLOG(@"do of loop");
				idx = [self skipWordAndWhiteSpace:form withIndex:idx];
				Form *f3 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				//[f3 reverse];
				if ([[f3 string] characterAtIndex:0] != '(') {	
					[self parseAtom:f3 withIndex:0];	
					[_machine pushLoopGoto:looplabel];
					[_machine pushPreviousLabel];

				} else {

					[self parseForms:f3 withIndex:0];	
					[_machine pushLoopGoto:looplabel];
					[_machine pushPreviousLabel];
				}
			return 0x444;
			//}
		} else {
		//loop condition is form
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			Form *f4 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			[f4 reverse];
			[self parseForms:f4 withIndex:0];	

			[_machine pushLoopDefaultRegister];

			idx = [self skipFormAndWhiteSpace:form withIndex:idx];
			NSLOG2(@"WW=%d",idx);
			TupleInt* ti = [self grepWordOfLine:[form string] withIndex:idx];
			NSLOG2(@"WW=%d",[ti first]);
			NSLOG(@"do of loop form");
			//skip do word
			idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			Form *f3 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			if ([[f3 string] characterAtIndex:0] != '(') {	
				[self parseAtom:f3 withIndex:0];	
				[_machine pushLoopGoto:looplabel];
				[_machine pushPreviousLabel];

			} else {

				[self parseForms:f3 withIndex:0];	
				[_machine pushLoopGoto:looplabel];
				[_machine pushPreviousLabel];
			}
			return 0x444;
		}

	}
	return 0x000;
}

- (int) parseFormForDefunClause:(Form*)form
{
	NSLOG(@"Parsing Defun Clause");



	int idx = [self skipWordAndWhiteSpace:form withIndex:0];
	Form *funname = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
	//if ([f isForm] < 0) {

	//pushing function label
	NSString *ns = [NSString stringWithFormat:@"label%@:",[funname string]];
	[_machine pushNewLabel:ns];

	idx = [self skipWordAndWhiteSpace:form withIndex:idx];
	Form *arglist = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];

	TupleInt *ti = [self getRestOfForm:[form string] withIndex:idx]; 

	idx = [self skipFormAndWhiteSpace:form withIndex:idx];
	Form *funbody = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];

	//Symbol *s = [[Symbol alloc] ctorName:[funname string] form:funbody type:(TYPE)functype];
	Symbol *s = [[Symbol alloc] ctorName:[funname string] form:[ti second] type:(TYPE)functype];
	[_symboltable addObject:s];
	//FIXME_lastsymbol = s;
	NSLOG4(@"defunname=%@ defunbody=%@ type=%d",[funname string],[ti second],functype);

/*
	while (idx < [arglist string]) { 
		NSLOG(@"parsing function argument list");
		NSString *st = [self grepWordOfLineParens:[arglist string] withIndex:idx];
		idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		Hex *varhex = [[Hex new] ctorString:[arglist string]];
		Symbol *s2 = [_symboltable searchForHex: varhex ];
		[_machine pushLoadSymbol:varhex];
	}
*/

	//idx = [self skipFormAndWhiteSpace:form withIndex:idx];
	if ([[funbody string] characterAtIndex:0] != '(') {
		[self parseAtom:funbody withIndex:0];
		return 0xabba;
	} else {
		[funbody reverse];
		[self parseForms:funbody withIndex:0];
		return 0xabba;
	}

	return 0x000;

}

- (int) parseFormForIfClause:(Form*)form
{
	NSLOG(@"Parsing If Clause");
	int idx = [self skipWordAndWhiteSpace:form withIndex:0];
	NSLOG2(@"P=%d",idx);
	Form *f = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
	NSLOG2(@"ISFORM=%@",[f string]);
	//if ([f isForm] < 0) {
	if ([[f string] characterAtIndex:0] != '(') {
		//found symbol or value
		//if ([_lastsymbol isKindOfClass:[Symbol class]]) {
		switch ((TYPE)[self getTypeOfString: [f string]]) {
		case (const TYPE)itype:
			[_machine pushIfConstant:atoi([[f string] UTF8String])];//TODO use value to type value conversion within Symbol
			//TODO parsing of true and false clauses	
			break;
		case (const TYPE)symtype:
		default:{
			Hex *varhex = [[Hex new] ctorString:[f string]];
			Symbol *s2 = [_symboltable searchForHex: varhex ];
			int address;
			if (s2 == nil) 
				address = -1;
			else
				address = [[s2 address] number];
	
			//check if variable's address exists
			if (address < 0) {
				//TODO raise error
				NSLOG(@"Syntax Error : unknown value of variable");
				return -1;
			} else {
				//compare address in if clause for true or false
				[_machine pushIf:[[Hex alloc] ctorInt: address]];
			}
		}	
		}//switch
		idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		NSLOG2(@"P=%d",idx);
		Form *ff = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
		
		//if ([f isForm] < 0) {
		//true clause is not a form
		if ([[ff string] characterAtIndex:0] != '(') {
			[self parseAtom:ff withIndex:0];

			idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			NSLOG2(@"P=%d",idx);
			Form *fff = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			
			if ([[fff string] compare:@""] == 0 || [[fff string] compare:@")"] == 0 || [[fff string] compare:@"\n"] == 0) {
				NSLOG(@"* no else clause");
				return 0x333;	
			}
			//if ([f isForm] < 0) {
			//else clause is not a form

			if ([[fff string] characterAtIndex:0] != '(') {
				[_machine pushPreviousLabel];
				[self parseAtom:fff withIndex:0];
				return 0x333;
			} else {//else clause is form
				[_machine pushPreviousLabel];
				[self parseForms:fff withIndex:0];
				return 0x333;
			}
		} else {//true clause is form
			NSLOG2(@"ff str=%@", [ff string]);
			[ff reverse];//FIXMENOTETODO
			[self parseForms:ff withIndex:0];
			[_machine pushPreviousLabel];

			idx = [self skipFormAndWhiteSpace:ff withIndex:idx];
			Form *form4 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
		
			NSLOG2(@"form4 string=%@",[form4 string]);
	
			/*if ([[form4 string] compare:@""] == 0 || [[form4 string] compare:@")"] == 0 || [[form4 string] compare:@"\n"] == 0) {
				NSLOG(@"* no else clause");
				return 0x333;	
			}*/
			//else clause is not a form
			//if ([f isForm] < 0) {
			if ([[form4 string] characterAtIndex:0] != '(') {
				idx = [self skipWordAndWhiteSpace:ff withIndex:idx];
				//Form *form11 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				//[form11 reverse];
				//[self parseForms:form11 withIndex:0];
				[self parseAtom:form4 withIndex:0];
				return 0x333;
			} else {//else clause is form
				idx = [self skipFormAndWhiteSpace:form withIndex:idx];
				Form *form10 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				[form10 reverse];
				[self parseForms:form10 withIndex:0];
				return 0x333;
			}
			return 0x333;
		}
	} else {//if clause is form
		NSLOG2(@"if clause is form=%@", [f string]);
		[f reverse];
		[self parseForms:f withIndex:0];
		[_machine pushIfDefaultRegister];
		NSLOG2(@"f =%@",[f string]);
		idx += [[f string] length];
		idx = [self skipWordAndWhiteSpace:form withIndex:idx];
		NSLOG2(@"P=%d",idx);
		Form *ff = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
		
		//true clause is atom	
		//if ([f isForm] < 0) {
		if ([[ff string] characterAtIndex:0] != '(') {
			[self parseAtom:ff withIndex:0];
			[_machine pushPreviousLabel];
			idx = [self skipFormAndWhiteSpace:ff withIndex:idx];
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			Form *form5 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			
			if ([[form5 string] compare:@""] == 0 || [[form5 string] compare:@")"] == 0 || [[form5 string] compare:@"\n"] == 0) {
				NSLOG(@"* no else clause");
				return 0x333;	
			}
			//else clause is not a form
			//if ([f isForm] < 0) {
			if ([[form5 string] characterAtIndex:0] != '(') {
				NSLOG2(@"form5 atom string=%@",[form5 string]);
				[self parseAtom:form5 withIndex:0];
				idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
				Form *form9 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				[form9 reverse];
				[self parseForms:form9 withIndex:0];
				return 0x333;
			} else {//else clause is form
				NSLOG2(@"form5 form string=%@",[form5 string]);
				idx = [self skipFormAndWhiteSpace:form withIndex:idx];
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
				Form *form6 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				[self parseForms:form6 withIndex:0];
				return 0x333;
			}
		//true clause is form
		} else {
			[ff reverse];
			[self parseForms:ff withIndex:0];
			[_machine pushPreviousLabel];
			//idx = [self skipWordAndWhiteSpace:form withIndex:idx];
			idx = [self skipFormAndWhiteSpace:form withIndex:idx];
			Form *form5 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			
			if ([[form5 string] compare:@""] == 0 || [[form5 string] compare:@")"] == 0 || [[form5 string] compare:@"\n"] == 0) {
				NSLOG(@"* no else clause");
				return 0x333;	
			}
			//else clause is not a form
			NSLOG3(@"--------->%@ idx=%d",[form5 string],idx);
			Form *form6 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
			//if ([f isForm] < 0) {
			if ([[form6 string] characterAtIndex:0] != '(') {
				Form *form7 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				[self parseAtom:form7 withIndex:0];
				idx = [self skipWordAndWhiteSpace:form withIndex:idx];
				Form *form8 = [[Form alloc] initWithString:[self grepFormOrWord:[form string] withIndex:idx]];
				if ([[form8 string] characterAtIndex:0] != '(') {
					[self parseAtom:form7 withIndex:0];
				}
				return 0x333;
			} else {//else clause is form
				[form6 reverse];
				[self parseForms:form6 withIndex:0];
				return 0x333;
			}
		}
		return 0x333;
	}
	
	//}
	//}
//	[_machine pushIf:[[Hex alloc] ctorInt: [[_lastsymbol address] number]]];
//		return 0x333;
/*	 else {
		if ([_machine type] != HAVE_MACHINE_6502ASM)
			[_machine pushIfDefaultRegister];//TODO
		return 0x000;
	}
*/
/*	r = [self parseLineForAssignmentWithOperator:[form string]];
	if (r == 0xabc) {//assignment with op 
		[_machine pushIf:[Hex ctor: [_lastsymbol address]]];
		return 0x333;
	}
*/
	return 0x000;
}
/*
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

	} else {//if clause is form
		NSLOG2(@"is form = %@",[f string]);
		[f reverse];
		[self parseForms:f withIndex:0];
		[_machine pushIfDefaultRegister];
		return 0x333;
	}
	//}
	//}
//	[_machine pushIf:[[Hex alloc] ctorInt: [[_lastsymbol address] number]]];
//		return 0x333;
*//*	 else {
		if ([_machine type] != HAVE_MACHINE_6502ASM)
			[_machine pushIfDefaultRegister];//TODO
		return 0x000;
	}
*/
/*	r = [self parseLineForAssignmentWithOperator:[form string]];
	if (r == 0xabc) {//assignment with op 
		[_machine pushIf:[Hex ctor: [_lastsymbol address]]];
		return 0x333;
	}
*/
/*	return 0x000;
}*/

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
			//goto lablepif;
			Word *w = [Word ctor:[self grepWordOfLine:line withIndex:idx]];
			return idx;
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
	
//lablepif:

	////if ([w isClosingBrace] >= 0)
			
	return idx;
}
 
- (int)parseOperator:(NSString*)op form:(Form*)form
{

	int idx = 0;
	//NOTE skip '('
	//idx++;

	switch ([op characterAtIndex: 0]) {//character as e.g. '+', (in op string!)
	case '1':
	case '+':{
		//++,1+
		if ([op length] > 1) {
			//skip op
			idx ++;
			if ( [op characterAtIndex: 1] == '+') {//NOTE e.g. i++
			//[_machine pushOperatorPlusPlus:addr];
				//[self setLastSymbol:s];
				return 0xabc;
			}
		//+
		} else if ([op characterAtIndex:0] != '1') {
			//skip operator syntax '+'
			//idx++;
			//skip whitespace 
			//idx++;
			NSLOG2(@"with idx : %@",[form string]);
			TupleInt *ti = [self skipWhiteSpace:[form string] withIndex:idx];
			idx = [ti first];
			NSLOG2(@"with idx : %@",[ti second]);
			//TupleInt *ti5 = [self hasSubForms:[form string]];
			//if ([ti5 first] < 0) {
			NSString *s5 = [self grepFormOrWord:[form string] withIndex:idx];
			if ([s5 characterAtIndex:0] != '(') {
			//if ([[self hasSubForms:[form string]] first] < 0) {
				while (idx < [[form string] length]-1) {//-1 skip last parens
					TupleInt *ti = [self grepWordOfLineParensAndChomp:[form string] withIndex:idx];
					NSLOG2(@"with idx : %@",[ti second]);
					idx = [ti first];

					if ([self parsePlus:ti] != 0)
						return -1;
					idx++;
				}
				return 0xabc;
			} else {//if ([[self hasSubForms:[form string]] first] == 1) {
			TupleInt *ti5 = [self hasSubForms:[form string]];
			if ([ti5 first] < 0) {

				while (idx < [[form string] length]-1) {
					TupleInt *ti = [self grepWordOfLineParensAndChomp:[form string] withIndex:idx];
					idx = [ti first];

					if ([self parsePlus:ti] != 0)
						return -1;
					idx++;
				}	
				return 0xabc;

			}
			}	
		}
		break;
	}
	}

	switch ([op characterAtIndex: 0]) {//character as e.g. '+'
	case '1':
	case '-':{
		//--,1-
		if ([op length] > 1) {
			idx ++;
			if ( [op characterAtIndex: 1] == '-') {//NOTE e.g. i++
			//[_machine pushOperatorPlusPlus:addr];
			}
		//+
		} else if ([op characterAtIndex:0] != '1') {
			TupleInt *ti = [self skipWhiteSpace:[form string] withIndex:idx];
			idx = [ti first];
			TupleInt *ti5 = [self hasSubForms:[form string]];
			if ([ti5 first] < 0) {
				while (idx < [[form string] length]-1) {
					TupleInt *ti = [self grepWordOfLineParensAndChomp:[form string] withIndex:idx];
					idx = [ti first];

					if ([self parseMin:ti] != 0)
						return -1;
					idx++;
				}
				return 0xabc;
			}	
		}
		break;
	}
	case '*':{
		//**
		if ([op length] > 1) {
			idx ++;
			if ( [op characterAtIndex: 1] == '*') {//NOTE e.g. i++
			//[_machine pushOperatorMulMul:addr];
			}
		//*
		} else {
			TupleInt *ti = [self skipWhiteSpace:[form string] withIndex:idx];
			idx = [ti first];
			TupleInt *ti5 = [self hasSubForms:[form string]];
			if ([ti5 first] < 0) {
			//if ([[self hasSubForms:[form string]] first] < 0) {
				while (idx < [[form string] length]-1) {
					TupleInt *ti = [self grepWordOfLineParensAndChomp:[form string] withIndex:idx];
					idx = [ti first];

					if ([self parseMul:ti] != 0)
						return -1;
					idx++;
				}
				return 0xabc;
			}	
		}
		break;
	}
/*	case '|':{
		if ([op length] > 1 && [op characterAtIndex: 1] == '|')//NOTE || 
			;//[_machine pushOperatorOr:addr];//e.g. || 
		else
			;//[_machine pushOperatorBitwiseOr:addr];
		break;
	}
	case '&':{
		if ([op length] > 1 && [op characterAtIndex: 1] == '&')//NOTE || 
			;//[_machine pushOperatorAnd:addr];//e.g. || 
		else
			;//[_machine pushOperatorBitwiseAnd:addr];
		break;
	}
	case '^':{
		//[_machine pushOperatorBitwiseExclusiveOr:addr];
	}
*/	default:{
		break;
	}
	}

	return 0x000;
}
/*
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
*/
- (TYPE)checkTypeOf:(Symbol*)sym and:(TYPE)t
{

	if ([sym type] == t)
		return t;

	if (([sym type] == ctype && t == itype) 
		|| 
		(t == ctype && [sym type] == itype)) 
		return itype;

	if ([_typetable hasType: [sym type]]) {//t is not used
		return [sym type];
	} 

	return -1;
}

- (TYPE)getTypeOfString:(NSString*)s
{
	NSLOG2(@"TYPE2=%@",s);
	if ([s compare: @"0"] != 0 && atoi([s UTF8String]) > 0) {
		NSLOG2(@"atoi=%d",atoi([s UTF8String]));
		return itype;
	}
	else if ([s compare: @"0"] != 0 && atof([s UTF8String]) > 0)
		return ftype;
	//character type also things like #\Linefeed
	else if ([s length] == 3 && [s characterAtIndex:0] == '#'
				 && [s characterAtIndex:1] == '\\'
				 && isascii([s characterAtIndex:2])) {
		return ctype;
	} else if ([s length] > 0 && [s characterAtIndex:0] == '"'
				&& [s characterAtIndex:[s length]-1] == '"')
		return stype;
	 else if ([s length] > 0)//TODO return -1 below
		return symtype;
	
/*
	if ([_typetable hasType: [s type]]) {//t is not used
		return [s type];
	} 
*/
	return -1;
}

- (TupleInt*) parsehexandset:(int)h 
{
	//big endian system
	switch (h) {
	case 0x00:{
		return 0;
	}
	case (const TYPE)ctype:{//ctype
		_parsetreestatus = [[TupleInt new] addFirst:ctype andSecond:@"char"]; 	
		break;
	}
	case (const TYPE)itype:{//itype
		_parsetreestatus = [[TupleInt new] addFirst:itype andSecond:@"integer"]; 	
		break;
	}
	case (const TYPE)vtype:{//vtype
		_parsetreestatus = [[TupleInt new] addFirst:vtype andSecond:@"void"]; 	
		break;
	}
	default:{
	}
	}	
	return _parsetreestatus;
}

- (int) parseDefinitionOfdeftype:(TupleInt*)status
{
	/*
	 * There is no machine instruction for type definitions
	 * on an ARM, 6502 etc.
	 * If a Lisp type gets encountered elsewhere the _typetable
	 * again provides help
         */
	int val = NULL;
	int addy = [_machine generateFreeAddress];
	[_typetable addType:addy withName:[status second]];
	[_machine pushDefinition:[[Hex new]setNumber:addy] with:[[Hex new]setNumber:val]];
	return 0;
}

- (int) parseDefinitionOfdefvar:(TupleInt*)sym and:(TupleInt*)val
{
	//TODO optional documentation string
	//TODO types of [var second] which is nto a form
	Hex *varhex = [[Hex new] ctorString:[sym second]];
	Hex *vargulf = [[Hex new] ctorInt:atoi([[val second] UTF8String])];

	NSLOG4(@"vars = %d %d val=%@",[varhex number],[vargulf number],[val second]);

	Symbol *s2 = [_symboltable searchForHex: varhex ];
	int address;
	if (s2 == nil) 
		address = -1;
	else
		address = [[s2 address] number];
	Symbol *s;
	//generate a new Hex _address, if _symboltable does not contain hexnumber address
	if (address < 0) {//var does not already exist 
		NSLOG(@"defvarAtom : no address found");
		address = [_machine generateFreeAddress];
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ctype];
			break;
		case (const TYPE)itype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:itype];
			break;
		case (const TYPE)stype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:stype];
			break;
		case (const TYPE)ftype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			
			break;
		}

		[_symboltable addObject:s];

	} else {

		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ctype];
			break;
		case (const TYPE)itype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:itype];
			break;
		case (const TYPE)stype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:stype];
			break;
		case (const TYPE)ftype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		}
	}
	[self setLastSymbol:s];
	//add symbol
	[_machine pushDefinition:varhex with:vargulf];//FIXME value NSString to number

	return 0;
}

//Form in [val second] gets assigned to variable
- (int) parseDefinitionOfdefvarWithForm:(TupleInt*)sym and:(TupleInt*)val
{
	//TODO optional documentation string
	Hex *varhex = [[Hex new] ctorString:[sym second]];

	//NSLOG3(@"vars = %d val=%@",[varhex number],[val second]);

	Symbol *s2 = [_symboltable searchForHex: varhex ];
	int address;
	if (s2 == nil) 
		address = -1;
	else
		address = [[s2 address] number];
	Symbol *s;
	//generate a new Hex _address, if _symboltable does not contain hexnumber address
	if (address < 0) {//var does not already exist 
		NSLOG(@"defvarForm : no address found");
		address = [_machine generateFreeAddress];
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ctype];
			break;
		case (const TYPE)itype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:itype];
			break;
		case (const TYPE)stype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:stype];
			break;
		case (const TYPE)ftype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			
			break;
		}
		[_symboltable addObject:s];
	} else {
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ctype];
			break;
		case (const TYPE)itype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:itype];
			break;
		case (const TYPE)stype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:stype];
			break;
		case (const TYPE)ftype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		}

	}
	[self setLastSymbol:s];

	return 0;
}

- (int) parseDefinitionOfsetfq:(TupleInt*)sym and:(TupleInt*)val
{
	//TODO optional documentation string
	//TODO types of [var second] which is nto a form
	Hex *varhex = [[Hex new] ctorString:[sym second]];
	Hex *vargulf = [[Hex new] ctorInt:atoi([[val second] UTF8String])];

	//NSLOG4(@"vars = %d %d val=%@",[varhex number],[vargulf number],[val second]);

	Symbol* s2 = [_symboltable searchForHex: varhex ];
	int address;
	if (s2 == nil) 
		address = -1;
	else
		address = [[s2 address] number];
	Symbol *s;
	//generate a new Hex _address, if _symboltable does not contain hexnumber address
	if (address < 0) {//var does not already exist 
		NSLOG(@"setfqAtom : no address found");
		address = [_machine generateFreeAddress];
		NSLOG2(@"TYPE=%d",[self getTypeOfString:[val second]]);
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ctype];
			break;
		case (const TYPE)itype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:itype];
			break;
		case (const TYPE)stype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:stype];
			break;
		case (const TYPE)ftype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			
			break;
		}
		NSLOG2(@"s addr= %d",[[s address] number]);
		[_symboltable addObject:s];

	} else {
		NSLOG(@"setfqAtom : address found");
		NSLOG2(@"+++++++++++++++>%d",[self getTypeOfString:[val second]]);
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ctype];
			[_machine pushDefinition:varhex with:[[Hex alloc]ctorInt:atoi([[val second] UTF8String])]];
			break;
		case (const TYPE)itype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:itype];
			[_machine pushDefinition:varhex with:vargulf];
			break;
		case (const TYPE)stype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:stype];
			[_machine pushDefinition:varhex with:vargulf];
			break;
		case (const TYPE)ftype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ftype];
			[_machine pushDefinition:varhex with:vargulf];
			break;
		case (const TYPE)symtype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			[_machine pushDefinition:varhex with:vargulf];
			break;
		//default type is symtype
		default:
		case -1:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			[_machine pushDefinition:varhex with:vargulf];
			break;
		}
	}
	[self setLastSymbol:s];
	//add symbol

	return 0;

}

//Form in [val second] gets assigned to variable
- (int) parseDefinitionOfsetfqWithForm:(TupleInt*)sym and:(TupleInt*)val
{
	//TODO optional documentation string
	Hex *varhex = [[Hex new] ctorString:[sym second]];

	NSLOG3(@"setfq vars = %d val=%@",[varhex number],[val second]);

	Symbol *s2 = [_symboltable searchForHex: varhex ];
	int address;
	if (s2 == nil)
		address = -1;
	else
		[[s2 address] number];
	Symbol *s;
	//generate a new Hex _address, if _symboltable does not contain hexnumber address
	if (address < 0) {//var does not already exist 
		NSLOG(@"setfq Form : no address found");
		address = [_machine generateFreeAddress];
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ctype];
			break;
		case (const TYPE)itype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:itype];
			break;
		case (const TYPE)stype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:stype];
			break;
		case (const TYPE)ftype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			s = [[Symbol new] ctorName:[sym second] form:[[Form alloc] initWithString: [val second]] type:symtype];
			
			break;
		}
		[_symboltable addObject:s];
	} else {
		switch ((TYPE)[self getTypeOfString:[val second]]){
		case (const TYPE)ctype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ctype];
			break;
		case (const TYPE)itype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:itype];
			break;
		case (const TYPE)stype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:stype];
			break;
		case (const TYPE)ftype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:ftype];
			break;
		case (const TYPE)symtype:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		//default type is symtype
		default:
		case -1:
			[_symboltable addObjectExists:varhex form:[[Form alloc] initWithString:[val second]] type:symtype];
			break;
		}

	}
	[self setLastSymbol:s];
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

- (NSMutableArray*)splitForms:(NSString*)formstring
{
	//NOTE reversed formstring !
	NSMutableArray *array = [[NSMutableArray alloc] init];
	int idx = 0;
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	char c;
	int nopen = 0;
	int nclosed = 0;
	while (idx < [formstring length]) {
		//NSLog(@"idx=%d c=%c",idx,[formstring characterAtIndex:idx]);
		//if ((c = [formstring characterAtIndex:idx]) == '`') {
			
		//} else 
		if ((c = [formstring characterAtIndex:idx]) == '(')
			nopen++;//NOTE formstring is reversed
			if (nopen == nclosed && nopen != 0 && nclosed != 0) {
				[s appendFormat:@"%c",c];
				Form *form = [[Form alloc] initWithString:s];
				//Form get formatted inherently with fomatLisp
				//in the above ctor
				NSLOG(@"Added form to array");
				[array addObject:form];
				s =[[NSMutableString alloc] initWithString: @""];
				nopen = nclosed = 0;
			}
		else if ((c = [formstring characterAtIndex:idx]) == ')') {
			nclosed++;//NOTE formstring is reversed
			[s appendFormat:@"%c",[formstring characterAtIndex:idx]];
		}
		else {
			[s appendFormat:@"%c",[formstring characterAtIndex:idx]];
		}
		idx++;
	 }

	//FIXME Lisp [fileName addStatus:HAVE_CLOSINGBRACE String:&st];
	NSLOG(@"Array of Forms done.");
	return array;

}
/*
- (int)hasSubForms:(NSString*)formstring
{
	NSMutableArray *array = [self splitForms:formstring];
	NSEnumerator *iter = [array objectEnumerator];
	Form *f;
	int n = -1;
	while (f = [iter nextObject])
		n++;
	if (n > -1)
		return n+2;//-1 and 0 
	else
		return -1;
}
*/
- (TupleInt*)hasSubForms:(NSString*)formstring
{
	NSMutableArray *array = [self splitForms:formstring];
	NSEnumerator *iter = [array objectEnumerator];
	Form *f;
	int n = -1;
	while (f = [iter nextObject]) {//TODO better implementation
		if ([formstring compare:[f string]] == 0)
			return [[TupleInt alloc] addFirst:-1 andSecond:nil];
		n++;
	}
	if (n > -1)
		//n+2, -1 and 0 
		return [[TupleInt alloc] addFirst:n+1 andSecond:array];
	else
		return [[TupleInt alloc] addFirst:-1 andSecond:nil];
}


- (int) parsePlus:(TupleInt*)ti
{					
	switch (((TYPE)[self getTypeOfString:[ti second]])) {
		
	case (const TYPE)ctype:{ //NOTE character (conversion from char to int - ascii)
		int a = atoi([[ti second] UTF8String]);
		NSString *s = [NSString stringWithFormat:@"%d",a];
		NSLOG2(@"converted ascii a=%@",s);
		[_machine pushOperatorPlusConstant:s];
		//TODO [self setLastSymbol:s2];
		return 0;
		break;
	}
	case (const TYPE)itype:{ //integer
		Hex* varhex = [[Hex alloc] ctorString:[ti second]];
		Symbol *s2 = [_symboltable searchForHex: varhex ];
		int address; 
		if (s2 == nil)
			address = -1;
		else
			address = [[s2 address] number];

		NSLOG2(@"address=%d",address);

		if (address > -1) //symbol exists
			[_machine pushOperatorPlusSymbol:[s2 address]];
		else				
			[_machine pushOperatorPlusConstant:[ti second]];
		[self setLastSymbol:s2];
		return 0;
		break;
	}
	case (const TYPE)ftype: //float
	//[_machine pushOperatorPlusConstant:[ti second]];//TODO foating point unit code
		break;
	case (const TYPE)symtype:
		default:{

			Hex* varhex = [[Hex alloc] ctorString:[ti second]];
			Symbol *s2 = [_symboltable searchForHex: varhex ];
			int address; 
			if (s2 == nil)
				address = -1;
			else
				address = [[s2 address] number];
			NSLOG2(@"address2=%d",address);
			if (address > -1) {//symbol exists
							
				[_machine pushOperatorPlusSymbol:[s2 address]];
				[self setLastSymbol:s2];
				return 0;
			} else {
				//symbol does not exist
				//thus can not be computed
				//TODO [self setLastSymbol:s2];
				NSLOG2(@"Invalid Types for + operator, TODO : no float type=%d", [self getTypeOfString:[ti second]]);
				//[form addError:
				return -1;
			}
			break;
		}
	}
	return -1;
}

- (int) parseMin:(TupleInt*)ti
{					
	switch (((TYPE)[self getTypeOfString:[ti second]])) {
		
	case (const TYPE)itype:{ //integer
		Hex* varhex = [[Hex alloc] ctorString:[ti second]];
		Symbol *s2 = [_symboltable searchForHex: varhex ];
		int address; 
		if (s2 == nil)
			address = -1;
		else
			address = [[s2 address] number];

		NSLOG2(@"address=%d",address);

		if (address > -1) //symbol exists
			[_machine pushOperatorMinusSymbol:[s2 address]];
		else				
			[_machine pushOperatorMinusConstant:[ti second]];
		return 0;
		break;
	}
	case (const TYPE)ftype: //float
	//[_machine pushOperatorMinusConstant:[ti second]];//TODO foating point unit code
		break;
	case (const TYPE)symtype:
		default:{
			Hex* varhex = [[Hex alloc] ctorString:[ti second]];
			Symbol *s2 = [_symboltable searchForHex: varhex ];
			int address;
			if (s2 == nil) 
				address = -1;
			else
				address = [[s2 address] number];
			if (address > -1) {//symbol exists
							
				[_machine pushOperatorMinusSymbol:[s2 address]];
				return 0;
			} else {
				//symbol does not exist
				//thus can not be computed
				NSLOG(@"Invalid Types for - operator, TODO : no float");
				//[form addError:
				return -1;
			}
			break;
		}
	}
	return -1;
}

- (int) parseMul:(TupleInt*)ti
{					
	switch (((TYPE)[self getTypeOfString:[ti second]])) {
		
	case (const TYPE)itype:{ //integer
		Hex* varhex = [[Hex alloc] ctorString:[ti second]];
		Symbol *s2 = [_symboltable searchForHex: varhex ];
		int address; 
		if (s2 == nil)
			address = -1;
		else
			address = [[s2 address] number];

		NSLOG2(@"address=%d",address);

		if (address > -1) //symbol exists
			[_machine pushOperatorMulSymbol:[s2 address]];
		else				
			[_machine pushOperatorMulConstant:[ti second]];
		return 0;
		break;
	}
	case (const TYPE)ftype: //float
	//[_machine pushOperatorMulConstant:[ti second]];//TODO foating point unit code
		break;
	case (const TYPE)symtype:
		default:{
			Hex* varhex = [[Hex alloc] ctorString:[ti second]];
			Symbol *s2 = [_symboltable searchForHex: varhex ];
			int address;
			if (s2 == nil) 
				address = -1;
			else
				address = [[s2 address] number];
			if (address > -1) {//symbol exists
							
				[_machine pushOperatorMulSymbol:[s2 address]];
			} else {
				//symbol does not exist
				//thus can not be computed
				NSLOG(@"Invalid Types for * operator, TODO : no float");
				//[form addError:
				return -1;
			}
			return 0;
			break;
		}
	}
	return -1;
}

-(int) skipWordAndWhiteSpace:(Form*)form withIndex:(int)idx
{
	//skip "first word"
	TupleInt *ti = [self grepWordOfLineParens:[form string] withIndex:idx];
	//skip prevailing whitespace
	NSLOG2(@"skip = %@",[ti second]);
	TupleInt *ti2 = [self skipWhiteSpace:[form string] withIndex:[ti first]];
	return [ti2 first];
}

-(int) skipFormAndWhiteSpace:(Form*)form withIndex:(int)idx
{
	int nopen = 0, nclosed = 0;
	int pidx = idx;

	if (idx > [form string])
		return -1;

	while (idx < [[form string] length]) {
		char c = [[form string] characterAtIndex:idx];
		if (c == '(')
			nopen ++;
		if (c == ')') {
			nclosed ++;
	
			if (nclosed == nopen && nopen > 0) {
				idx++;
				TupleInt *ti = [self skipWhiteSpace:[form string] withIndex:idx];
				return [ti first];
			}
		}
		//skip prevailing whitespace
		NSLOG2(@"skipForm = %c",c);
		idx++;
	}
	return idx;
}

@end
