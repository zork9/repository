#ifndef RAYPIXMAPIMAGE_H
#define RAYPIXMAPIMAGE_H

#include<X11/Xlib.h>
#include<X11/xpm.h>
#include<string>

#include "RayMantaImageBase.h"

class RayMantaPixmapImage : public RayMantaImageBase 
{
 public:
  RayMantaPixmapImage();
  RayMantaPixmapImage(Display **dpy, std::string const& filename);
  int init() { XInitImage(image); return 0;}
  ~RayMantaPixmapImage();

  virtual int draw(Display **dpy, Window *w, int xx, int yy);
  virtual int putpixel(int xx, int yy, unsigned long value);
  virtual unsigned long getpixel(int xx, int yy);

protected:
  XImage *shape;


}; //class RayMantaPixmapImage

#endif
