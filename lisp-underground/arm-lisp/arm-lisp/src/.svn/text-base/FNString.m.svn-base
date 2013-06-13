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


#import "FNString.h"
#import "TupleIterator.h"

@implementation FNString

- (FNString*)ctor:(NSString*)filename {
	_filename = filename;
	_filebuffer = nil;//[[FileBuffer alloc] ctor:@""];
	_errorobj = [Error new];
	_statusobj = [Status new];
			
	return self;
}

- (FileBuffer*)buffer {
	if (_filebuffer != nil)
		return _filebuffer;
	return nil;
}

- (NSString*)bufferstring {
	if (_filebuffer != nil)
		return [_filebuffer string];
	return nil;
}

- (int) scan {
	
//	if (_filebuffer == (FileBuffer *)0)
//		[_filebuffer init];
	
	//FIXME put int thread
	//FIXME2 ecl
	[self readInFile];
	[self scancompile];
	
	//fprintf(stdout, "%c", [fileBuffer characterAtIndex: 0]);
	
	
	return 0;
}


- (int) readInFile {
	
	FILE *fp;
	NSLOG(@"reading in file...");	
	if ((fp = fopen([_filename UTF8String], "r")) == (FILE *)0) {
		fprintf(stderr, "- file scanner : cannot read in file."); 
		return -1;
	}
	
	if (flock(fileno(fp), LOCK_SH) < 0) {
		fprintf(stderr, "- file scanner : cannot lock shared lock.");
		return -1;
	}

	//code block
	fseek(fp, 0L, SEEK_END);
	long max = ftell(fp);
	long pos = 0;//ftell(fp);
	fseek(fp, max, SEEK_SET);
	pos = ftell(fp);
	pos-=2;
	//read in file le
	NSMutableString *s = [[NSMutableString alloc] initWithString:@""];
	//unichar c;
	char c;
	//pos--;
	//while (fseek(fp, pos--,SEEK_END) && pos >= 0 && (c = fgetc(fp))) {
	while (fseek(fp, pos,SEEK_SET) == 0 && pos >= 0  && (c = getc(fp))) {

		//_filebuffer = (FileBuffer *)[_filebuffer stringByAppendingString: [NSString stringWithCharacters:&c length: 1]];
		[s appendFormat:@"%c",c];
		//printf("c=%c pos=%d\n",c,pos);
		//printf("s=%s\n",(char*)([s UTF8String]));
		//NSLog(@"c++");
		pos--;	
	}
	if (flock(fileno(fp), LOCK_UN) < 0) {
		fprintf(stderr, "- file scanner cannot unlock shared lock.");
		return -1;
	}
	if (!fclose(fp)) {
		NSString *st;
		//st = [NSString stringWithFormat:@"reading file done : %@", s];
		//NSLog(st);
		_filebuffer = [[FileBuffer alloc] ctor:s];	
		return 0;
	} else {
		fprintf(stdout, "- file scanner : cannot close readin file."); 
		return -1;
	}
	return -1;
}

- (int) scancompile{

	//FIXME err struct
	if (_filebuffer == (FileBuffer *)0)
		return -1;
	
	//compiler = [ Compiler new ]; 
	//[scancompiler compile: _filebuffer ]; 
	
	return 0;
	
}

- (int) isheader {
	
	if ([self length] < 2)
		return -1;
	
	if ([self characterAtIndex: ([self length]-1)] == 'h' 
		&&
		[self characterAtIndex: ([self length]-2)] == '.')
		return 0;
	
	return -1;
}

- (int) issource {
	
	if ([self length] < 2)
		return -1;
	
	if ([self characterAtIndex: ([self length]-1)] == 'm'
		&&
		[self characterAtIndex: ([self length]-2)] == '.')
		return 0;
	
	return -1;
}

- (int) isCHeader {
	
	if ([self length] < 2)
		return -1;
	
	if ([self characterAtIndex: ([self length]-1)] == 'h' 
		&&
		[self characterAtIndex: ([self length]-2)] == '.')
		return 0;
	
	return -1;
}

- (int) isCSource {
	
	if ([self length] < 2)
		return -1;
	
	if (//([self characterAtIndex: ([self length]-1)] == 'cc' 
		 /*||*/ [self characterAtIndex:([self length]-1)] == 'c'
		 //|| [self characterAtIndex:([self length]-1)] == 'cpp'
		
		&&
		[self characterAtIndex: ([self length]-2)] == '.')
		return 0;
	
	return -1;
}


- (void) addStatus:(int)s {
	
	[_statusobj addStatus:s ];

}

- (void) addStatusFirst:(int)status andSecond:(NSObject*)oi 
{
	[_statusobj addStatus:status withObject:oi ];
}

- (void)addStatus:(int)status String:(NSString**)s
{
	[_statusobj addStatusFirst:status andSecond:*s];
}

- (void)printStatus:(int)status
{

	Tuple *t = [_statusobj getObject:status];	
	TupleIterator *ti = [TupleIterator ctor:t];

	while (![ti atEnd]) {
		printf("%s", [[t second] UTF8String]);
		t = [ ti next ];		
	}

}

- (void) addError:(int)e {
	
	[_errorobj addError:e ];
	
}

- (NSString*)stringFromIndex:(int)start toIndex:(int)end {
	int i = start-1;
	NSString *str = [[NSString alloc] initWithString:@""];
	while (i < end) {
		str += [[self bufferstring] characterAtIndex:i++];
	}
	
	return str;
}

- (void)addErrors:(Error*)err {

	NSEnumerator *e = [[err getErrors] objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		[_errorobj addErrorTuple: object];
	}

}

- (Tuple*)getLastStatus
{

	Tuple *t = [_statusobj getObject:[_statusobj length]];	
	return t; 

}

@end
