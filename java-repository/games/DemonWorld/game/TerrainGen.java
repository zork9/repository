package game;
/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
import java.awt.*;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.color.ColorSpace;
import java.awt.image.BufferedImage;
import java.awt.image.ComponentColorModel;
import java.awt.image.DataBuffer;
import java.awt.image.DataBufferByte;
import java.awt.image.Raster;
import java.awt.image.WritableRaster;
import java.io.IOException;
import java.nio.ByteBuffer;
import javax.imageio.ImageIO;
import java.awt.Frame;
import java.awt.event.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.*;
import java.io.*;
import java.util.*;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/*
 * class TerrainGen :
 * generates maps of polygons and contains
 * drawing primitives for map building
 * This is the base class of a TerrainPieceBase
 */

public class TerrainGen {
private LinkedList vertices = new LinkedList();
private int index = 0;
private int width = 320;
private int height = 200;
private int padsize = 4;
//bb is the work buffer for image files and texturemapping
private ByteBuffer bb;
private String prefix = "./pics/";
private boolean bigendian = true;

/*
 * embedded classes
 */
	protected class Vertex
	{
		protected float x,y,z,c;
		public Vertex(float xx, float yy, float zz)
		{
			x = xx;
			y = yy;
			z = zz;
			c = 200;
		}

		public Vertex(float xx, float yy, float zz, float cc)
		{
			x = xx;
			y = yy;
			z = zz;
			c = cc;
		}

		public float getc()
		{
			return c;
		}
		public float getx()
		{
			return x;
		}
	
		public float gety()
		{
			return y;
		}
	
		public float getz()
		{
			return z;
		}
	
	};

/*
 * Constructors
 */	
	public TerrainGen(int ww, int hh, int pad, boolean bige)
	{
		width = ww;
		height = hh;
		//read pad vertices at oncefor storing a polygon
		padsize = pad;
		bigendian = bige;

	}

/*
 * math functionality
 */

    public float normal(float xx1, float yy1, float zz1, float xx2, float yy2, float zz2)
    {

	return (float)Math.sqrt((float)xx1*xx2 + (float)yy1*yy2 + (float)zz1*zz2);

    }

/* 
 * ByteBuffer functionality
 */

	
	public void gfxfiletobytebuffer(String gfxfilename)
	{ 
		BufferedImage bufferedImage = null;
		int w=0,h=0;
		try {
			bufferedImage = ImageIO.read(new File(prefix+gfxfilename));
			w = bufferedImage.getWidth();
			h = bufferedImage.getHeight();
		} catch (IOException e) {}

		WritableRaster raster =
                                Raster.createInterleavedRaster (DataBuffer.TYPE_BYTE,
                                                w,
                                                h,
                                                4,
                                                null);
                ComponentColorModel colorModel =
                                new ComponentColorModel (ColorSpace.getInstance(ColorSpace.CS_sRGB),
                                                new int[] {8,8,8,8},
                                                true,
                                                false,
                                                ComponentColorModel.TRANSLUCENT,
                                                DataBuffer.TYPE_BYTE);
                 BufferedImage imgImg =
                                new BufferedImage (colorModel,
                                                raster,
                                                false,
                                                null);

                 DataBufferByte imgBuf =
                                (DataBufferByte)raster.getDataBuffer();
		 byte[] imgRGBA = imgBuf.getData();

                 bb = ByteBuffer.wrap(imgRGBA);
	}

/*
 * gfx file e.g. jpg or png functionality
 */

