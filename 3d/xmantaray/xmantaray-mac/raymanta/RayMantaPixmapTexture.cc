/*
 Copyright (C) Johan Ceuppens 2011

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include<fstream>
#include "RayMantaPixmapTextureModel.h"
#include "RayMantaMatrix3.h"
#include<cstdlib>

namespace ray3d {

/*
* NOTE : You map the _xpmimage 
* (xpm XImage, see file RayMantaPixmapImage.h/.cc)
* onto the walls, curved,dungeon tower and straight walls.
*/	
//main draw method

int PixmapTexture::initdraw(PixmapTextureModel& model)
{
	thetax = 1.5;
	thetay = 2.5;
	thetaz = 3.5;

	initdraw1(model);//,/*offsetx+*/100,/*offsety+*/100);

}

int PixmapTexture::drawmain(Display **dpy, Window *w, int offsetx, int offsety)
{
	//drawcurved3(dpy,w,offsetx,offsety);
	//drawsmallandrotate(dpy,w,offsetx+200,offsety+200);
	//drawenlargeandrotate2(dpy,w,offsetx+100,offsety+100);
	drawbiggerandrotate(dpy,w,offsetx+100,offsety+100);
	//drawsmaller(dpy,w,offsetx+200,offsety+200,1,1);
	//draw3(dpy,w);
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double fracx = _w/_enlargew, fracy = _h/_enlargeh;
	int prevx = 0, prevy = 0;
	
	for (int yy = 0; yy < _enlargeh; yy++) {
		for (int xx = 0; xx < _enlargew; xx++) { 
			//_alpha += 5;//0.9;
			_alpha = 5;//0.9;
			_beta = 5;
			Point pt(xx*fracx,yy*fracy,1);
	
					
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
			XDrawLine(*dpy, *w, gc,
				offsetx+(int)pt.get_x(),
				offsety+(int)pt.get_y(),
				offsetx+(int)pt.get_x(),
				offsety+(int)pt.get_y());
			for (int k = prevy/_beta; k < pt.get_y(); k++)  {
				for (int j = prevx/_alpha; j < pt.get_x(); j++)  {
				XDrawLine(*dpy, *w, gc,
					offsetx+(int)prevx/_alpha+j,
					offsety+(int)prevy/_beta+k,
					offsetx+(int)prevx/_alpha+j,
					offsety+(int)prevy/_beta+k);
			}
			}
			prevx = xx;//pt.get_x();//xx
			prevy = yy;//pt.get_y();
			}
			}
	return 0;
}
//draw smaller version with curved sides (e.g. dungeon tower)
int PixmapTexture::drawcurved(Display **dpy, Window *w, int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	double fracx = _w/_enlargew, fracy = _h/_enlargeh;
	for (int xx = 0; xx < _w; xx++) { 
		for (int yy = 0; yy < _h; yy++) {
				//Point p1((*vi)[i-1]);
				//Point p2((*vi)[i]);
				//Point p1(_polygons[0][0].get_x(),_polygons[0][0].get_y(),1);
				Point pt(xx*fracx,yy*fracy,1);
				Point p2(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				//pt = pt.scaley(angle);//_pixmaptexture.get_alpha());
				//_globalalpha +=  _alpha;
				//_alpha += 5;//0.9;
				//Point pt(((int)((xx*_alpha/_enlargew))),((int)((yy*_alpha/_enlargeh))),1);
			//	//_global += 1;
	
					
				//unsigned long color = 65000;
				unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				//if (_globalalpha > 1) {
				for (int j = prevx; j < xx*_alpha/_enlargew; j++) {
				for (int k = prevy; k < yy*_alpha/_enlargeh; k++) {
					Point pt2((int)((xx+j)*_alpha/_enlargew),(int)((yy)*_alpha/_enlargeh),1);
					XDrawLine(*dpy, *w, gc,offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y(),offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y());
					Point pt3((int)((xx)*_alpha/_enlargew),(int)((yy+k)*_alpha/_enlargeh),1);
					XDrawLine(*dpy, *w, gc,offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y(),offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y());
				}
				}
				//	_global = 0;
				//	_globalalpha = 0;
				//}
				prevy = yy*_alpha/_enlargeh;
				prevx = xx*_alpha/_enlargew;
			}
			}
			//}
//		}
		
	return 0;
}
int PixmapTexture::draw3(Display **dpy, Window *w)
{
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

	const std::string filename("./post.xpm");
	//NOTE: do not draw polygon lines, rather texture in between 
	//NOTE: polygons are fixed at 4 points
//	ray3d::Polygon poly;
/*	poly += ray3d::Point(20,20,20);
	poly += ray3d::Point(102,102,102);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(20,20,20);
	_polygons.push_back(poly);
*/	double prevxx = 0, prevyy = 0;
	//for (PolygonVector::iterator vi = _polygons.begin(); vi != _polygons.end(); vi++ ) {
			//for (int i = 0; i < 4; i++) {
			for (int xx = 0; xx < get_w(); xx++) { 
			for (int yy = 0; yy < get_h(); yy++) {
				//Point p1((*vi)[i-1]);
				//Point p2((*vi)[i]);
				//Point p1(_polygons[0][0].get_x(),_polygons[0][0].get_y(),1);
				Point p2(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				//pt = pt.scaley(angle);//_pixmaptexture.get_alpha());
				_alpha -= 0.001;
				//_alpha += 0.001;
				Point pt(((int)(xx*(_alpha))%24),((int)(yy*(_alpha))%24),1);
				int j = 0;
				for (j = 0; j < prevxx; j++) {
					if (pt.get_x()-prevxx > 1) {
        				gc = XCreateGC(*dpy, *w, valuemask, &values);
					XDrawLine(*dpy, *w, gc,200+(int)pt.get_x()+j,200+(int)pt.get_y(),200+(int)pt.get_x()+j,200+(int)pt.get_y());
					} else { break; }
				}
				XDrawLine(*dpy, *w, gc,100+(int)pt.get_x()+j,100+(int)pt.get_y(),100+(int)pt.get_x()+j,100+(int)pt.get_y());
				//unsigned long color = 65000;
				unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				/////XDrawLine(*dpy, *w, gc, p1.get_x()+(int)pt.get_x(),p1.get_y()+(int)pt.get_y(),p1.get_x()+(int)pt.get_x(),p1.get_y()+(int)pt.get_y());
				XDrawLine(*dpy, *w, gc,100+(int)pt.get_x(),100+(int)pt.get_y(),100+(int)pt.get_x(),100+(int)pt.get_y());
				prevxx = xx;
			}
			}
			//}
//		}
		
	return 0;
}
//draw smaller version with curved sides (e.g. dungeon tower)
int PixmapTexture::drawcurved3(Display **dpy, Window *w, int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	double fracx = _w/_enlargew, fracy = _h/_enlargeh;
	for (int xx = 0; xx < _w; xx++) { 
		for (int yy = 0; yy < _h; yy++) {
				Point pt(xx*fracx,yy*fracy,1);
				Point p2(xx,yy,1);
				//_alpha += 5;//0.9;
				_alpha += 5;//0.9;
				//Point pt(((int)((xx*_alpha/_enlargew))),((int)((yy*_alpha/_enlargeh))),1);
				unsigned long color = 65000;
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				XDrawLine(*dpy, *w, gc,offsetx+xx/_alpha,offsety+yy/_alpha,offsetx+xx,offsety+yy);
					
					
				//unsigned long color = 65000;
				unsigned long color2 = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color2;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				//if (_globalalpha > 1) {
				for (int j = prevx; j < xx*_alpha/_enlargew; j++) {
				for (int k = prevy; k < yy*_alpha/_enlargeh; k++) {
					Point pt2((int)((xx+j)*_alpha/_enlargew),(int)((yy)*_alpha/_enlargeh),1);
					XDrawLine(*dpy, *w, gc,offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y(),offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y());
					Point pt3((int)((xx)*_alpha/_enlargew),(int)((yy+k)*_alpha/_enlargeh),1);
					XDrawLine(*dpy, *w, gc,offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y(),offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y());
				}
				}
				//}
				prevy = yy*_alpha/_enlargeh;
				prevx = xx*_alpha/_enlargew;
			}
			}
			//}
//		}
		
	return 0;
}

//put big pixmap translated through Z axis
int PixmapTexture::drawcurved2(Display **dpy, Window *w, int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	double fracx = _w/_enlargew, fracy = _h/_enlargeh;
	for (int xx = 0; xx < _w; xx++) { 
		for (int yy = 0; yy < _h; yy++) {
				//Point p1((*vi)[i-1]);
				//Point p2((*vi)[i]);
				//Point p1(_polygons[0][0].get_x(),_polygons[0][0].get_y(),1);
				Point pt(xx*fracx,yy*fracy,1);
				Point p2(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				//pt = pt.scaley(angle);//_pixmaptexture.get_alpha());
				//_globalalpha +=  _alpha;
				//_alpha += 5;//0.9;
				//Point pt(((int)((xx*_alpha/_enlargew))),((int)((yy*_alpha/_enlargeh))),1);
			//	//_global += 1;
	
					
				//unsigned long color = 65000;
				unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				//if (_globalalpha > 1) {
				for (int j = prevx; j < xx*_alpha/_enlargew; j++) {
				for (int k = prevy; k < yy*_alpha/_enlargeh; k++) {
					Point pt2((int)((xx+j)*_alpha/_enlargew),(int)((yy)*_alpha/_enlargeh),1);
        				Matrix3 rotmz = ray3d::rotatez(thetaz);
					Vector3 prot(pt2.get_x(),pt2.get_y(),pt2.get_z());
					prot = rotmz*prot;
					///////XDrawLine(*dpy, *w, gc,offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y(),offsetx+(int)pt2.get_x(),offsety+(int)pt2.get_y());
					XDrawLine(*dpy, *w, gc,offsetx+(int)prot[0],offsety+(int)prot[1],offsetx+(int)prot[0],offsety+(int)prot[1]);
					Point pt3((int)((xx)*_alpha/_enlargew),(int)((yy+k)*_alpha/_enlargeh),1);
					prot = Vector3(pt3.get_x(),pt3.get_y(),pt3.get_z());
					prot = rotmz*prot;
					///////XDrawLine(*dpy, *w, gc,offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y(),offsetx+(int)pt3.get_x(),offsety+(int)pt3.get_y());
					XDrawLine(*dpy, *w, gc,offsetx+(int)prot[0],offsety+(int)prot[1],offsetx+(int)prot[0],offsety+(int)prot[1]);
				}
				}
				//	_global = 0;
				//	_globalalpha = 0;
				//}
				prevy = yy*_alpha/_enlargeh;
				prevx = xx*_alpha/_enlargew;
			}
			}
			//}
//		}
		
	return 0;
}
//draw smaller version, straight walls, Quake
int PixmapTexture::drawsmall(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	double fracx = _w/5, fracy = _h/5;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h; yy += fracy) {
		for (int xx = 0; xx < _w; xx += fracx) { 
			Point pt(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				_alpha += 5;//0.9;
				_beta += 5;//0.9;
					
				//unsigned long color = 65000;
				unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				XDrawLine(*dpy, *w, gc,
				offsetx+(int)dx,
				offsety+(int)dy,
				offsetx+(int)dx,
				offsety+(int)dy);
				dx ++;
			}
			dy ++;
			}
			//}
//		}
		
	return 0;
}
//draw smaller version, straight walls, Quake and rotate
int PixmapTexture::drawsmallandrotate(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;
	//_alpha = 5;
	//_beta = 5;
	double prevx=0,prevy=0;
	double fracx = _w/_alpha, fracy = _h/_beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h; yy += fracy) {
		for (int xx = 0; xx < _w; xx += fracx) { 
			Point pt(xx,yy,1);
				//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
				_alpha += _alpha;//0.9;
				_beta += _beta;//0.9;
					
				//unsigned long color = 65000;
				unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				XDrawLine(*dpy, *w, gc,
				offsetx+(int)dx,
				offsety+(int)dy,
				offsetx+(int)dx,
				offsety+(int)dy);
				dx ++;
			}
			dy ++;
			}
			//}
//		}
		
	return 0;
}
//draw enlargement version/
int PixmapTexture::drawbig(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	_alpha = 5;
	_beta = 5;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
			_alpha += 5;//0.9;
			_beta += 5;//0.9;
					
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
			XDrawLine(*dpy, *w, gc,
				offsetx+(int)xx/_alpha,
				offsety+(int)yy/_beta,
				offsetx+(int)xx/_alpha,
				offsety+(int)yy/_beta);
				dx ++;
			}
			dy ++;
			}
		
	return 0;
}
//draw enlarged version 2 (xpm chars get projected towards you and the pic enlarges)
int PixmapTexture::drawbigger(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	_alpha = 5;
	_beta = 5;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
        		Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			Vector3 prot(xx/_alpha,yy/_beta,1);
			//prot = rotmx*prot;
			//prot = rotmy*prot;
			prot = rotmx*prot;
			if (color != 0)//alpha channel black
			XDrawLine(*dpy, *w, gc,
				offsetx+(int)xx,
				offsety+(int)yy,
				offsetx+(int)xx,
				offsety+(int)yy);
			/*XDrawLine(*dpy, *w, gc,
				offsetx+(int)prot[0],
				offsety+(int)prot[1],
				offsetx+(int)prot[0],
				offsety+(int)prot[1]);
			*/	dx ++;
			}
			dy ++;
			}
		
	return 0;
}
int PixmapTexture::drawbiggerandrotate(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	_alpha = 5;
	_beta = 5;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
        		Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			thetax += 0.001;
			thetay += 0.001;
			thetaz += 0.001;
			Vector3 prot(xx/_alpha,yy/_beta,1);
			//prot = rotmz*prot;
			//prot = rotmy*prot;
			prot = rotmx*prot;
			if (color != 0)//alpha channel black
			/*XDrawLine(*dpy, *w, gc,
				offsetx+(int)xx,
				offsety+(int)yy,
				offsetx+(int)xx,
				offsety+(int)yy);
			*/XDrawLine(*dpy, *w, gc,
				offsetx+(int)prot[0],
				offsety+(int)prot[1],
				offsetx+(int)prot[0],
				offsety+(int)prot[1]);
				dx ++;
			}
			dy ++;
			}
		
	return 0;
}

