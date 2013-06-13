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

class Matrix 
{

protected float[] array = new float[9]; 

public Matrix(float xx1, float yy1, float zz1, float xx2, float yy2, float zz2, float xx3, float yy3, float zz3)
{

	array[0] = xx1;	
	array[1] = yy1;	
	array[2] = zz1;	
	array[3] = xx2;	
	array[4] = yy2;	
	array[5] = zz2;	
	array[6] = xx3;	
	array[7] = yy3;	
	array[8] = zz3;	

}

public Matrix mul(Matrix m)
{
	float[] a = m.array();
	float vx1 = a[0]*array[0]+a[1]*array[1]+a[2]*array[2];
	float vy1 = a[0]*array[3]+a[1]*array[4]+a[2]*array[5];
	float vz1 = a[0]*array[6]+a[1]*array[7]+a[2]*array[8];
	float vx2 = a[3]*array[0]+a[4]*array[1]+a[5]*array[2];
	float vy2 = a[3]*array[3]+a[4]*array[4]+a[5]*array[5];
	float vz2 = a[3]*array[6]+a[4]*array[7]+a[5]*array[8];
	float vx3 = a[6]*array[0]+a[7]*array[1]+a[8]*array[2];
	float vy3 = a[6]*array[3]+a[7]*array[4]+a[8]*array[5];
	float vz3 = a[6]*array[6]+a[7]*array[7]+a[8]*array[8];

	return new Matrix(vx1,vy1,vz1,vx2,vy2,vz2,vx3,vy3,vz3);
}

public Vector mul(Vector v)
{
	float vx = v.x()*array[0]+v.y()*array[1]+v.z()*array[2];
	float vy = v.x()*array[3]+v.y()*array[4]+v.z()*array[5];
	float vz = v.x()*array[6]+v.y()*array[7]+v.z()*array[8];

	return new Vector(vx,vy,vz);
}

public Vector3 mul(Vector3 v)
{
	float vx = v.x()*array[0]+v.y()*array[1]+v.z()*array[2];
	float vy = v.x()*array[3]+v.y()*array[4]+v.z()*array[5];
	float vz = v.x()*array[6]+v.y()*array[7]+v.z()*array[8];

	return new Vector3(vx,vy,vz);
}

public Vector3 mul2(Vector3 v)
{
	float vx = v.x()*array[0]+v.y()*array[1]+v.z()*array[2];
	float vy = v.x()*array[3]+v.y()*array[4]+v.z()*array[5];
	float vz = v.x()*array[6]+v.y()*array[7]+v.z()*array[8];

	return new Vector3(vx,vy,vz);
}


public float[] array()
{
	return array;
} 


};