	public void gfxfiletovertices(float xx, float yy, float zz, float ww, float hh, String gfxfilename)
	{
		gfxfiletobytebuffer(gfxfilename);	
		bb.position(0);
		for (int j = 0; j < 100; j++) {
			for (int i = 0; i < 63; i+=4) {
				byte b = bb.get(j*100+i);
				byte b2 = bb.get(j*100+i+1);
				byte b3 = bb.get(j*100+i+2);
				byte b4 = bb.get(j*100+i+3);
				if (bigendian)
					vertices.add(new Vertex(xx+i,yy+j,zz,b*8*8*8+b2*8*8+b3*8+b4));
				else
					vertices.add(new Vertex(xx+i,yy+j,zz,b+b2*8+b3*8*8+b4*8*8*8));
				
			}
		}
		
	}
/*
 * drawing primitives e.g. squares, polygons
 */

	public void generatecircle(float r)
	{
		padsize = 3;

		float increment = (float)(2*Math.PI/48);//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;
	
		for (float angle = 0; angle < 2*Math.PI; angle+=increment) {
			vertices.add(new Vertex(cx,cy,0.0f));
			vertices.add(new Vertex((float)(cx+Math.cos(angle)*radius),(float)(cy+Math.sin(angle)*radius),0.0f));
			vertices.add(new Vertex((float)(cx+Math.cos(angle + increment)*radius),(float)(cy+Math.sin(angle + increment)*radius),0.0f));
		}
	}

