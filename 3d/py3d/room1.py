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

# Copyright (C) Johan Ceuppens 2011-2012

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

from vector3 import *
from cube import *

class Room1():
    def __init__(self):

	self.cubes = []
	self.cubes.append(Cube(0,0,0))
	self.cubes.append(Cube(20,20,0))
	self.cubes.append(Cube(100,200,0))

    def rotate(self,engine,rx,ry,rz):
	for cube in self.cubes:
	    cube.rotate(engine,rx,ry,rz)

    def transpose(self):
	1

    def display(self,engine):
	engine.setcolor((0,0,255))
	engine.display(Vector3(0,0,0),Vector3(100,100,0))
	engine.display(Vector3(0,0,100),Vector3(100,100,100))
        ###FIXengine.rotate(.3,1,1)
	v1 = engine.transmit(
	Vector3(0,0,0))
	v2 = engine.transmit(
	Vector3(100,100,0))
	v3 = engine.transmit(
	Vector3(0,0,100))
	v4 = engine.transmit(
	Vector3(100,100,0))
	engine.displayPoly([(v1.array[0],v1.array[1]),(v2.array[0],v2.array[1]),(v3.array[0],v3.array[1]),(v4.array[0],v4.array[1])])

	engine.setcolor((0,0,240))
	for cube in self.cubes:
		cube.display(engine)
	
