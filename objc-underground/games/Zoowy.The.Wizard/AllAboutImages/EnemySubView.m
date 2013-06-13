/*
 Copyright (C) 2013 Johan Ceuppens
 
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
// Copyright (c) 2011 iOSDeveloperZone.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#import "EnemySubView.h"
#import "FirstViewController.h"

@implementation EnemySubView

- (id) alloc
{
	[super alloc];
	[self setNeedsDisplay:YES];

	return self;
}

- (id) initx:(int)xx y:(int)yy w:(int)ww h:(int)hh
{
	
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	
	return self;
}

- (void)setx:(int)xx y:(int)yy
{
	x = xx;
	y = yy;
}

- (void)drawRect:(CGRect)rect
{
	int r  = rand();
	
	if (r < RAND_MAX/4) {
		x += 3;
		direction = @"right";
	}
	else if (r < RAND_MAX/2) {
		x -= 3;
		direction = @"left";
	}
	else if (r < RAND_MAX/4*3) {
		y += 3;
		direction = @"down";
	}
	else if (r < RAND_MAX) {
		y -= 3;
		direction = @"up";
	}
	else 
		x += 3;
	
	//x += 10;
	self.center = CGPointMake(x+IPADXOFFSET, y+IPADYOFFSET);
	if ([direction compare:@"left"] == 0)
		self.image = [UIImage imageNamed:@"skeleton-left-1-32x32"];//TODO put in class
	else if ([direction compare:@"right"] == 0)
		self.image = [UIImage imageNamed:@"skeleton-right-1-32x32"];
	else if ([direction compare:@"up"] == 0)
		self.image = [UIImage imageNamed:@"skeleton-up-1-32x32"];
	else if ([direction compare:@"down"] == 0)
		self.image = [UIImage imageNamed:@"skeleton-down-1-32x32"];
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 100000000;
	nanosleep(&ts,NULL);


	CGContextRef *context = UIGraphicsGetCurrentContext();
	
	
	NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(moveThread) object:nil];
	[thread start];
	
}

-(void)moveThread
{
	
		//enemysubview.center = CGPointMake(xoffset+IPADXOFFSET, yoffset+IPADYOFFSET);
		[self drawRect:CGRectMake((int)[self getx],(int)[self gety],16,16)];
		[self setNeedsDisplay];
	
}

@end
