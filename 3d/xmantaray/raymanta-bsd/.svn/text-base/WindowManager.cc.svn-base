//local
#include "WindowManager.h"
#include "RayManta.h"
#include "RayMantaWindow.h"

WindowManager::WindowManager() 
{
  unsigned int nchildren;
  Window win, root, parent, *children;
/*  Display *display = XOpenDisplay(dpy_name);
  if (!display) 
    {
      printf("error connecting to X server\n");
      exit(0);
    }
*//*  if ((XQueryTree(display, RootWindow(display, DefaultScreen(display)), &root, &parent, 
	     &children, &nchildren)) == 0)
    {
      printf("XQueryTree failed.\n");
    }
 */ // printf("children = %d\n", (int)nchildren);
/*  for (int i = 0; i < (int) nchildren; i++)
    {
      if (children[i] == None) 
	continue;
           
      XWindowAttributes attrib;
      if (XGetWindowAttributes(pixie.getDisplay(), children[i], &attrib)) 
	{
	  if (attrib.override_redirect) //ignore overrides
	    continue; 
	  if (attrib.map_state != IsUnmapped)  
	    {
	      new RayMantaWindow(children[i]);
	    }
	}
    }
*/  //  XMapWindow(display, RootWindow(display, DefaultScreen(display)));
  printf("made windowmanager\n");
}

WindowManager::~WindowManager()
{
}


