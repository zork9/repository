#
# An example GNUmakefile
#

# Include the common variables defined by the Makefile Package
include $(GNUSTEP_MAKEFILES)/common.make

# Two libraries
LIBRARY_NAME = liblisparm

#
# The files for the liblisparm library
#
# The Objective-C files to compile
liblisparm_OBJC_FILES = \
CNode.m Disk.m FileBuffer.m File.m Flock.m Fork.m GFXImage.m GFX.m GFXWidgets.m Kernel.m libcmacros.m Malloc.m Node.m OTree.m RamDisk.m RuntimeExample.m String.m Tree.m \

# The C source files to be compiled
liblisparm_C_FILES =

# The PostScript wrap source files to be compiled
##FIXMEliblisparm_PSWRAP_FILES = drawing.psw

# The header files for the library
liblisparm_HEADER_FILES_DIR = ###FIXME./liblisparm
liblisparm_HEADER_FILES_INSTALL_DIR = liblisparm 
liblisparm_HEADER_FILES = 

#
# The files for the libtwo library
#
# The Objective-C files to compile
###libtwo_OBJC_FILES = two.m another.m test.m

# The header files for the library
###libtwo_HEADER_FILES_DIR = ./two
###libtwo_HEADER_FILES_INSTALL_DIR = two
###libtwo_HEADER_FILES = two.h another.h test.h common.h

# Option include to set any additional variables
-include GNUmakefile.preamble

# Include in the rules for making libraries
include $(GNUSTEP_MAKEFILES)/library.make

# Option include to define any additional rules
-include GNUmakefile.postamble
