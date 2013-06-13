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


#import "GameView.h"
#import "GameSubView.h"
#import "FirstViewController.h"

@implementation GameView

@synthesize redButton,greenButton,blueButton;//The GameView is the first responder for these buttons

- (id) alloc
{
	[super alloc];
	[self setNeedsDisplay:YES];
	
	return self;
}

- (id) init
{
	//[super alloc];
	//[self initWithFrame:CGRectMake(0,0,16*16,16*16)];
	
	//controller = p;
	
	x = 0;
	y = 0;
	w = 16*16;
	h = 16*16;
	
	[[UIColor redColor] set];
	self.backgroundColor = [UIColor redColor];
	
	UIImage *image = [UIImage imageNamed:@"KinkakuJi"];
	self.image = image;
	//UIImage *image2 = [UIImage imageNamed:@"t16tiles"];
	//self.animationImages = [NSArray new];
	//[self.animationImages addObject:image];
	//[self.animationImages addObject:image2];
	
	//map = [[ Map alloc] ctor];
	
}
- (void)drawRect:(CGRect)rect
{
	CGContextRef *context = UIGraphicsGetCurrentContext();
	
	[[UIColor redColor] set];
	self.backgroundColor = [UIColor redColor];

//	CGContextRef *context = UIGraphicsGetCurrentContext();
	UIImage *image = [UIImage imageNamed:@"KinkakuJi"];
	self.image = image;
	
	//UIImage *image = [UIImage imageNamed:@"KinkakuJi"];
	//[image drawInRect:rect];
	//[self setNeedsDisplay:YES];
	//GSRectfill(0,0,100,100);
	
	//[((FirstViewController*) controller) doRedButton];
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
//	UITouch *touch = [[event allTouches] anyObject];
//	CGPoint touchLocation = [touch locationInView:self.view];//TODO self.view
	
	//if (CGRectContainsPoint(self.window.frame, touchLocation)) {
	//x += 10;
	//y += 10;
	
	//[((FirstViewController*) controller) setx:x y:y];
	//[((FirstViewController*) controller) move];
	//dragging = YES;
	//}
	
	//UIImage *image = [UIImage imageNamed:@"t16tiles"];//[map render];
	//[controller setImage:image];
	
	
	//[controller getImageView].backgroundColor = [UIColor blackColor];
	//self.imageView.clipsToBounds = YES;
	
	//self.imageView.image = image;
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{}


- (int) getx
{
	return x;
}

-(int) gety
{
	return y;
}

//GameView is first responder
- (IBAction)doRedButton{ 
	
	//[self setNeedsDisplay:YES];
	
	int i = 0, j = 0;
	for ( ; i < 16; i++) {
		for ( ; j < 16; j++) {
			
			//CGRect frame;
			//(	subviews[i][j]).image.frame.origin = CGPointMake(j*16+x, i*16+y);
			//frame.size.width = frame.size.height = 16;
			
			subviews[i][j].center = CGPointMake(0,0);//j*16+x, i*16+y);
			[subviews[i][j] initWithImage: [UIImage imageNamed:@"tile-grass-3-16x16"]];
			[subviews[i][j] setNeedsDisplay:YES];
			//subviews[i][j].center = CGPointMake(((int)[subviews[i][j] getx]+x), ((int)[subviews[i][j] gety]+y));
			//[subviews[i][j] setNeedsDisplay:YES];
			
		}
		j = 0;
	}
	
	//x -= 10;
	
	//[((FirstViewController*) controller) doRedButton]; 
	//self.center = CGPointMake(0,0);
	
	//UIImageView* view = [controller getImageView];
	//view.center = CGPointMake(0, 0);
	//[self setNeedsDisplay:YES];
	/*
	NSArray *array = [self subviews];
		 
	NSEnumerator *e = [array objectEnumerator];
	id object;
	while (object = [e nextObject]) {
		//object.center = CGPointMake(0,0);
		//if ([self isKindOfClass:[GameSubView class]]) {
			//[((GameSubView*) object) foo];
		//[object.center = CGPointMake(0, 0)];
		//}
	}*/
}
-(void)addSubviewToArray:(GameSubView*)v
{
	subviews[((int)[v getx])%16][((int)[v gety])%16] = v;
}

- (IBAction)doGreenButton{  
	//x += 10;
	//self.center = CGPointMake(x, y);	
}
- (IBAction)doBlueButton{
	//y += 10;
	//self.center = CGPointMake(x,y); 
}

/*
-(void) keyDown: (NSEvent *)event
{
	//NSLog(@"%d %@",[event keyCode], [event characters]);
	
	switch ([[event characters] characterAtIndex:0])
	{
		case 'a':
			break;
	}
}*/

@end