int PixmapTexture::initdraw1(PixmapTextureModel& model)
{

	model.empty_points();

	double prevx=0,prevy=0;
	_alpha = 5;
	_beta = 5;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
        	/*	Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			thetax += 0.001;
			thetay += 0.001;
			thetaz += 0.001;
			Vector3 prot(xx/_alpha,yy/_beta,1);
			//prot = rotmz*prot;
			//prot = rotmy*prot;
			prot = rotmx*prot;
		*/
		if (color != 0)//alpha channel black
			/*XDrawLine(*dpy, *w, gc,
				offsetx+(int)xx,
				offsety+(int)yy,
				offsetx+(int)xx,
				offsety+(int)yy);
			*//*XDrawLine(*dpy, *w, gc,
				offsetx+(int)prot[0],
				offsety+(int)prot[1],
				offsetx+(int)prot[0],
				offsety+(int)prot[1]);
			*/	dx ++;
			//model.addpoint(Point(prot[0],prot[1],prot[2],color));
			model.addpoint(Point(xx/_alpha,yy,1,color));
			}
			dy ++;
		}
		
	return 0;
}
//enlarge with _alpha, _beta and rotate with thetax thetay,thetaz matrices
int PixmapTexture::rotatemodel(PixmapTextureModel& model)
{
	model.empty_points();

	int i = 0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
        		Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			thetax += 0.001;
			thetay += 0.001;
			thetaz += 0.001;
			Vector3 prot(xx,yy,1);
			//prot = rotmz*prot;
			//prot = rotmy*prot;
			prot = rotmx*prot;
			Point p(prot[0],prot[1],prot[2],color);
			if (color != 0)//alpha channel black
				model.addpoint(Point(p[0],p[1],p[2],p.get_color()));
		}
	}
	return 0;
}
//draw enlarged version with point vector3 proj/rot matrix.
int PixmapTexture::drawenlargeandrotate(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	_alpha = 5;
	_beta = 5;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
			thetax *= 1.5;
        		Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			Vector3 prot(xx,yy,1);
			//prot = rotmx*prot;
			XDrawLine(*dpy, *w, gc,
				offsetx+(int)prot[0],
				offsety+(int)prot[1],
				offsetx+(int)prot[2],
				offsety+(int)yy);
				dx ++;
			}
			dy ++;
			}
		
	return 0;
}
//draw rotation of pixmap
int PixmapTexture::drawenlargeandrotate2(Display **dpy, Window *w,int offsetx, int offsety)
{

/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

			//for (int i = 0; i < 4; i++) {
			//FIXME int ww = get_w() + get_w() * _alpha;
			//int hh = get_h() + get_h() * _alpha;

	double prevx=0,prevy=0;
	_alpha = 1;
	_beta = 1;
	double fracx = _alpha, fracy = _beta;//FIXME1 fixed 10
	int dx=0,dy=0;
	for (int yy = 0; yy < _h*_beta; yy ++) {
		for (int xx = 0; xx < _w*_alpha; xx ++) { 
			Point pt(xx/_alpha,yy/_beta,1);
			//Point pt = p2.scalex(angle);//_pixmaptexture.get_alpha());
			//unsigned long color = 65000;
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
			thetax *= 1.5;
        		Matrix3 rotmx = ray3d::rotatex(thetax);
        		Matrix3 rotmy = ray3d::rotatey(thetay);
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			Vector3 prot(xx,yy,1);
			prot = rotmx*prot;
			prot = rotmy*prot;
			prot = rotmz*prot;
			XDrawLine(*dpy, *w, gc,
				offsetx+(int)prot[0],
				offsety+(int)prot[1],
				offsetx+(int)prot[2],
				offsety+(int)yy);
				dx ++;
			}
			dy ++;
			}
		
	return 0;
}
//draw - smaller version of pixmap
int PixmapTexture::drawsmaller(Display **dpy, Window *w, int offsetx, int offsety, double a, double b)
{
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
*/	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);

	//NOTE: do not draw polygon lines, rather texture in between 
	//NOTE: polygons are fixed at 4 points
