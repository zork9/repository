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


#import "FirstViewController.h"
#import "GameSubView.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#import "ArmLispCompiler.h"

@implementation FirstViewController
@synthesize imageView = mImageView;

@synthesize window;
@synthesize redButton,greenButton,blueButton,alphaButton,interactButton;

void *routine2(void *data) {
	int xx = 0,yy = 0;
	//struct timeval tv;
	struct timespec ts;
	//gettimeofday(&tv, NULL);
	ts.tv_sec = 0;
	ts.tv_nsec = 100000000;
	
	int t = 0;
	
	//while (1) 
	{
		//xx += 10;
		//[data setx:xx y:yy];
		//[data setImage];
		int r  = rand();
		
		if (r < RAND_MAX/4)
			xx += 32;
		else if (r < RAND_MAX/2)
			xx -= 32;
		else if (r < RAND_MAX/4*3)
			yy += 32;
		else if (r < RAND_MAX)
			yy -= 32;
		else {
			xx += 32;
		}

		//nanosleep(&ts,NULL);
		[data moveEnemyx:xx y:yy];
		//[data setNeedsReDisplay:YES];
		/*if ([data moveEnemyx:xx y:yy] == 0)
			continue;
		else {
			break;
		}*/

	}
	
	return NULL;						 
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];

	fx = 0.0;
	nenemysubviews = 0;
	//self.imageView = [self.imageView initx:0 y:0 w:16 h:16 controller:self];
	//self.imageView = [self.imageView init];
	//[self.imageView initWithFrame:CGRectMake(0,0,16*16,16*16)];
	
	map = [[Map new] ctor];
	player = [[Player new] ctor];
	enemy = [[Enemy new] ctor];
	
	x = 0;
	y = 0;
	xoffset = x;
	yoffset = y;
	[[UIColor redColor] set];
	self.imageView.backgroundColor = [UIColor redColor];
	//self.imageView.backgroundColor = [UIColor redColor];
	
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
			GameSubView* subview = [[GameSubView alloc] initWithFrame:CGRectMake(j*16+IPADXOFFSET, i*16+IPADYOFFSET, 16, 16)];
			
			//subview = [subview init:self.imageView];
			subview.image = [map renderx:j y:i];
			/*if (j == 7 && i == 7)
				subview.image = [player render:1];
			else if (j == 8 && i == 7)
				subview.image = [player render:2];
			else if (j == 7 && i == 8)
				subview.image = [player render:3];
			else if (j == 8 && i == 8)
				subview.image = [player render:4];
			*///else
			//	subview.image = [map renderx:j y:i];
			
			subview = [subview initx:j*16 y:i*16 w:16 h:16 controller:self];
			
			//[subview setNeedsReDisplay:YES];
			[self.imageView addSubview:subview];
			[self.imageView addSubviewToArray:subview];
			subviews[i][j] = subview;
			
		}
		j = 0;
	}

	GameSubView* subview = [[GameSubView alloc] initWithFrame:CGRectMake(7*16+IPADXOFFSET, 7*16+IPADYOFFSET, 32, 32)];
	subview = [subview initx:7*16+IPADXOFFSET y:7*16+IPADYOFFSET w:32 h:32 controller:self];
	subview.image = [player render:1];
	playersubviews[0] = subview;
	[self.imageView addSubview:subview];
	
	EnemySubView* subview2 = [[EnemySubView alloc] initWithFrame:CGRectMake(0*16+IPADXOFFSET, 0*16+IPADYOFFSET, 32, 32)];
	subview2 = [subview2 initx:0*16+IPADXOFFSET y:0*16+IPADYOFFSET w:32 h:32];
	subview2.image = [enemy render:1];
	enemysubviews[nenemysubviews++] = subview2;
	[self.imageView addSubview:subview2];
	

	
	//while () {
		/*
		struct timespec ts;
		//gettimeofday(&tv, NULL);
		ts.tv_sec = 0;
		ts.tv_nsec = 100000000;
		
	pthread_attr_t attr;
	pthread_t pid;
	int ret;
	
	ret = pthread_attr_init(&attr);
	
	assert(!ret);
	
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	assert(!ret);
	
	int er = pthread_create(&pid, &attr, &routine2, self);
	
	ret = pthread_attr_destroy(&attr);
	
	assert(!ret);
	
	if (er != 0) {
		
		//raise error
		exit(0);
		
	}

	nanosleep(&ts,NULL);
	//}
		 */
	
//	NSString *filename = [[NSString alloc] initWithString:@"/Users/link/ios/examples/AllAboutImages1/AllAboutImages/test.lisp"];
	NSString *filename = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"lisp"];
	//NSString *filename = [[NSString alloc] initWithString:@"test.lisp"];


	
	ArmLispCompiler *armlispcompiler = [[ArmLispCompiler alloc] ctor:HAVE_MACHINE_ARMASM];
	[armlispcompiler compilablesource:filename];
	
	
	//NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(moveEnemies) object:nil];
	//[thread start];
	int ii = 0;
	while (ii < nenemysubviews) {
		enemysubviews[ii].center = CGPointMake(xoffset+IPADXOFFSET, yoffset+IPADYOFFSET);
		[enemysubviews[ii] drawRect:CGRectMake((int)[enemysubviews[ii] getx],(int)[enemysubviews[ii] gety],16,16)];
		[enemysubviews[ii] setNeedsDisplay];
		ii++;
	}
	
	
	
}

