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

class Vector3 
{

protected float[] array = new float[3];//,color;

public Vector3(float xx, float yy, float zz)//, float cc)
{
	array[0] = xx;
	array[1] = yy;
	array[2] = zz;
	//color = cc;	
}

public Vector3 add(float xx, float yy, float zz)
{
	array[0] += xx;
	array[1] += yy;
	array[2] += zz;

	return this;
}

public Vector3 add(Vector3 v)
{
	float vx = v.x() + array[0];
	float vy = v.y() + array[1];
	float vz = v.z() + array[2];
	return new Vector3(vx,vy,vz);
}
public float x() 
{
	return array[0];
}

public float y() 
{
	return array[1];
}

public float z() 
{
	return array[2];
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

public void normalize()
{
	float magnitude = array[0]*array[0]+array[1]*array[1]+array[2]*array[2];

	if (magnitude == 0)
		return;

	array[0] /= magnitude; 
	array[1] /= magnitude; 
	array[2] /= magnitude; 
}
};