	public void generatetwothirdcylinder(float r, float length)
	{
		padsize = 2;

		float increment = (float)(2*Math.PI/48);//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;

		for (float zz = -length/2; zz < length/2; zz+=0.2f) {
			generatetwothirdcircle(r,zz);
			//generate lines	
			vertices.add(new Vertex((float)(cx-Math.cos(-Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));
			vertices.add(new Vertex((float)(cx+Math.cos(Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));

		}	
		for (float zz = -length/2; zz < length/2; zz+=0.2f) {
			//aenerate left circle connections	
			vertices.add(new Vertex((float)(cx-Math.cos(-Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));
			zz+=0.2f;
			vertices.add(new Vertex((float)(cx-Math.cos(-Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));
				
		}
		for (float zz = -length/2; zz < length/2; zz+=0.2f) {
			//generate right circle connections	
			vertices.add(new Vertex((float)(cx+Math.cos(Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));
			zz+=0.2f;
			vertices.add(new Vertex((float)(cx+Math.cos(Math.PI/4)*radius),(float)(cy+Math.cos(Math.PI+Math.PI/4)*radius),zz));
				
		}
	}

	public void generatehalfcylinder(float r, float length)
	{
		padsize = 2;

		float increment = (float)(2*Math.PI/48);//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;

		for (float zz = -length/2; zz < length/2; zz+=0.2f) {
			generatehalfcircle(r,zz);
			//generate lines	
			vertices.add(new Vertex(cx-radius,cy,zz));
			vertices.add(new Vertex(cx+radius,cy,zz));
		}	
	}

	public void generatehalfcircletest(float r, float zz)
	{
		padsize = 3;

		float increment = (float)(2*Math.PI/48);//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;
	
		for (float angle = 0; angle < Math.PI; angle+=increment) {
			vertices.add(new Vertex(cx,cy,0.0f));
			vertices.add(new Vertex((float)(cx+Math.cos(angle)*radius),(float)(cy+Math.sin(angle)*radius),zz));
			vertices.add(new Vertex((float)(cx+Math.cos(angle + increment)*radius),(float)(cy+Math.sin(angle + increment)*radius),zz));
		}
	}
 
	public void generatetwothirdcircle(float r, float zz)
	{
		padsize = 2;

		float increment = (float)(2*Math.PI/(48*3));//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;
		float angle = 0;
	
		for (angle = (float)(-Math.PI/4); angle < Math.PI+Math.PI/4; angle+=increment) {
			vertices.add(new Vertex((float)(Math.cos(angle)*radius),(float)(Math.sin(angle)*radius),zz));
			vertices.add(new Vertex((float)(Math.cos(angle + increment)*radius),(float)(Math.sin(angle + increment)*radius),zz));
		}
	}
	public void generatehalfcircle(float r, float zz)
	{
		padsize = 2;

		float increment = (float)(2*Math.PI/(48*3));//in 48 pieces	
		float cx = 0.0f;
		float cy = 0.0f;
		float radius = r;
		float angle = 0;
	
		for (angle = 0; angle < Math.PI; angle+=increment) {
			vertices.add(new Vertex((float)(Math.cos(angle)*radius),(float)(Math.sin(angle)*radius),zz));
			vertices.add(new Vertex((float)(Math.cos(angle + increment)*radius),(float)(Math.sin(angle + increment)*radius),zz));
		}
	}
 
	public void generatecylindertest(float r)
	{
		padsize = 3;
		float radius = r;
		float increment = (float)(2*Math.PI/(32*3));//in 48 pieces	
		for (float angle = 0; angle < Math.PI; angle+=increment) {
			vertices.add(new Vertex((float)(Math.cos(angle)*radius),(float)(Math.sin(angle)*radius),0.0f));
			System.out.println("x="+Math.cos(angle)*radius+" y="+Math.sin(angle)*radius);
			angle += increment;
			vertices.add(new Vertex((float)(Math.cos(angle)*radius),(float)(Math.sin(angle)*radius),0.0f));
			System.out.println("x="+Math.cos(angle)*radius+" y="+Math.sin(angle)*radius);
			angle += increment;
			vertices.add(new Vertex((float)(Math.cos(angle)*radius),(float)(Math.sin(angle)*radius),0.0f));
			System.out.println("x="+Math.cos(angle)*radius+" y="+Math.sin(angle)*radius);
		

	}
				


	}


	public void trapezoidtexturemap(ByteBuffer bb2, int capacity, int ww, int hh, int leftxoffset, int rightxoffset)
	{
			int xoffset = 40;	
			int woffset = 40;	
			for (int j = 0; j < hh; j++) {
			int pos1 = j*hh;
                        bb2.position(0);
			for (int i = 0; i < ww; i++) {
				
				byte b = bb2.get(i*(int)(ww/hh)+j*ww);
				if (i == 0)
					bb2.position(pos1+leftxoffset-leftxoffset/width*j);
				else if (i >= rightxoffset)
					continue;

				bb2.put((byte)b);

			}
			}
                        bb2.position(0);
	}

	public void generatedowntiltedsquare(float xx, float yy, float ww, float hh, float d1)
	{
		padsize = 4;
		float zz = 0;
		vertices.add(new Vertex((float)xx,(float)yy,zz+d1));
		vertices.add(new Vertex((float)xx+ww,(float)yy,zz));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,zz));
		vertices.add(new Vertex((float)xx,(float)yy+hh,zz));
	}

	public void generateuptiltedsquare(float xx, float yy, float ww, float hh, float d1)
	{
		padsize = 4;
		float zz = 0;
		vertices.add(new Vertex((float)xx,(float)yy,zz-d1));
		vertices.add(new Vertex((float)xx+ww,(float)yy,zz));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,zz));
		vertices.add(new Vertex((float)xx,(float)yy+hh,zz));
	}

	public void generatetiltedsquaretest1(float xx, float yy, float ww, float hh, float d1, float d2, float d3, float d4)
	{
		padsize = 4;
		float dx1 = 0;
		float dx2 = 0;
		float dx3 = 0;
		float dx4 = 0;
		float dz1 = 0;
		float dz2 = 0;
		float dz3 = 0;
		float dz4 = 0;
		vertices.add(new Vertex((float)xx,(float)yy+hh+d1,dz1));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,dz1));
		vertices.add(new Vertex((float)xx+ww,(float)yy,dz1));
		vertices.add(new Vertex((float)xx,(float)yy+hh,dz1));
	}

	public void generatesquare(float xx, float yy, float ww, float hh)
	{
		padsize = 4;

		vertices.add(new Vertex((float)xx,(float)yy,0.0f));
		vertices.add(new Vertex((float)xx+ww,(float)yy,0.0f));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,0.0f));
		vertices.add(new Vertex((float)xx,(float)yy+hh,0.0f));
		
	}

	public void generaterectangle(float xx, float yy, float ww, float hh)
	{
		padsize = 4;

		vertices.add(new Vertex((float)xx,(float)yy,0.0f));
		vertices.add(new Vertex((float)xx+ww,(float)yy,0.0f));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,0.0f));
		vertices.add(new Vertex((float)xx,(float)yy+hh,0.0f));
		
	}

