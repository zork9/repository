ECHO=echo
CXX=g++
CFLAGS=-c -Wall -I..
LDFLAGS=
SOURCES=\
test1.cpp

OBJS = ../RayManta.o ../RayMantaWindow.o ../WindowManager.o  ../Xmanager.o ../RayMantaImage.o ../RayMantaPoint.o ../RayMantaMatrix.o ../RayMantaMatrix3.o ../RayMantaNet.o ../RayMantaNetPthread.o ../RayMantaGA.o ../RayMantaNetMarkov2.o ../Boltzman.o ../RayMantaEngine.o ../RayMantaModel.o ../RayMantaSphereModel.o ../RayMantaPolygon.o ../RayMantaPolygonModel.o

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(OBJECTS) test1 
	
test1: 
	$(CXX) $(INCLUDES) $(OBJECTS) -o test1  -L../pondyparser -lpondyparser -L../xparser -lxparser -L../xlua -lxlua -L../lib -llua -L/usr/X11R6/lib -lX11 -lXext -lXpm -L.. $(OBJS) 

clean:
	rm -f *.o *.so test1
.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@
