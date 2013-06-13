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
#import "arm-lisp-config.h"
#import "ArmCompiler.h"
#import "TypeTable.h"
#import "SymbolTable.h"
#import "OperatorTable.h"
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
};

enum {
	SYMBOL_ASSIGNMENT = '=',
};

@interface ArmLispCompiler : ArmCompiler {

	ByteCodeMachine* _machine;

	OperatorTable *_operatortable;
	SymbolTable* _symboltable;
	TypeTable *_typetable;
	TupleInt *_parsetreestatus;

	Symbol* _lastsymbol;
}

- (ArmLispCompiler*)ctor:(MACHINETYPE)i;
- (int)grepLines:(NSString *)fileName; 
- (TupleInt*)grepWord:(FNString *)fileName withIndex:(int)idx;
- (TupleInt*)getRestOfForm:(NSString*)formstring withIndex:(int)idx;
- (TupleInt*) parsehexandset:(int)h; 
- (TYPE)checkTypeOf:(Symbol*)s and:(TYPE)t;
- (TYPE)getTypeOf:(NSString*)s;

- (int)compilablesource:(NSString*)fileName;
- (int) parseFile:(FNString*)fileName withIndex:(int)idx; 
- (int) parseForms:(FNString*)fileName withIndex:(int)idx; 
- (NSMutableArray*)splitForms:(NSString*)line;
- (int) parseLineForAssignment:(NSString*)line;
- (int) parseFormForDefinition:(Form*)form;
- (int) parseFormForOperator:(Form*)form;
- (int) parsePlus:(TupleInt*)ti;
- (int) parseLineForAssignmentWithOperator:(NSString*)line;
- (int) parseForm:(FNString*)fileName withIndex:(int)idx;
- (int) parseDefinitionOfdeftype:(TupleInt*)status;
- (int) parseDefinitionOfdefvar:(TupleInt*)status hex:(Hex*)hex;
- (int) parseDefinitionOfdefvarWithForm:(TupleInt*)sym and:(TupleInt*)val;
- (int) parseDefinitionOfsetq:(TupleInt*)status hex:(Hex*)hex;
- (int) parseDefinitionOfsetf:(TupleInt*)status hex:(Hex*)hex;
- (int) parseOperator:(NSString*)op withAddress:(Hex*)addr;
- (int) parseOperator:(NSString*)op withAddress:(Hex*)addr andAddress:(Hex*)addr2;
- (int)parseOperator:(NSString*)op form:(Form*)form;
- (int) parseAssignment:(TupleInt*)status withOp:(TupleInt*)value;

- (int) setLastSymbol:(Symbol*)s;

- (int)hasSubForms:(NSString*)formstring;
@end
