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

class Cube():
    def __init__(self, tx,ty,tz):

	self.tx = tx
	self.ty = ty
	self.tz = tz

   	### backside square
	self.v11 = Vector3(10.0+self.tx,10.0+self.ty,0.0+self.tz)
        self.v12 = Vector3(20.0+self.tx,10.0+self.ty,0.0+self.tz)
        self.v13 = Vector3(20.0+self.tx,20.0+self.ty,0.0+self.tz)
        self.v14 = Vector3(10.0+self.tx,20.0+self.ty,0.0+self.tz)
	### front side square
        self.v21 = Vector3(10.0+10.0+self.tx,10.0+5.0+self.ty,5.0+self.tz) ## NOTE z
        self.v22 = Vector3(20.0+10.0+self.tx,10.0+5.0+self.ty,5.0+self.tz)
        self.v23 = Vector3(20.0+10.0+self.tx,20.0+5.0+self.ty,5.0+self.tz)
        self.v24 = Vector3(10.0+10.0+self.tx,20.0+5.0+self.ty,5.0+self.tz)
	### connections
        self.vconn1 = Vector3(10.0+self.tx,10.0+self.ty,0.0+self.tz)
        self.vconn2 = Vector3(10.0+10.0+self.tx,10.0+5.0+self.ty,5.0+self.tz)

        self.vconn3 = Vector3(20.0+self.tx,10.0+self.ty,0.0+self.tz)
        self.vconn4 = Vector3(20.0+10.0+self.tx,10.0+5.0+self.ty,5.0+self.tz)
   
	self.vconn5 = Vector3(20.0+self.tx,20.0+self.ty,0.0+self.tz)
	self.vconn6 = Vector3(20.0+10.0+self.tx,20.0+5.0+self.ty,5.0+self.tz)

	self.vconn7 = Vector3(10.0+self.tx,20.0+self.ty,0.0+self.tz)
	self.vconn8 = Vector3(10.0+10.0+self.tx,20.0+5.0+self.ty,5.0+self.tz)

    def transpose(self):
	1

    def rotate(self,engine,rx,ry,rz):
	### FIXME : reset engine's matrices mx etc. are held
	engine.rotate(rx,ry,rz)
    	self.v11 = engine.transmit(self.engine.mx,self.engine.my)

    	self.v12 = engine.transmit(self.engine.mx,self.engine.my)
    	self.v13 = engine.transmit(self.engine.mx,self.engine.my)
    	self.v14 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn1 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn2 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn3 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn4 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn5 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn6 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn7 = engine.transmit(self.engine.mx,self.engine.my)
    	self.vconn8 = engine.transmit(self.engine.mx,self.engine.my)



    def display(self, engine):
    	engine.display(self.v11,self.v12)
    	engine.display(self.v12,self.v13)
    	engine.display(self.v13,self.v14)
    	engine.display(self.v14,self.v11)

	engine.display(self.v21,self.v22)
    	engine.display(self.v22,self.v23)
    	engine.display(self.v23,self.v24)
    	engine.display(self.v24,self.v21)

	engine.display(self.vconn1,self.vconn2)
	engine.display(self.vconn3,self.vconn4)
	engine.display(self.vconn5,self.vconn6)
	engine.display(self.vconn7,self.vconn8)
