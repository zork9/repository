.SUFFIXES : .o .cc .c

### NOTE needs objc gcc for arm-eabi to compile on the ARM (GBA) itself
CC = gcc 
LD = ld
CFLAGS = -g -I/usr/include/GNUstep -I../include 
INCLUDES = 

OBJS = \
ByteCodeMachine.o \
JavaByteCodeMachine.o \
ArmAssemblerMachine.o \
6502AssemblerMachine.o \
### ClassLocator.o	\
Compiler.o \
Dispatcher.o \
Error.o \
FNString.o \
Fuzzy.o \
Object.o \
GBAObject.o \
Hex.o \
HashTable.o \
HashTableStrings.o \
HashTableTupleInts.o \
MethodName.o \
MethodNameArray.o \
ObjectLocator.o \
ParseString.o \
ParseTree.o \
ParseTreeOp.o \
ParseTreeOpLeaf.o \
Scanner.o \
Status.o \
Symbol.o \
SymbolTable.o \
Tuple.o \
TupleInt.o \
TupleIterator.o\
Type.o \
TypeChar.o \
TypeInt.o \
TypeVoid.o \
TypeTable.o \
TypeName.o \
TypeNameMem.o \
TypeNameArray.o \
WordBase.o \
Word.o \
Data.o \
DataArray.o \
scansystem.o \
ArmCompiler.o \
ArmScanner.o \
ArmSubCompiler.o \
ArmSubScanner.o \
ArmObjCCompiler.o \

LIBMEMORYOBJS = \
###libmemory/GBAChunk.o \
libmemory/GBAMemory.o \
libmemory/MemChunk.o \
libmemory/Memory.o \

all: lib 

lib: $(OBJS) $(LIBMEMORYOBJS)
	@echo "--"
	@echo "--"
	
	ar rcu carm.a *.o

clean: 
	rm *.o *.a

.m.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cc.o :
	$(CC) $(CFLAGS) $(INLCUDES) -c $<
