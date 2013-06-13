### 3d.engine - 3DS Max file reader
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
from string import *
from vector3 import *

class DSFile:
    def __init__(self, dsfilename):
	self.vertices = []
	self.infile = open(dsfilename, 'r')
	self.infile.seek(0)
	self.prevend = 0

    def read(self):
	id = 0
	id = self.infile.read(2)
	id = ord(id[0]) + ord(id[1])
	end = self.infile.read(4)
	end = ord(end[0])*1 + ord(end[1])*10 + ord(end[2])*100 + ord(end[3])*1000
	print "id=%d" % id

	filelen =  self.infile.read(16/8) ### short
	filelen = ord(filelen[0])*1 + ord(filelen[1])*10
	print "filelen=%d end=%d" %  (filelen,end)
	for i in range(0, end):###FIX filelen/4):
		str = self.infile.read(64/8) ### NOTE: float is 64 bits long here
		bin = ord(str[0])*1+ord(str[1])*10+ord(str[2])*100+ord(str[3])*1000+ord(str[4])*10000+ord(str[5])*100000+ord(str[6])*1000000+ord(str[7])*10000000
		#print "ord=%f" % bin
		if (id == 411): ## FIXME FIX only vertices
			self.vertices.append(bin/3) ### NOTE FIX FIXME bin/3

    def display(self,engine):
            engine.setcolor((0,0,255))
	    l = len(self.vertices)
	    if l % 6 > 0:
	        l = l - len(self.vertices) % 6
	    else:
		l = l
		
	    j = 0
	    for i in range(0,l/6):
		v1 = Vector3(self.vertices[j],self.vertices[j+1],self.vertices[j+2])
	    	v2 = Vector3(self.vertices[j+3],self.vertices[j+4],self.vertices[j+5])
		pygame.draw.line(engine.screen, (255,0,0), ## NOTEFIXME 
			(v1.array[0],v1.array[1]),
			(v2.array[0],v2.array[1]))

	    	j += 6

