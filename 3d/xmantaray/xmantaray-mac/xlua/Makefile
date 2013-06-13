ECHO=echo
CXX=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=\
xlua.cpp \
xluacode.cpp

OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libxlua.so


all: $(SOURCES) $(OBJECTS) $(LIBRARY)
	
clean:
	rm -f *.o *.so *.a

$(LIBRARY): $(OBJECTS) 
	@echo "***COMPILER NOTE*** if this fails repath liblua.so or liblua.a in the local Makefile"
	ar rcu libxlua.a *.o
	ranlib libxlua.a

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@
