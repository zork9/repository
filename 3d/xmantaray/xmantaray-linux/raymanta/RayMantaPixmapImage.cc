#include "RayMantaPixmapImage.h"
#include "RayManta.h"

RayMantaPixmapImage::RayMantaPixmapImage (Display **dpy, std::string const& filename)
{

  XpmAttributes attributes;
  attributes.valuemask = XpmReturnPixels | XpmReturnExtensions | XpmExactColors
    | XpmCloseness;
  attributes.exactColors = False;
  attributes.closeness = 40000;
  int ret;
  if((ret = XpmReadFileToImage(*dpy,
			 const_cast<char *>(const_cast<std::string&>(filename).c_str()),
			 &image,
			 &shape,
			 &attributes)) != 0)
    {
      printf("RayMantaPixmapImage's XpmReadPixmap from file : error %d\n", ret);
      delete this;
      return;
    }

}

RayMantaPixmapImage::~RayMantaPixmapImage ()
{
}

int RayMantaPixmapImage::draw(Display **dpy, Window *w, int destxx, int destyy)
{
#define NIL (0)
  GC gc = XCreateGC(*dpy, *w, 0, NIL);
  XPutImage(*dpy, *w, gc, image, 0,0,destxx,destyy,500,500);
}

int RayMantaPixmapImage::putpixel(int xx, int yy, unsigned long value)
{
	XPutPixel(image, xx,yy,value);

}

unsigned long RayMantaPixmapImage::getpixel(int xx, int yy)
{
	return XGetPixel(image, xx,yy);

}

