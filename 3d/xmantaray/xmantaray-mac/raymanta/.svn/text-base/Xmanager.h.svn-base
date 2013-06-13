#ifndef XMANAGER_H
#define XMANAGER_H

// libc 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
// X
#include <X11/Xlib.h>
#include <X11/xpm.h>
class RayManta;
//extern RayManta pixie;
template <class D> class DisplayBase;
class Xmanager {
 protected:
  
  int depth, screen;
  Visual *visual;
  Window root_window;
  XFontSet fontset;

 public:
  Xmanager();
  void init(DisplayBase<Display * *>& dpyb);
  ~Xmanager();
  XFontSet createFontSet(DisplayBase<Display **>& dpyb);
  inline int getScreen() {return screen;}
  inline Window getRootWindow() { return root_window; }
  inline int getDepth() { return depth; }
  inline Visual *getVisual() { return visual; }
  inline XFontSet getFontSet() { return fontset; }
}; //class Xmanager

static const char *getFontElement(const char *pattern, char *buf, int bufsiz, ...);
static const char *getFontSize(const char *pattern, int *size);
#endif
