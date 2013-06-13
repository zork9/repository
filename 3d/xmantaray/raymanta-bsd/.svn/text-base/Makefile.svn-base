.SUFFIXES : .o .cc .c

CXX = g++
CC = gcc
INCLUDES = -I/usr/X11R6/include
CFLAGS = -g -I/usr/X11R6/include  -I/usr/X11R6/include/X11
LIBS = -L/usr/X11R6/lib -lX11 -lXpm -lXext -lpthread -L./lib ###-llua -L./xlua -lxlua
# -ljpeg -lpng -L./widget -lPixieWidget -lImlib
OBJS = RayManta.o RayMantaWindow.o WindowManager.o  Xmanager.o RayMantaImage.o RayMantaPoint.o RayMantaMatrix.o RayMantaMatrix3.o RayMantaMatrix4.o RayMantaNet.o RayMantaNetPthread.o RayMantaGA.o RayMantaNetMarkov2.o Boltzman.o RayMantaEngine.o RayMantaModel.o RayMantaSphereModel.o RayMantaPolygon.o RayMantaPolygonModel.o RayMantaImageBase.o RayMantaPixmapImage.o RayMantaTextureModel.o RayMantaPixmapTextureModel.o RayMantaTexture.o RayMantaPixmapTexture.o RayMantaBaseVisit.o RayMantaXNet.o keywords.o RayMantaPixmapTextureModelFill.o RayMantaPixmapTextureModelRotate.o RayMantaSpiderTexture.o RayMantaSpiderModel.o RayMantaRayTracer.o RayMantaProducerSystem.o

###FIXME add RayMantaNetMarkov.o

###FIXME RayManta: debug xlua $(OBJS) main.o
all: RayManta

RayManta: $(OBJS) main.o
	@echo "***COMPILER NOTE*** Please include RayMantaNetMarkov.o inside this Makefile for Markov networking (RayMantaNetMarkov2.o is mainstream included.)"
	ar rcu libraymanta.a *.o
	ranlib libraymanta.a
	$(CXX) $(CFLAGS) $(INCLUDES) $(OBJS) -o xmantaray  $(LIBS) main.o

clean: 
	rm *.o libraymanta.a xmantaray xmantaraytracer config.h ./xlua/*.o ./xlua/*.so ./xlua/*.a ./test/*.so ./test/*.o ./test/test1;

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

.cc.o :
	$(CXX) $(CFLAGS) ${INLCUDES} -c $< -o $@
