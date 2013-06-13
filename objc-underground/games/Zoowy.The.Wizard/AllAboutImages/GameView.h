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

#import <UIKit/UIKit.h>
//#import <EventKitUI/EventKitUI.h>
#import "Map.h"
@class GameSubView;

#define SCREENWIDTH 16*8
#define SCREENHEIGHT 16*8

@interface GameView : UIImageView {
	int x,y,w,h;
	UIViewController* controller;
	UIButton *redButton;
	UIButton *greenButton;
	UIButton *blueButton;
	
	//UIWindow *window;
	GameSubView *subviews[16][16];
}


@property (nonatomic,retain) IBOutlet UIButton *redButton;
@property (nonatomic,retain) IBOutlet UIButton *greenButton;
@property (nonatomic,retain) IBOutlet UIButton *blueButton;

- (IBAction)doRedButton;
- (IBAction)doGreenButton;
- (IBAction)doBlueButton;

- (id) init;
- (void)drawRect:(CGRect)rect;
//-(void) keyDown: (NSEvent *)event;

@end
