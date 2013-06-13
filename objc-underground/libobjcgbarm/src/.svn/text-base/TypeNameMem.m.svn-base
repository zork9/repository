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

#import "TypeNameMem.h"
#import "string.h"

@implementation TypeNameMem

- (int) defineWithId:(int)typeid andName:(NSString*)name {
	_size = 1024;//FIXME C prog disease
	_data = calloc(_size, 1);
	 
	memmove(_data,typeid,sizeof(typeid));
	memset(_data,0,1);

	//put name in the back, reversed
	char **s;
	//ifdef ONARM char **s = &(char *)[[self reverse:name] UTF8String];
	*s = (char *)[[self reverse:name] UTF8String];
	memmove(_data+_size-sizeof(*s),*s,sizeof(*s));

	return 0;
	
}

//ctor
- (TypeNameMem *)ctor:(long int)i withTypeName:(NSString *)n {
	[super init];
	//////////////WRITETYPEMEM(name);

	[self defineWith:i andName:n];

	return self;
}

- (NSString *)string {

	char **s;
	*s = malloc(_size/2+1);
	memset(*s,0,_size/2+1);
	memcpy(*s, _data+_size/2,_size/2);	
	NSString *rs = [NSString new];
	[rs stringWithFormat:@"%@", *s];
	return [self reverse: rs];	
	
}

- (int)type {
	int **is;
	*is = malloc(_size/2+1);
	memcpy(*is,_data,_size/2);
	return *is;	
}

- (int) this:(TypeNameMem*) tn isa:(const char *)str {
	if (!strncmp(str,[[tn string] UTF8String],strlen(str)))
		return 0;
	else
		return -1;
}

- (int) subCompileSelfOn:(Disk*)disk {


	////[disk defineWith: _id and: _name toFormat:ELF];

	return 0;
}

- (int) subCompileSelfOn:(Disk*)disk withFormat:(int)fmt{
	////[disk defineWith: _id and: _name toFormat:fmt];
	
	return 0;
}

- (int)writeOn:(Disk*)disk data:(Data*)data{

	//FIXME [disk write:self data:[data data]];

}

- (NSString*)reverse:(NSString*)str {
        NSString *reversestr = @"";

        int l = [str length];
        int i = 0;
        while (i++ < l){
                reversestr += [str characterAtIndex:i];
        }

        return reversestr;
}

@end
