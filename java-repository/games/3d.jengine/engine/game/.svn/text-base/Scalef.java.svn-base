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

class Scalef
{
private Matrix mattrans = null; 

public Scalef(float xx, float yy, float zz)
{
	mattrans = new Matrix(xx,0f,0f,
				0f,yy,0f,
				0f,0f,zz);
}

public Vector3 f(float xx, float yy, float zz, Vector3 v)
{
	mattrans = new Matrix(xx,0f,0f,
				0f,yy,0f,
				0f,0f,zz);
	return mattrans.mul2(v);
}

public Vector3 f(Vector3 v)
{
	return mattrans.mul2(v);
}

public Vector f(float xx, float yy, float zz, Vector v)
{
	mattrans = new Matrix(xx,0f,0f,
				0f,yy,0f,
				0f,0f,zz);
	return mattrans.mul(v);
}

public Vector f(Vector v)
{
	return mattrans.mul(v);
}




};
