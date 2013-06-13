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

class Camera 
{

private Vector3 pos;
private Quaternion rotq = new Quaternion(1,0f,0f,0f);
private Matrix rotmatrix = rotq.getRotationMatrix();

public Camera()
{
	pos = new Vector3(0f,0f,0f);
}

public Camera(float ww, float xx, float yy, float zz)
{
	rotq = new Quaternion(ww,xx,yy,zz);
	rotmatrix = rotq.getRotationMatrix();
	pos = new Vector3(0f,0f,0f);

}	

public void movex(float dx)
{
	pos.add(rotmatrix.mul(new Vector3(dx,0f,0f)));
}

public void movey(float dy)
{
	pos.add(0f,-dy,0f);
}

public void movez(float dz)
{
	pos.add(rotmatrix.mul(new Vector3(0f,0f,-dz)));
}

public void rotatex(float dx)
{
	Quaternion nrot = new Quaternion((float)(dx*Math.PI/180),1f,0f,0f);
	rotmatrix = rotmatrix.mul(nrot.getRotationMatrix());

} 

public void rotatey(float dy)
{
	Quaternion nrot = new Quaternion((float)(dy*Math.PI/180),0f,1f,0f);
	rotmatrix = nrot.getRotationMatrix().mul(rotmatrix);
} 


public float x()
{
	return pos.x();
}

public float y()
{
	return pos.y();
}

public float z()
{
	return pos.z();
}

};
