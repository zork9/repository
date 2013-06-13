/*
 Copyright (C) 2013 Johan Ceuppens
 
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#import "Enemy.h"
#include <pthread.h>
#include <assert.h>

void *routine(void *data) {
	int xx,yy;
	while (1) {
		xx += 10;
		[data setx:xx y:yy];
		[data setImage];
	}
							 
	 return NULL;						 
}

@implementation Enemy

- (id) ctor
{
	enemyImages[0] = [UIImage imageNamed:@"skeleton-down-1-32x32"];
	//playerImages[1] = [UIImage imageNamed:@"player-down-2-16x16"];
	//playerImages[2] = [UIImage imageNamed:@"player-down-3-16x16"];
	//playerImages[3] = [UIImage imageNamed:@"player-down-4-16x16"];
/*	pthread_attr_t attr;
	pthread_t pid;
	int ret;
	
	ret = pthread_attr_init(&attr);
	
	assert(!ret);

	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	assert(!ret);
	
	int er = pthread_create(&pid, &attr, &routine,self);
	
	ret = pthread_attr_destroy(&attr);
	
	assert(!ret);
	
	if (er != 0) {
		
	//raise error
		return nil;
		
	}
*/	
	return self;
}


- (UIImage*) render:(int)r
{
	switch (r) {
	case 1:
		return enemyImages[0];
		break;
	case 2:
		return enemyImages[0];
		break;
	case 3:
		return enemyImages[0];
		break;
	case 4:
		return enemyImages[0];
		break;
	default:
		return enemyImages[0];
			break;
	}
	//	}
	//}
	//return [UIImage imageNamed:@"tile-grass-1-16x16"];
}

- (void) setx:(int)xx y:(int)yy 
{
	x = xx;
	y = yy;
}

-(void) setImage
{
	enemyImages[0] = [UIImage imageNamed:@"KinkakuJi"];
	//[self setNeedsDisplay:YES];
}

@end
