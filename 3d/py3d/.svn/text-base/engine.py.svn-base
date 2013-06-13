### 3d.engine
###
### Copyright (c) 2011-2012 Johan Ceuppens
###
### All rights reserved.
###
### Redistribution and use in source and binary forms, with or without
### modification, are permitted provided that the following conditions
### are met:
### 1. Redistributions of source code must retain the above copyright
###    notice, this list of conditions and the following disclaimer.
### 2. Redistributions in binary form must reproduce the above copyright
###    notice, this list of conditions and the following disclaimer in the
###    documentation and/or other materials provided with the distribution.
### 3. The name of the authors may not be used to endorse or promote products
###    derived from this software without specific prior written permission.
###
### THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
### IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
### OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
### IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
### INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
### NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
### DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
### THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
### (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
### THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Copyright (C) Johan Ceuppens 2011

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import pygame, sys,os
from pygame.locals import *
import math
from vector3 import *
from matrix3 import *

class Engine():
    def __init__(self, screen):
	theta1 = self.theta1 = 3.0
	theta2 = self.theta2 = 3.0
	theta3 = self.theta3 = 3.0
	self.mx = Matrix3(1,0,0,
			0,math.cos(theta1),-math.sin(theta1),
			0,math.sin(theta1),math.cos(theta1))
	self.my = Matrix3(math.cos(theta2)/1.0,0, math.sin(theta2)/1.0,
			0,1,0,
			-math.sin(theta2),0, math.cos(theta2))
	self.mz = Matrix3(math.cos(theta3)/1.0, -math.sin(theta3)/1.0, 0,
			math.sin(theta3)/1.0, math.cos(theta3)/1.0, 0,
			0,0,1)
	self.screen = screen
	self.color = (255,255,255)

    def rotate(self, t1,t2,t3):
	self.mx = Matrix3(1,0,0,
			0,math.cos(t1),-math.sin(t1),
			0,math.sin(t1),math.cos(t1))
	self.my = Matrix3(math.cos(t2)/1.0,0, math.sin(t2)/1.0,
			0,1,0,
			-math.sin(t2),0, math.cos(t2))
	self.mz = Matrix3(math.cos(t3)/1.0, -math.sin(t3)/1.0,0.0,
			math.sin(t3)/1.0, math.cos(t3)/1.0, 0.0,
			0.0,0.0,1.0)

#    def drawLine(self, x1,y1,x2,y2):
#	xlen = x2-x1
#	ylen = y2-y1
#	xmod = xlen / (ylen + 1)#Float division with 0
#	ymod = ylen / (xlen + 1)
#	yy = y1
#	if x1<x2:
#	    xx = x1
#	    while xx < x2 or yy < y2:
#	        self.screen.blit(self.surf, (xx, yy))
#	        xx += xmod
#	        yy += ymod
#	else:
#	    xx = x2
#	    while xx < x1 or yy < y2:
#	        self.screen.blit(self.surf, (xx, yy))
#	        xx += xmod
#	        yy += ymod
	    

    def transmit(self, v):
	m = self.mx.multiplyByMatrix(self.my)
	m = m.multiplyByMatrix(self.mz)
	retv = m.multiply(v)
	return retv


    ### NOTES :
    ### this function displays according to the present rot matrices
    def display(self, v1, v2):
	m = self.mx.multiplyByMatrix(self.my)
	m = m.multiplyByMatrix(self.mz)
	v1 = m.multiply(v1)
	v2 = m.multiply(v2)
	pygame.draw.line(self.screen, self.color, ## NOTEFIXME 
			(v1.array[0],v1.array[1]),
			(v2.array[0],v2.array[1]))

    def displayPoly(self, pointlist):
	pygame.draw.polygon(self.screen, self.color, pointlist,0)

    def setcolor(self, c):
	self.color = c