//	ray3d::Polygon poly;
/*	poly += ray3d::Point(20,20,20);
	poly += ray3d::Point(102,102,102);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(20,20,20);
	_polygons.push_back(poly);
*/	double dx = 0, dy = 0;
	for (int yy = 0; yy < _w; yy += b) {
		for (int xx = 0; xx < _h; xx += a) { 
			Point pt(xx,yy,1);
			unsigned long color = get_xpmimage().getpixel((int)pt.get_x(), (int)pt.get_y());
			values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        		Matrix3 rotmz = ray3d::rotatez(thetaz);
			Vector3 prot(dx,dy,1);
			prot = rotmz*prot;
        		gc = XCreateGC(*dpy, *w, valuemask, &values);
			//XDrawLine(*dpy, *w, gc,dx+offsetx,dy+offsety,dx+offsetx,dy+offsety);
			XDrawLine(*dpy, *w, gc,prot.get_x()+offsetx,prot.get_y()+offsety,prot.get_x()+offsetx,prot.get_y()+offsety);
			dx++;
			}
			dy++;
			}
		
	return 0;
}

int PixmapTexture::draw2(Display **dpy, Window *w)
{
/*	#define NIL (0)
  	XSetWindowAttributes attrib_create;
  	unsigned long create_mask = CWBackPixmap | CWBorderPixel |
                              CWOverrideRedirect | CWEventMask;

  	attrib_create.background_pixmap = None;
  	attrib_create.override_redirect = True;
  	attrib_create.event_mask = ButtonPressMask | ButtonReleaseMask |
                             ButtonMotionMask | EnterWindowMask;

	XChangeWindowAttributes(*dpy,*w,create_mask,&attrib_create);
	XGCValues values;
	values.foreground = 1400;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
	values.background = 2048;
	unsigned long valuemask = GCForeground | GCBackground;
        GC gc = XCreateGC(*dpy, *w, valuemask, &values);
      	//GC gc = XCreateGC(*dpy, *w, 0, NIL);

	const std::string filename("./post.xpm");
	//NOTE: do not draw polygon lines, rather texture in between 
	//NOTE: polygons are fixed at 4 points
	ray3d::Polygon poly;
	poly += ray3d::Point(2,2,2);
	poly += ray3d::Point(120,120,120);
	poly += ray3d::Point(20,20,20);
	poly += ray3d::Point(2,2,2);
	_polygons.push_back(poly);
	for (PolygonVector::iterator vi = _polygons.begin(); vi != _polygons.end(); vi++ ) {
			for (int i = 1; i < 5; i++) {
				Point p1((*vi)[i-1]);
				Point p2((*vi)[i]);
			
				Point p3(p1.scalex(_alpha));	
				unsigned long color = _xpmimage.getpixel(p3.get_x(), p3.get_y());
				values.foreground = color;//RedPixel(*dpy, DefaultScreen(*dpy));//2048;
        			gc = XCreateGC(*dpy, *w, valuemask, &values);
				XDrawLine(*dpy, *w, gc, p3.get_x(),p3.get_y(),p2.get_x(),p2.get_y());
			}
		}
*/		
	return 0;
}



} // namespace ray3d

