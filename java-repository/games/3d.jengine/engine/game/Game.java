package game;
/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
import java.awt.*;
import javax.swing.*;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.GraphicsEnvironment;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.imageio.ImageIO;

import java.util.*;
import java.util.Random;
import java.awt.image.*;
import java.awt.image.BufferedImage;

public class Game extends JPanel implements ActionListener {
private String fileprefix = "./pics/";
private String musicfileprefix = "./music/";
private int SCREENWIDTH = 320;
private int SCREENHEIGHT = 200;
//private Texturef tex = new Texturef("door-48x48-1.png");
private Sphere sphere = new Sphere(100.0f,20);
private Translatef translatef = new Translatef(0,0,0);
private Camera cam = new Camera();

public Game() {
	
	Timer timer;

        addKeyListener(new TAdapter());
        setFocusable(true);
	
        setBackground(Color.white);
        setDoubleBuffered(true);

        timer = new Timer(40, this);
        timer.start();

	loadlevel1();

    }

    public void addNotify() {
        super.addNotify();
        GameInit();
    }

    public void loadlevel1()
    {
    }

    public void loadlevel2()
    {
    }

    public void GameInit() {
        LevelInit();
    }


    public void LevelInit() {

    }

/*
 * Collision detection code
 */
/****
   public boolean DoGatewayCollision()
    {
	for (int i = 0; i < gateways.size(); i++) {
		Object o = gateways.get(i);
		Gateway bo = (Gateway)o;
		if (collision(player.getx()-map.getx(),player.gety()-map.gety(),player.getw(),player.geth(),bo.getx(),bo.gety(),bo.getw(),bo.geth())) {

			currentgateway = bo;

			return true;
		}
	}
	return false;
    }	
*****/

/*
 * Drawing
 */ 
/*****    public void DrawGateways(Graphics2D g2d)
    {
	for (int i = 0; i < gateways.size(); i++) {
		Object o = gateways.get(i);
		Gateway bo = (Gateway)o;
		g2d.drawImage(bo.getImage(), bo.getx()+map.getx(), bo.gety()+map.gety(), this);
	}
    }	
*****/
	
    public void paint(Graphics g)
    {
      Graphics2D g2d = (Graphics2D) g;
	g2d.setColor(Color.black);
      g2d.fillRect(0, 0, 320, 200);
      g2d.setColor(Color.red);

	for (int i = 0; i < sphere.size(); i++) {

		Vector3 v = sphere.getVertex(i);
		//v = new Quaternion(2f,2f,2f,2f).rotateVector(v);	

		cam.movey(2f);
		//cam.rotatex(0.2f);
		v = new Vector3(cam.x(),cam.y(),cam.z());
      		g2d.fillRect((int)v.x()+(int)sphere.x(),(int)v.y()+(int)sphere.y(),1,1);
			

	} 

      //g2d.drawImage(tex.getImage(),null,null);
      Toolkit.getDefaultToolkit().sync();
      g.dispose();

    }

    class TAdapter extends KeyAdapter {
        public void keyReleased(KeyEvent e) {
	} 
      
        public void keyPressed(KeyEvent e) {

          int key = e.getKeyCode();

	   	if (key == KeyEvent.VK_LEFT) {
			sphere.setx(sphere.x()-1f);
			repaint();	
		}
	   	if (key == KeyEvent.VK_RIGHT) {
			sphere.setx(sphere.x()+1f);
			repaint();	
	   	}
	   	if (key == KeyEvent.VK_UP) {
			sphere.sety(sphere.y()-1f);
			repaint();	
	   	}
	   	if (key == KeyEvent.VK_DOWN) {
			sphere.sety(sphere.y()+1f);
			repaint();	
		}	
	   	if (key == KeyEvent.VK_X) {
	   	}
	   	if (key == KeyEvent.VK_Z) {//go back to history of talkmodes
	   	}
		if (key == KeyEvent.VK_ESCAPE) {
	   		System.exit(99);
		}
	}
    }

    public void actionPerformed(ActionEvent e) {
        repaint();  
    }

}
