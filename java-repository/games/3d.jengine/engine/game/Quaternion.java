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

/*
 * representation : w+ix+jy+kz
 */
class Quaternion 
{

protected float[] array = new float[4];

public Quaternion(float ww, float xx, float yy, float zz)
{
	array[0] = ww;
	array[1] = xx;
	array[2] = yy;
	array[3] = zz;
}

public Quaternion conjugate()
{
	return new Quaternion(array[0],-array[1],-array[2],-array[3]);
}

public Quaternion add(float ww, float xx, float yy, float zz)
{
	array[0] += ww;
	array[1] += xx;
	array[2] += yy;
	array[3] += zz;

	return this;
}

//this q multiplied by q2
public Quaternion mul(Quaternion q2)
{

	return new Quaternion(array[0]*q2.w()-array[1]*q2.x()-array[2]*q2.y()-array[3]*q2.z(),
			array[0]*q2.x()+array[1]*q2.w()+array[2]*q2.z()-array[3]*q2.y(),
			array[0]*q2.y()-array[1]*q2.z()+array[2]*q2.w()+array[3]*q2.x(),
			array[0]*q2.z()+array[1]*q2.y()-array[2]*q2.x()+array[3]*q2.w());


}

public Vector3 rotateVector(Vector3 v)
{
	Vector3 vn = new Vector3(v.x(),v.y(),v.z());
	vn.normalize();


	Quaternion vq = new Quaternion(0f,vn.x(),vn.y(),vn.z());
	Quaternion rq = vq.mul(conjugate());
	rq = mul(rq);

	return new Vector3(rq.x(),rq.y(),rq.z());	
}

public Quaternion rotate(float angle, float xaxisx, float yaxisy, float zaxisz)
{
	float s = (float)Math.sin(angle/2);
	return new Quaternion((float)Math.cos(angle/2),xaxisx*s,
						yaxisy*s,
						zaxisz*s);	

}

public Matrix getRotationMatrix()
{
//NOTE norm is x*x+y*y+z*z+w*w 
	return new Matrix(array[0]*array[0]+array[1]*array[1]-array[2]*array[2]-array[3]*array[3],
			2*array[1]*array[2]-2*array[0]*array[3],
			2*array[1]*array[3]-2*array[0]*array[2],
			2*array[1]*array[2]+2*array[0]*array[3],
			array[0]*array[0]-array[1]*array[1]+array[2]*array[2]-array[3]*array[3],
			2*array[1]*array[3]+2*array[0]*array[1],
			2*array[1]*array[3]-2*array[0]*array[2],
			2*array[1]*array[3]-2*array[0]*array[1],
			array[0]*array[0]-array[1]*array[1]-array[2]*array[2]+array[3]*array[3]);

}

//You can normalize a q to a unti q but the product will then be again a unit q
public void normalize()
{
	float magnitude = array[0]*array[0]+array[1]*array[1]+array[2]*array[2]+array[3]*array[3];

	if (magnitude == 0)
		return;

	array[0] /= magnitude; 
	array[1] /= magnitude; 
	array[2] /= magnitude; 
	array[3] /= magnitude; 
}


public float w() 
{
	return array[0];
}

public float x() 
{
	return array[1];
}

public float y() 
{
	return array[2];
}

public float z() 
{
	return array[3];
}

};
