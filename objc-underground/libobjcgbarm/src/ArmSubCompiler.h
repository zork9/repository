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
#import "ArmSubScanner.h"
#import "ArmCompiler.h"
#import "ClassLocator.h"
#import "ErrorSubCompiler.h"

typedef struct RType { int id; NSString *rtypestring; } RType;

//auto- C in objC compiler or other langs with output to elf
@interface ArmSubCompiler : ArmCompiler {

	ArmSubScanner *_armSubScanner;
	NSString *_compilerShellCommand;
	ClassLocator *_classLocator;

	ErrorSubCompiler *_errorsubcompiler;
}

- (ArmSubCompiler*)ctor:(NSString*)command;
- (void)erroradd:(int)ei;
- (int)errorset;
- (void)compile:(FNString*)fileName;//override for other compiler command
- (void)scanFile:(FNString*)fileName;
- (int)scanFileRec:(FNString*)fileName;
- (int)subCompilable:(FNString*)fileName;
- (int)subCompilableObjCSourceFile:(FNString*)fileName;
//pure C in method definitions ->
- (int)subCompilableRec:(FNString*)pstr withIndex:(int)idx;
//non-pure C but objC in method definitions ->
- (int)compileRec:(FNString*)fileName;
- (int)compileObjC:(int)idx;

- (int)compilablesource:(FNString*)fileName;

- (int) scanObjCMethodDeclarationIn:(FNString*)pstr withIndex:(int)idx fino:(int)fno;
- (int) scanDeclarationForType:(NSString*)pstr withIndex:(int)idx returns:(struct RType*)rType;
- (int) scanDeclarationForFuncName:(NSString*)pstr withIndex:(int)idx returns:(NSString*)rName;
- (int) scanDeclarationForArgs:(NSString*)pstr withIndex:(int)idx returns:(NSMutableArray*)rArgs;

- (int) writeDeclarationWithReturnTypeToHeader:(struct RType*)returnType withFuncName:(NSString*)funcName andArgs:(NSMutableArray*)Args onfno:(int)fno;

@end
