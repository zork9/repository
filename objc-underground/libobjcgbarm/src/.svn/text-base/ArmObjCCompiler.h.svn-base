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
#import "ArmCompiler.h"
#import "TypeTable.h"
#import "SymbolTable.h"
#import "ByteCodeMachine.h"

enum {
	NOENDOFIMPLEMENTATION = -2, 
	NOCLOSINGBRACE = -3,

};

enum {
	HAVE_ENDOFIMPLEMENTATION = 2,
	HAVE_OPENINGBRACE = 3,
	HAVE_CLOSINGBRACE = 4,
	HAVE_FILEPARSED = 5,
	HAVE_DEFINITION = 6,
	HAVE_OPERATOR = 7,
	HAVE_IF = 8,
	HAVE_ELSE = 9,
	HAVE_WHILE = 10,
};

enum {
	SYMBOL_ASSIGNMENT = '=',
};

@interface ArmObjCCompiler : ArmCompiler {

	ByteCodeMachine* _machine;

	SymbolTable* _symboltable;
	TypeTable *_typetable;
	TupleInt *_parsetreestatus;
	int _bracescodenumber; // must be zero after parsing a function, opening braces == closing braces
	Symbol* _lastsymbol;
}

- (ArmObjCCompiler*)ctor:(MACHINETYPE)i;
- (int)grepLines:(FNString *)fileName; 
- (TupleInt*)grepWord:(FNString *)fileName withIndex:(int)idx;
- (TupleInt*) parsehexandset:(int)h; 
- (int)checkTypeOf:(Symbol*)s and:(TYPE)t;

- (int)compilablesource:(FNString*)fileName;
- (int) parseLineForAssignment:(NSString*)line;
- (int) parseLineForOperator:(NSString*)line;
- (int) parseLineForAssignmentWithOperator:(NSString*)line;
- (int) parseMethodImpl:(FNString*)fileName withIndex:(int)idx;
- (int) parseDefinition:(TupleInt*)status;
- (int) parseOperator:(NSString*)op withAddress:(Hex*)addr;
- (int) parseOperator:(NSString*)op withAddress:(Hex*)addr andAddress:(Hex*)addr2;
- (int) parseAssignment:(TupleInt*)status withOp:(TupleInt*)value;

- (int) setLastSymbol:(Symbol*)s;
- (int)searchForBracesCode;

@end
