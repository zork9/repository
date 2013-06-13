package game;
/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
import java.util.*;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class TerrainPieceWalkingTube extends TerrainPieceBase {

	public TerrainPieceWalkingTube(int ww, int hh, int padsz,int GLdraw) {
		super(ww,hh,padsz,GLdraw,true);	
		//generatehalfcircle(10.0f,10);	
		generatetwothirdcylinder(10.0f,10);	
	}
};
