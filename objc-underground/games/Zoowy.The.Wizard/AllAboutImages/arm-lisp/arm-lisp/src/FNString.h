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

/*
 * filename String : file buffer agent
 */
#ifndef _FNSTRING_H_
#define _FNSTRING_H_

#import <Foundation/Foundation.h>
//#import "../../liblisparm/FileBuffer.h"
#import "FileBuffer.h"
#import "ScanSystem.h"
#import "Error.h"
#import "Status.h"
#include <sys/file.h>

@interface FNString : NSObject {
	NSString *_filename;	
	FileBuffer *_filebuffer;
	Error *_errorobj;
	Status *_statusobj;
	//ScanSystem *scansys;
	
}

- (FNString*)ctor:(NSString*)filename;

- (FileBuffer*)buffer;
- (NSString*)bufferstring;

- (int) scan;
- (int) scancompile;
- (int) readInFile;
- (int) isheader;//should be fuzzynated
- (int) issource;
- (int) isCHeader;
- (int) isCSource;
- (void) addStatus:(int)status;//FIXME obj instead of int
- (void) addStatusFirst:(int)status andSecond:(NSObject*)oi;//FIXME obj instead of int

- (void)addStatus:(int)status String:(NSString**)s;
- (void)printStatus:(int)status;

- (void) addError:(int)e;
- (void) addErrors:(Error*)err;

- (NSString*)stringFromIndex:(int)start toIndex:(int)end;

- (Tuple*)getLastStatus;

@end

#endif