	public void generaterectangularpillar(float xx, float yy, float zz, float ww, float hh)
	{
		padsize = 4;
	//	generaterectangle(xx,yy,ww,hh);
		vertices.add(new Vertex((float)xx,(float)yy,ww));
		vertices.add(new Vertex((float)xx+ww,(float)yy,ww));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh,ww));
		vertices.add(new Vertex((float)xx,(float)yy+hh,ww));
	
		vertices.add(new Vertex((float)xx,(float)yy+ww,ww));
		vertices.add(new Vertex((float)xx+ww,(float)yy+ww,ww));
		vertices.add(new Vertex((float)xx+ww,(float)yy+hh+ww,ww));
		vertices.add(new Vertex((float)xx,(float)yy+hh+ww,ww));

		//put pixels in vertices array
		gfxfiletovertices(xx,yy,zz,ww,hh,"pillar-63x100-1.png");


	}



	/*
	 * Function : generatetiltedsquarestop :
	 * generate a square with 4 adjacent squares lower with 
	 * lower outer corners. 
	 * the 4 outer outer corners are length down d1, etc. 
	 */
	public void generatetiltedsquarestop(int xx, int yy, int ww, int hh, int dz1, int dz2, int dz3, int dz4)
	{
		generatedowntiltedsquare(-xx,-yy,ww,hh,dz1);
		generatedowntiltedsquare(0,-xx,-ww,hh,dz2);//NOTE negative width;
		generatedowntiltedsquare(-xx,0,ww,hh,dz3);
		generatedowntiltedsquare(0,0,-ww,hh,dz4);
	}


	public void generatemap1()
	{
	
		for (int i = -10; i < 10; i+=10) {
		int j;
		for (j = -16; j < 16; j+=10) {
				generatedowntiltedsquare(i,-j,1,1,3);//FIXME better width and height 
				generatedowntiltedsquare(0,-j,-1,1,3);//NOTE negative width;
				generatedowntiltedsquare(-i,0,1,1,3);
				generatedowntiltedsquare(0,0,-1,1,3);
			}
			j = -100;	
		}
	}

	public void generatemap2()
	{
	
		for (int i = 0; i < 10; i++) {
			generatetiltedsquarestop(i,0,1,1,3*i,3*i,3*i,3*i);//FIXME better width and height 
			//generatedowntiltedsquare(0,-j,-1,1,3);//NOTE negative width;
			//generatedowntiltedsquare(-i,0,1,1,3);
			//generatedowntiltedsquare(0,0,-1,1,3);
		}
	}


	public float getvertexc(int index)
	{
		Object o = vertices.get(index);
		Vertex v = (Vertex)o;
		float cc = v.getc();
		return cc;
	} 
	public float getvertexx(int index)
	{
		Object o = vertices.get(index);
		Vertex v = (Vertex)o;
		float xx = v.getx();
		return xx;
	} 
	public float getvertexy(int index)
	{
		Object o = vertices.get(index);
		Vertex v = (Vertex)o;
		float yy = v.gety();
		return yy;
	} 
	public float getvertexz(int index)
	{
		Object o = vertices.get(index);
		Vertex v = (Vertex)o;
		float zz = v.getz();
		return zz;
	} 

	public int size()
	{
		return vertices.size();
	}

	public int padsize()
	{
		return padsize;
	}
};
