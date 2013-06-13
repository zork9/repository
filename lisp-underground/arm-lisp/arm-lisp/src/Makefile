.SUFFIXES : .o .cc .c

### NOTE needs objc gcc for arm-eabi to compile on the ARM (GBA) itself
CC = gcc 
LD = ld
CFLAGS = -g -I/usr/include/GNUstep -I../include 
INCLUDES = 

OBJS = \
6502AssemblerMachine.o ArmAssemblerMachine.o ArmCompiler.o ArmCompilerBase.o ArmLispCompiler.o ArmLispScanner.o ArmScanner.o ArmSubCompiler.o ArmSubScanner.o ByteCodeMachine.o ClassLocator.o Compiler.o Data.o DataArray.o Dispatcher.o Error.o ErrorSubCompiler.o FNString.o FileBuffer.o FileName.o FileStream.o Form.o Fuzzy.o GBAObject.o HashTable.o HashTableStrings.o HashTableTupleInts.o Hex.o JavaByteCodeMachine.o MethodName.o MethodNameArray.o Node.o Object.o ObjectLocator.o Operator.o OperatorTable.o ParseString.o ParseTree.o ParseTreeOp.o ParseTreeOpLeaf.o ScanSystem.o Scanner.o Stack.o Status.o Structure.o StructureBracket.o Symbol.o SymbolArm.o SymbolTable.o SymbolTableArm.o Tuple.o TupleInt.o TupleIterator.o Type.o TypeChar.o TypeInt.o TypeName.o TypeNameArray.o TypeNameMem.o TypeTable.o TypeVoid.o Util.o Word.o WordBase.o main.o

LIBMEMORYOBJS = \
###libmemory/GBAChunk.o \
libmemory/GBAMemory.o \
libmemory/MemChunk.o \
libmemory/Memory.o \

all: lib 

lib: $(OBJS) $(LIBMEMORYOBJS)
	@echo "--"
	@echo "--"
	gcc -c -I/usr/include/GNUstep main.m
	gcc -o arm-lisp *.o -framework Cocoa	
##	ar rcu carm.a *.o

clean: 
	rm *.o *.a

.m.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cc.o :
	$(CC) $(CFLAGS) $(INLCUDES) -c $<
