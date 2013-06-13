#
# An example GNUmakefile
#

# Include the common variables defined by the Makefile Package
include $(GNUSTEP_MAKEFILES)/common.make

# Two libraries
LIBRARY_NAME = liborb 

#
# The files for the liborb library
#
# The Objective-C files to compile
liborb_OBJC_FILES = Bean.m Broker.m Client.m ClientProxy.m Daemon.m Model.m Observer.m ObserverProxy.m Orb.m Server.m ServerProxy.m TCPServer.m

# The C source files to be compiled
liborb_C_FILES =

# The PostScript wrap source files to be compiled
##FIXMEliborb_PSWRAP_FILES = drawing.psw

# The header files for the library
liborb_HEADER_FILES_DIR = ###FIXME./orb
liborb_HEADER_FILES_INSTALL_DIR = liborb 
liborb_HEADER_FILES = 

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