- (UIImageView*)getImageView
{
	return self.imageView;
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload
{
    self.imageView = nil;
    [super viewDidUnload];
}


- (void)dealloc
{
    [mImageView release];
    [super dealloc];
}

// MARK: -
// MARK: UI Actions
- (IBAction)contentModeChanged:(UISegmentedControl *)segmentedControl
{
	
	switch(segmentedControl.selectedSegmentIndex)
    {
			
		self.imageView.backgroundColor = [UIColor blackColor];
			
        case 0:{
			
            break;
		}
        case 1:
            //self.imageView.contentMode = UIViewContentModeScaleAspectFit;
			//subviews[0][0].contentMode = UIViewContentModeScaleAspectFit;
            break;
        case 2:
			//x -= 10;
			//y -= 10;
			//[self move];
            //self.imageView.contentMode = UIViewContentModeScaleAspectFill;
			//subviews[0][0].contentMode = UIViewContentModeScaleAspectFill;
            break;
    }
}

- (void)move
{
	self.imageView.backgroundColor = [UIColor blackColor];

	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
		
			//CGRect frame;
		//(	subviews[i][j]).image.frame.origin = CGPointMake(j*16+x, i*16+y);
		//frame.size.width = frame.size.height = 16;
		
			//subviews[i][j].center = CGPointMake(j*16+x, i*16+y);
			//subviews[i][j].center = CGPointMake(((int)[subviews[i][j] getx]+x), ((int)[subviews[i][j] gety]+y));
			//[subviews[i][j] setNeedsDisplay:YES];
		
		}
		j = 0;
	}
}


- (void) setx:(int)xx y:(int)yy
{
	x = xx;
	y = yy;
}

- (void)setImage:(UIImage*)img
{
	self.imageView.image = img;
}

//left
- (IBAction)doRedButton{ 
	[player setDirection:@"left"];
	playersubviews[0].image = [player render:1];
	//exit(0);
	int offset = 10;
	x += offset;
	self.imageView.backgroundColor = [UIColor blackColor]; 
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
		
			//subviews[i][j].image = [map renderx:j y:i];
			subviews[i][j].center = CGPointMake(j*16+x+IPADXOFFSET, i*16+y+IPADYOFFSET);
			
		}
		j = 0;
	}
	
	//for ( ; i < 1000000; i++) {
	//	enemysubview.image = [enemy render:1];
	//xoffset += 32;
	int ii = 0;
	while (ii < nenemysubviews) {
		int ex = [enemysubviews[ii] getx];
		int ey = [enemysubviews[ii] gety];
		//enemysubviews[ii].center = CGPointMake(ex-x+IPADXOFFSET,ey+IPADYOFFSET);
		[enemysubviews[ii] setNeedsDisplay];
		[enemysubviews[ii] setx:ex+offset y:ey];
		ii++;
	}
		//[self.imageView setNeedsDisplay:YES];
		//[enemysubviews[0][0] setNeedsDisplay:YES];
	//}
	//[enemysubview setNeedsDisplay:YES];
}

//right
- (IBAction)doGreenButton{
	[player setDirection:@"right"];
	playersubviews[0].image = [player render:1];
	//exit(0);
	int offset = 10;
	x -= offset;
	self.imageView.backgroundColor = [UIColor redColor]; 
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
			
			subviews[i][j].center = CGPointMake(j*16+x+IPADXOFFSET, i*16+y+IPADYOFFSET);
			
		}
		j = 0;
	}
	int ii = 0;
	while (ii < nenemysubviews) {
		int ex = [enemysubviews[ii] getx];
		int ey = [enemysubviews[ii] gety];
		//enemysubviews[ii].center = CGPointMake(ex+offset+IPADXOFFSET,ey+IPADYOFFSET);
		[enemysubviews[ii] setNeedsDisplay];
		[enemysubviews[ii] setx:ex-offset y:ey];
		ii++;
	}
}
//move up
- (IBAction)doBlueButton{ 
	[player setDirection:@"up"];
	playersubviews[0].image = [player render:1];
	//exit(0);
	int offset = 10;
	y += offset;
	self.imageView.backgroundColor = [UIColor redColor]; 
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
			
			subviews[i][j].center = CGPointMake(j*16+x+IPADXOFFSET, i*16+y+IPADYOFFSET);
			
		}
		j = 0;
	}
	int ii = 0;
	while (ii < nenemysubviews) {
		int ex = [enemysubviews[ii] getx];
		int ey = [enemysubviews[ii] gety];
		//enemysubviews[ii].center = CGPointMake(ex+offset+IPADXOFFSET,ey+IPADYOFFSET);
		[enemysubviews[ii] setNeedsDisplay];
		[enemysubviews[ii] setx:ex y:ey+offset];
		ii++;
	}
}
//move down
- (IBAction)doAlphaButton{ 
	[player setDirection:@"down"];
	playersubviews[0].image = [player render:1];
	//exit(0);
	int offset = 10;
	y -= offset;
	self.imageView.backgroundColor = [UIColor redColor]; 
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
			
			subviews[i][j].center = CGPointMake(j*16+x+IPADXOFFSET, i*16+y+IPADYOFFSET);
			
		}
		j = 0;
	}
	int ii = 0;
	while (ii < nenemysubviews) {
		int ex = [enemysubviews[ii] getx];
		int ey = [enemysubviews[ii] gety];
		//enemysubviews[ii].center = CGPointMake(ex+offset+IPADXOFFSET,ey+IPADYOFFSET);
		[enemysubviews[ii] setNeedsDisplay];
		[enemysubviews[ii] setx:ex y:ey-offset];
		ii++;
	}
}


