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
import pygame, sys,os
from pygame.locals import *
from engine import *
from dsfile import *
from room1 import *
from string import *

class Screen():
    def __init__(self):
        self.window = pygame.display.set_mode((800, 600))
    	self.dsf = DSFile("./example.3ds")

	for i in range(0,8):##FIX 8
    		self.dsf.read()###FIXME FIX multiple reads 1000 should be EOF of .3ds file	
	pygame.font.init()
        self.screen = pygame.display.get_surface()
        self.screenwidth = 800
        self.screenheight = 600
#	self.font = pygame.font.SysFont("Vera", 16)
        self.engine = Engine(self.screen)
        
        self.clock = pygame.time.Clock() 

	self.counter = 1

	self.transx = 1
	self.transy = 1

    def run(self):
        run = 1
        
        while run:
        
#            self.screen.fill(0, None, 0)

            event = pygame.event.poll()#get()
	    if 1:
               if event.type == QUIT or (event.type == KEYDOWN and 
                                         event.key in [K_ESCAPE, K_q]):
                   run = 0
               ###moving
	       key = pygame.key.get_pressed()
	
##	       if key[pygame.K_LEFT] and self.map.offsetx < 0:

	   # self.counter += 1
	    self.transx += 2
	    self.transy += 2
	    self.engine.rotate(self.transx,self.transx,3)
###	    self.v1 = self.engine.display(self.engine.mx,self.engine.my)




#            v1 = Vector3(10.0,10.0,0.0)
#            v2 = Vector3(20.0,10.0,0.0)
#            v3 = Vector3(20.0,20.0,0.0)
#            v4 = Vector3(10.0,20.0,0.0)
#	    v1 = engine.display(v1,v2)
#	    v2 = engine.display(engine.my,engine.mz)
#	    v2 = engine.display(v2,v3)
#	    v3 = engine.display(engine.mz,engine.mz)
#	    v3 = engine.display(v3,v4)
#	    v4 = engine.display(v4,v1)
#	    engine.display(v1,v2)
#	    engine.display(v2,v3)
#	    engine.display(v3,v4)
#	    engine.display(v4,v1)

			
#            cube = Cube(0,0,0)
#	    cube.display(engine)
            room = Room1()
#	    room.rotate(engine,2,2,2)
            room.display(self.engine)
            self.dsf.display(self.engine)
            pygame.display.flip()
           

            self.clock.tick(18)



