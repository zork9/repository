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

from vector3 import *

class Matrix3():
    def __init__(self, xx1,yy1,zz1,xx2,yy2,zz2,xx3,yy3,zz3):
	self.array = [xx1,yy1,zz1,xx2,yy2,zz2,xx3,yy3,zz3]


    def transpose(self):
	m = Matrix3(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
	array = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
	array[0] = self.array[0]
	array[1] = self.array[3]
	array[2] = self.array[6]
	array[3] = self.array[1]
	array[4] = self.array[4]
	array[5] = self.array[7]
	array[6] = self.array[2]
	array[7] = self.array[5]
	array[8] = self.array[8]
	m.array = array
        return m	

    def multiply(self, v1):
	retv = Vector3(0.0,0.0,0.0)
	for j in [0,1,2]:
	    for i in [0,1,2]:
	        retv.array[i] += self.array[j*3+i] * v1.array[i]
	return retv

    def multiplyByMatrix(self, m1):#FIXME sum
	retm = Matrix3(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
	m = m1.transpose()
	for k in [0,1,2,3,4,5,6,7,8]:
	    for j in [0,1,2]:
	        retm.array[k] += self.array[j] * m.array[j]
	return retm
    
