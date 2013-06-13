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
#ifndef _FILENAMESTREAM_H_
#define _FILENAMESTREAM_H_

#import <Foundation/Foundation.h>
#include <sys/file.h>

@interface FileNameStream : NSObject {

	FILE *_fp;

}

- (FileNameStream*)ctor;
- (int)open:(NSString*)filename;
- (char) get;
- (char) get:(int)index;
- (int)close;

@end

#endif