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
import javax.imageio.ImageIO;
import java.awt.Toolkit;
import java.awt.color.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import java.awt.image.*;
import java.util.*;
import java.io.*;
import java.nio.*;

class Texturef
{
private String prefix = "./pics/";
private BufferedImage bufferedImage;
private ByteBuffer bb;
private int w,h;
public Texturef(String imagefilename)
{
	try {
		bufferedImage = ImageIO.read(new File(prefix+imagefilename));
	} catch (IOException e) {}


	w = bufferedImage.getWidth();
	h = bufferedImage.getHeight();
	toByteBuffer();

	fade();

	toImage();
}

public BufferedImage getImage()
{
	return bufferedImage;
}

public void toByteBuffer()
{

BufferedImage imgImg;
WritableRaster raster;
	raster =
        Raster.createInterleavedRaster (DataBuffer.TYPE_BYTE,
                                                w,
                                                h,
                                                4,
                                                null);
        ComponentColorModel colorModel=
                                new ComponentColorModel (ColorSpace.getInstance(ColorSpace.CS_sRGB),
                                                new int[] {8,8,8,8},
                                                true,
                                                false,
                                                ComponentColorModel.TRANSLUCENT,
                                                DataBuffer.TYPE_BYTE);
       imgImg =
       new BufferedImage (colorModel,
                          raster,
                          false,
                          null);

       DataBufferByte imgBuf =
       (DataBufferByte)raster.getDataBuffer();
	byte[] imgRGBA = imgBuf.getData();

        bb = ByteBuffer.wrap(imgRGBA);

		
}

public void toImage()
{
	//bufferedImage.read(bb);
}

public void fade()
{
	bb.position(0);
        for (int i = 0; i < w*h*4; i++) {
	        byte b = bb.get(i);
	        if (i%4!=3/* && fadingcounter != 0*/)  {
		        b-=2;
		        if (b < 0)
			        b = 0;
	        }
	        bb.put((byte)b);
        }
        bb.position(0);

}

/*
 * leftxoffset : top left of trapezoid
 * rightxoffset : right top of trapezoid
 * dx : towards left
 * dx2 towards right
 */
public void trapezoidtexturemap(ByteBuffer bb2, int capacity, int ww, int hh, int leftxoffset, int rightxoffset, float dx, float dx2)
{
                        int xoffset = 40;
                        int woffset = 40;
                        for (int j = 0; j < hh; j++) {
                        int pos1 = j*ww;
                        bb2.position(0);
			float l = 0;
                        for (int i = 0; i < ww; i++) {

                                if (i == 0) {
                                        bb2.position(pos1+leftxoffset-leftxoffset/w*j);
					for (int k = 0; k < leftxoffset; k++) {
						bb.put((byte)0);
					}
				}
                                else if (i >= rightxoffset) {
					for (int k = i; k < rightxoffset; k++) {
						bb.put((byte)0);
					}
                                        break;
				}

				leftxoffset -= dx;
				rightxoffset += dx2;
				leftxoffset = leftxoffset<0?0:leftxoffset;	
				rightxoffset = rightxoffset<0?0:rightxoffset;	
				l += i/(ww-leftxoffset-rightxoffset);
                                byte b = bb2.get((int)l+(int)j*ww);
                                bb.put((byte)b);

                        }
                        }
                        bb2.position(0);
}

};
