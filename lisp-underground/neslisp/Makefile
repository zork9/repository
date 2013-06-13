CC=gcc
###INCLUDES=-I/usr/include/SDL

OBJS=lib.o \
	types.o \
	assembly_util.o \
	symboltable.o \
	stack.o \
	moose.o

all: neslisp 

neslisp: $(OBJS) 
	$(CC) -o neslisp $(OBJS) -lm ###-lSDL

clean:
	rm -f *.o neslisp 

.c.o:
	$(CC) $(INCLUDES) -c $<
