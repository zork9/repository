//
//  HashTableTupleInts.h
//  libobjcgbarm
//
//  Created by link on 25/10/12.
//  Copyright 2012 vub. All rights reserved.
//

#ifndef _GBAO_HASHTABLESTRINGS_H_
#define _GBAO_HASHTABLESTRINGS_H_

#import <Cocoa/Cocoa.h>
#import "HashTable.h"


@interface HashTableTupleInts : HashTable {

}

- (int)matchWithKey:(int)key returns:(NSString*)rString;
- (HashTableTupleInts *)ctor:(int)sz;

@end
#endif
