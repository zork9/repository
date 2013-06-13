/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
package game;

import org.lwjgl.LWJGLException;
import org.lwjgl.Sys;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;
import java.util.*;
 
public class Game {
 
	float xx = 0, yy = 0, zz = 0;
	float theta = 0f;
 
	long lastFrame;
 
	int fps;
	long lastFPS;
	
	boolean vsync;

	private int ortholeft = -100;
	private int orthoright = 300;
	private int orthoup = 300;
	private int orthodown = 0;
	private int orthonear = 0;
	private int orthofar = 1;


	private LinkedList terrainpieces = new LinkedList();
 
	public void start() {
		TerrainPieceWalkingTube tg = new TerrainPieceWalkingTube(320,200,4,GL11.GL_LINES);	
		terrainpieces.add(tg);
		TerrainPieceMap1 tg2 = new TerrainPieceMap1(800,600,4,GL11.GL_LINES);	
		terrainpieces.add(tg2);

		try {
			Display.setDisplayMode(new DisplayMode(320, 200));
			Display.create();
		} catch (LWJGLException e) {
			e.printStackTrace();
			System.exit(0);
		}
 
		initGL(); // init OpenGL
		getDelta(); // call once before loop to initialise lastFrame
		lastFPS = getTime(); // call before loop to initialise fps timer
 
		while (!Display.isCloseRequested()) {
			int delta = getDelta();
 
			update(delta);
			renderGL();
 
			Display.update();
			Display.sync(60); // cap fps to 60fps
		}
 
		Display.destroy();
	}
 
