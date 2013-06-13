package game;
/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import javax.swing.ImageIcon;
import java.awt.Toolkit;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import java.util.*;

class Vector 
{

protected float x,y,z;//,color;

public Vector(float xx, float yy, float zz)//, float cc)
{
	x = xx;
	y = yy;
	z = zz;
	//color = cc;	
}

public void add(float xx, float yy, float zz)
{
	x += xx;
	y += yy;
	z += zz;
}

public Vector add(Vector v)
{
	float vx = v.x() + x;
	float vy = v.y() + y;
	float vz = v.z() + z;
	return new Vector(vx,vy,vz);
}

public float x() 
{
	return x;
}

public float y() 
{
	return y;
}

public float z() 
{
	return z;
}

/******
public float c() 
{
	return color;
}

public float color() 
{
	return color;
}
*********/

};
