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

class Sphere extends ModelNative 
{
private float radius = 0f;
private float x = 0f,y = 0f, z = 0f;

public Sphere(float r, int pieces)
{
	radius = r;
	generatesphere(r,pieces);
}

public void generatesphere(float radius, int pieces)
{
                int meridians = 4*pieces;
                int parallels = 4*pieces;

                for (float theta = 0; theta < Math.PI; theta += Math.PI/meridians) {
                        for (float phi = 0; phi < 2*Math.PI; phi += 2*Math.PI/parallels) {

                                addVertex((float)(x+Math.cos(theta)*Math.sin(phi)*radius),
                                          (float)(y+Math.sin(theta)*Math.sin(phi)*radius),
                                          (float)(z+Math.cos(phi)*radius));
                        }      
                }
}

};
