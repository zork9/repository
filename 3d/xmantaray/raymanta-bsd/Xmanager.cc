#include "RayManta.h"
#include "Xmanager.h"

Xmanager::Xmanager()
{}

void Xmanager::init(DisplayBase<Display **>& dpyb)
{
  long event_mask;

  root_window = RootWindow(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display())));
  depth = DefaultDepth(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display())));
  visual = DefaultVisual(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display())));
  screen = DefaultScreen(*(dpyb.get_display()));
  //XSetErrorHandler((XErrorHandler) handleXErrors);

/*  //XGrabServer(*(dpyb.get_display()));
  //XrmInitialize();
  //XSynchronize(*(dpyb.get_display()), False);
  //XSync(*(dpyb.get_display()), False);
  //XUngrabServer(*(dpyb.get_display()));
  //XCreateSimpleWindow(*(dpyb.get_display()), XRootWindow(*(dpyb.get_display()) , DefaultScreen(*(dpyb.get_display()))), 0,0,1280,1024, 0, 0,0);
  event_mask = ButtonPressMask | ButtonReleaseMask |
    ColormapChangeMask | EnterWindowMask | PropertyChangeMask | 
    SubstructureRedirectMask | KeyPressMask | KeyReleaseMask;
  XSelectInput(*(dpyb.get_display()), root_window, event_mask);
  Cursor cursor;
  Pixmap pixmap_cursor, mask_cursor;
  XpmAttributes xpm_attrib;
  xpm_attrib.valuemask = XpmExactColors|XpmCloseness|XpmDepth;
  xpm_attrib.exactColors = False;
  xpm_attrib.closeness = 40000;
  xpm_attrib.depth = 1;
  
  if (0 == XpmReadFileToPixmap(*(dpyb.get_display()), root_window,
			       "/usr/X11R6/include/X11/pixmaps/mini-x.xpm",
			       &pixmap_cursor,&mask_cursor,&xpm_attrib)) 
    {
      XColor  closest, exact, closest2, exact2;
      int status;
      status = XAllocNamedColor(*(dpyb.get_display()), 
				DefaultColormap(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display()))), 
				"black", &exact, &closest);
      XAllocNamedColor(*(dpyb.get_display()), DefaultColormap(*(dpyb.get_display()), DefaultScreen(*(dpyb.get_display()))),
		       "lightgreen", &exact2, &closest2);
      if (status == 0) { printf("failed to alloc color\n");}
  
      cursor = XCreatePixmapCursor(*(dpyb.get_display()), pixmap_cursor,
					  mask_cursor, &closest,
					  &closest2, 0,0);
      XDefineCursor(*(dpyb.get_display()), root_window, cursor);//global cursor set
    }
  else 
    {
      printf("cursor pixmap failed.\n");
    }
  */
  printf("made xmanager\n");
}

Xmanager::~Xmanager()
{

}

static const char *getFontElement(const char *pattern, char *buf, int bufsiz, ...) {
  const char *p, *v;
  char *p2;
  va_list va;

  va_start(va, bufsiz);
  buf[bufsiz-1] = 0;
  buf[bufsiz-2] = '*';
  while((v = va_arg(va, char *)) != NULL) {
    p = strcasestr(pattern, v);
    if (p) {
      strncpy(buf, p+1, bufsiz-2);
      p2 = strchr(buf, '-');
      if (p2) *p2=0;
      va_end(va);
      return p;
    }
  }
  va_end(va);
  strncpy(buf, "*", bufsiz);
  return NULL;
}

static const char *getFontSize(const char *pattern, int *size) {
  const char *p;
  const char *p2=NULL;
  int n=0;

  for (p=pattern; 1; p++) {
    if (!*p) {
      if (p2!=NULL && n>1 && n<72) {
	*size = n; return p2+1;
      } else {
	*size = 16; return NULL;
      }
    } else if (*p=='-') {
      if (n>1 && n<72 && p2!=NULL) {
	*size = n;
	return p2+1;
      }
      p2=p; n=0;
    } else if (*p>='0' && *p<='9' && p2!=NULL) {
      n *= 10;
      n += *p-'0';
    } else {
      p2=NULL; n=0;
    }
  }
}

XFontSet Xmanager::createFontSet(DisplayBase<Display **>& dpyb)
{
  const char *fontname = "fixed";
#define   FONT_ELEMENT_SIZE 50
  XFontSet fs;
  char **missing;
  char *def = (char *)"-";
  int nmissing, pixel_size = 0, buf_size = 0;
  char weight[FONT_ELEMENT_SIZE], slant[FONT_ELEMENT_SIZE];

  fs = XCreateFontSet(*(dpyb.get_display()),
		      fontname, &missing, &nmissing, &def);
  if (fs && (! nmissing)) return fs;
  
#ifdef    HAVE_SETLOCALE
  if (! fs) {
    if (nmissing) XFreeStringList(missing);

    setlocale(LC_CTYPE, "C");
    fs = XCreateFontSet(*(dpyb.get_display()), fontname,
			&missing, &nmissing, &def);
    setlocale(LC_CTYPE, "");
  }
#endif // HAVE_SETLOCALE

  if (fs) {
    XFontStruct **fontstructs;
    char **fontnames;
    XFontsOfFontSet(fs, &fontstructs, &fontnames);
    fontname = fontnames[0];
  }

  getFontElement(fontname, weight, FONT_ELEMENT_SIZE,
		 "-medium-", "-bold-", "-demibold-", "-regular-", NULL);
  getFontElement(fontname, slant, FONT_ELEMENT_SIZE,
		 "-r-", "-i-", "-o-", "-ri-", "-ro-", NULL);
  getFontSize(fontname, &pixel_size);

  if (! strcmp(weight, "*")) strncpy(weight, "medium", FONT_ELEMENT_SIZE);
  if (! strcmp(slant, "*")) strncpy(slant, "r", FONT_ELEMENT_SIZE);
  if (pixel_size < 3) pixel_size = 3;
  else if (pixel_size > 97) pixel_size = 97;

  buf_size = strlen(fontname) + (FONT_ELEMENT_SIZE * 2) + 64;
  char *pattern2 = new char[buf_size];
  snprintf(pattern2, buf_size - 1,
	   "%s,"
	   "-*-*-%s-%s-*-*-%d-*-*-*-*-*-*-*,"
	   "-*-*-*-*-*-*-%d-*-*-*-*-*-*-*,*",
	   fontname, weight, slant, pixel_size, pixel_size);
  fontname = pattern2;

  if (nmissing) XFreeStringList(missing);
  if (fs) XFreeFontSet(*(dpyb.get_display()), fs);

  fs = XCreateFontSet(*(dpyb.get_display()), fontname,
		      &missing, &nmissing, &def);
  delete [] pattern2;

  return fs;
}