//interact
- (IBAction)doInteractButton
{
	int ii = 0;
	while (ii < nenemysubviews) {
		
		int xx = [enemysubviews[ii] getx];
		int yy = [enemysubviews[ii] gety];
		int px = [playersubviews[0] getx];
		int py = [playersubviews[0] gety];
		if (abs(xx - px) < 100 && abs(yy - py) < 300)
				  [self interact];
		ii++;	
	}
}

- (void)interact
{
	exit(0);
}

-(void)moveEnemies
{
	NSRunLoop* loop = [NSRunLoop currentRunLoop];
	/*
	CFRunLoopObserverContext *context = (0,self,NULL,NULL,NULL);
	
	CFRunLoopObserverRef *observer = CFRunLoopObserverCreate(kCFAllocatorDefault, kCFRunLoopAllActivities, YES, 0, &myRunLoopObserver, &context);
	if (observer) {
		
		CFRunLoopRef cfLoop = [loop getCFRunLoop];
		CFRunLoopAddObserver(cfLoop, observer, kCFRunLoopDefaultMode);
	}
		
	[NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(doFireTimer:) userInfo:nil repeats:YES];
	*/
	
	NSDate *futureDate = [NSDate dateWithTimeIntervalSinceNow:1];
	NSTimer *timer = [[NSTimer alloc] initWithFireDate:futureDate interval:0.1 target:self selector:@selector(myDoFireTimer:) userInfo:nil repeats:YES];
	
	[loop addTimer:timer forMode:NSDefaultRunLoopMode];
	
	int count = 1;
	do {
		
	//xoffset += 32;
	//yoffset += 32;
		int ii = 0;
		while (ii < nenemysubviews) {
			enemysubviews[ii].center = CGPointMake(xoffset+IPADXOFFSET, yoffset+IPADYOFFSET);
			[enemysubviews[ii] drawRect:CGRectMake((int)[enemysubviews[ii] getx],(int)[enemysubviews[ii] gety],16,16)];
			[enemysubviews[ii] setNeedsDisplay];
			ii++;
		}
	//	struct timespec ts;
	//	//gettimeofday(&tv, NULL);
	//	ts.tv_sec = 0;
	//	ts.tv_nsec = 5000000;
		//nanosleep(&ts, NULL);
		
		//[loop runUntilDate:futureDate];//[NSDate dateWithTimeIntervalSinceNow:1]];
	//sleep(1);
	} while (count--);
}

- (int)moveEnemyx:(int)xx y:(int)yy 
{ 
	//exit(0);
	//fx += 0.1;
	
	/*int r  = rand();
	
	if (r < RAND_MAX/4)
		x += 1;
	else if (r < RAND_MAX/2)
		x -= 1;
	else if (r < RAND_MAX/4*3)
		y += 1;
	else if (r < RAND_MAX)
		y -= 1;
	*/
	//enemysubviews[0][0].image = [map renderx:j y:i];
	//xoffset += xx;
	//yoffset += yy;
	int ii = 0;
	while (ii < nenemysubviews) {
		enemysubviews[ii].center = CGPointMake(xoffset+IPADXOFFSET, yoffset+IPADYOFFSET);
	//sleep(1);
		ii++;
	}
	return 0;
/*	GameSubView* subview2 = [[GameSubView alloc] initWithFrame:CGRectMake(0*16+xx+IPADXOFFSET, 0*16+yy+IPADYOFFSET, 32, 32)];
	subview2 = [subview2 initx:0*16+xx+IPADXOFFSET y:0*16+yy+IPADYOFFSET w:32 h:32 controller:self];
	subview2.image = [enemy render:1];
	[enemysubview dealloc];
	enemysubview = subview2;
	[self.imageView addSubview:subview2];
*/	//[enemysubview setNeedsDisplay:YES];
	
}

@end