	public void update(int delta) {
 
		if (Keyboard.isKeyDown(Keyboard.KEY_LEFT)) {
			xx -= 5f;
		}	
		else if (Keyboard.isKeyDown(Keyboard.KEY_RIGHT)) {
			xx += 5f;
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_UP)) {
			yy -= 5f;
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_DOWN)) {
			yy += 5f;
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_X)) {
			zz += 5f;
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_Z)) {
			zz -= 5f;
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_C)) {
			theta += 1.8f;
			GL11.glMatrixMode(GL11.GL_PROJECTION);
			GL11.glLoadIdentity();
			GL11.glRotatef(theta,0,0,1);
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_V)) {
			//GL11.glOrtho(-100,200,200,0,0,1);
			GL11.glOrtho(ortholeft--,orthoright--,orthoup,orthodown--,orthonear,orthofar);
		}
		else if (Keyboard.isKeyDown(Keyboard.KEY_B)) {
			//GL11.glOrtho(-100,200,200,0,0,1);
			GL11.glOrtho(ortholeft++,orthoright++,orthoup++,orthodown,orthonear,orthofar);
		}
		while (Keyboard.next()) {
		    if (Keyboard.getEventKeyState()) {
		        if (Keyboard.getEventKey() == Keyboard.KEY_F) {
		        	setDisplayMode(800, 600, !Display.isFullscreen());
		        }
		        else if (Keyboard.getEventKey() == Keyboard.KEY_V) {
		        	vsync = !vsync;
		        	Display.setVSyncEnabled(vsync);
		        }
		    }
		}
		
		updateFPS(); // update FPS Counter
	}
 
	public void setDisplayMode(int width, int height, boolean fullscreen) {

		// return if requested DisplayMode is already set
                if ((Display.getDisplayMode().getWidth() == width) && 
			(Display.getDisplayMode().getHeight() == height) && 
			(Display.isFullscreen() == fullscreen)) {
			return;
		}
		
		try {
			DisplayMode targetDisplayMode = null;
			
			if (fullscreen) {
				DisplayMode[] modes = Display.getAvailableDisplayModes();
				int freq = 0;
				
				for (int i=0;i<modes.length;i++) {
					DisplayMode current = modes[i];
					
					if ((current.getWidth() == width) && (current.getHeight() == height)) {
						if ((targetDisplayMode == null) || (current.getFrequency() >= freq)) {
							if ((targetDisplayMode == null) || (current.getBitsPerPixel() > targetDisplayMode.getBitsPerPixel())) {
								targetDisplayMode = current;
								freq = targetDisplayMode.getFrequency();
							}
						}

						// if we've found a match for bpp and frequence against the 
						// original display mode then it's probably best to go for this one
						// since it's most likely compatible with the monitor
						if ((current.getBitsPerPixel() == Display.getDesktopDisplayMode().getBitsPerPixel()) &&
						    (current.getFrequency() == Display.getDesktopDisplayMode().getFrequency())) {
							targetDisplayMode = current;
							break;
						}
					}
				}
			} else {
				targetDisplayMode = new DisplayMode(width,height);
			}
			
			if (targetDisplayMode == null) {
				System.out.println("Failed to find value mode: "+width+"x"+height+" fs="+fullscreen);
				return;
			}

			Display.setDisplayMode(targetDisplayMode);
			Display.setFullscreen(fullscreen);
			
		} catch (LWJGLException e) {
			System.out.println("Unable to setup mode "+width+"x"+height+" fullscreen="+fullscreen + e);
		}
	}
	
	public int getDelta() {
	    long time = getTime();
	    int delta = (int) (time - lastFrame);
	    lastFrame = time;
 
	    return delta;
	}
 
	public long getTime() {
	    return (Sys.getTime() * 1000) / Sys.getTimerResolution();
	}
 
	public void updateFPS() {
		if (getTime() - lastFPS > 1000) {
			Display.setTitle("FPS: " + fps);
			fps = 0;
			lastFPS += 1000;
		}
		fps++;
	}
 
	public void initGL() {
		GL11.glMatrixMode(GL11.GL_PROJECTION);
		GL11.glLoadIdentity();
		GL11.glOrtho(ortholeft,orthoright,orthoup,orthodown,orthonear,orthofar);
		//GL11.glOrtho(-100, 300, 300, 0, 0, 1);
		//GL11.glOrtho(-160, 160, 0, 200, 0, 1);
	}
 
	public void renderGL() {
		// Clear The Screen And The Depth Buffer
		GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);
 
		// R,G,B,A Set The Color To Blue One Time Only
		GL11.glColor3f(0.5f, 0.5f, 1.0f);
 
	 for (int j = 0; j < terrainpieces.size(); j++) {
                Object o = terrainpieces.get(j);
                TerrainPieceBase tp = (TerrainPieceBase)o;
 		for (int i = 0; i < tp.size()-4; i+=tp.padsize()) {//NOTE! -4 for outofbounds
                if (tp.padsize() == 4) {

                        float xx1 = tp.getvertexx(i);
                        float yy1 = tp.getvertexy(i);
                        float zz1 = tp.getvertexz(i);
                        float xx2 = tp.getvertexx(i+1);
                        float yy2 = tp.getvertexy(i+1);
                        float zz2 = tp.getvertexz(i+1);
                        float xx3 = tp.getvertexx(i+2);
                        float yy3 = tp.getvertexy(i+2);
                        float zz3 = tp.getvertexz(i+2);
                        float xx4 = tp.getvertexx(i+3);
                        float yy4 = tp.getvertexy(i+3);
                        float zz4 = tp.getvertexz(i+3);
                        float cc1 = tp.getvertexc(i);
                        float cc2 = tp.getvertexc(i+1);
                        float cc3 = tp.getvertexc(i+2);
                        float cc4 = tp.getvertexc(i+3);

                        //draw a polygon from the map vertices
                        GL11.glBegin(tp.getGLdraw());
                        GL11.glColor3f((int)cc1<<24,(int)cc1<<16,(int)cc1<<8);
                        //GL11.glColor4f(1,1,0,1);//gradients
                        GL11.glVertex3f(xx+xx1,yy+yy1,zz+zz1);
                        //gl.glColor4f(1,0,1,1);
                        GL11.glColor3f((int)cc2<<24,(int)cc2<<16,(int)cc2<<8);
                        GL11.glVertex3f(xx+xx2,yy+yy2,zz+zz2);
                        //GL11.glColor4f(1,1,1,1);
                        GL11.glColor3f((int)cc3<<24,(int)cc3<<16,(int)cc3<<8);
                        GL11.glVertex3f(xx+xx3,yy+yy3,zz+zz3);
                        //GL11.glColor4f(0,1,0,0);
                        GL11.glColor3f((int)cc4<<24,(int)cc4<<16,(int)cc4<<8);
                        GL11.glVertex3f(xx+xx4,yy+yy4,zz+zz4);

                        GL11.glEnd();
		}      
                else if (tp.padsize() == 2) {
                        float xx1 = tp.getvertexx(i);
                        float yy1 = tp.getvertexy(i);
                        float zz1 = tp.getvertexz(i);
                        float xx2 = tp.getvertexx(i+1);
                        float yy2 = tp.getvertexy(i+1);
                        float zz2 = tp.getvertexz(i+1);
                        float cc1 = tp.getvertexc(i);
                        float cc2 = tp.getvertexc(i+1);
			//System.out.println("x=" + xx1 + " y=" + yy1);
                        GL11.glBegin(tp.getGLdraw());
                        //GL11.glColor4f(1,1,0,1);
                        GL11.glColor3f((int)cc1<<24,(int)cc1<<16,(int)cc1<<8);
                        GL11.glVertex3f(xx+xx1,yy+yy1,zz+zz1);
                        //GL11.glColor4f(1,0,1,1);
                        GL11.glColor3f((int)cc1<<24,(int)cc1<<16,(int)cc1<<8);
                        GL11.glVertex3f(xx+xx2,yy+yy2,zz+zz2);
                        GL11.glEnd();
        	}
	}
	}
}
 
	public static void main(String[] argv) {
		Game game = new Game();

		game.start();
	}
}

