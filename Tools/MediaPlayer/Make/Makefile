# Application Makefile for MediaPlayer project

# Typical targets you will want to call are:
# make TARGET=os21dbg depend - create dependencies for this build
# make TARGET=os21dbg        - build debug version for OS21, ST40
# make TARGET=os21dbg clean  - clean up the mess
# make TARGET=os21rel   ...dto..same for os20.

# When top level directories are moved around, this will have to be adapted.
# VIEWBASE is pointing to the view's base directory
# TOOLBASE points to the location of the Makefile snippets
# DRVBASE is used for references to other components in the driver vob - also for Makefile snippets
# PROJECTBASE is used for project-local files (sources & headers location...)
#
# DRVBASE is in Unix path notation, DRVBASE_W is the same in 'simplified Win notation'
# (Example: Unix: /e/ccviews/toto_dv/bla  Windows: e:/ccviews/toto_dv/bla)
# Unix notation is needed e.g. for VPATH, Windows notation is needed for the
# actual Compiler (sh4gcc etc) invocation.

VIEWBASE   := $(shell echo `pwd` | sed -e 's/\/STCM_Application\/.*//')
PROJECTBASE:=$(VIEWBASE)/STCM_Application/Tools/MediaPlayer

# When the snippets get moved to their final destination, this might have to be changed.
TOOLBASE := $(VIEWBASE)/STCM_driver/STF/Make
NAVIGATIONTOOLBASE := 
FILESYSTEMTOOLBASE := 
NAVSUPPORTTOOLBASE := 
APPLICATIONTOOLBASE := 
DRIVEREXTGPLBASE := $(VIEWBASE)/STCM_driverExt/GPL

# selection of toolkit/operating system
include $(TOOLBASE)/osselect.make

DRVBASE:=$(shell echo `pwd` | sed -e 's/\/STCM_Application\/.*//')/STCM_driver
ifeq ($(HOST_OS), cygwin)
DRVBASE_W:=$(shell cygpath -m $(DRVBASE))
VIEWBASE_W := $(shell cygpath -m $(VIEWBASE))
PROJECTBASE_W:=$(shell cygpath -m $(PROJECTBASE))
else
DRVBASE_W:=$(DRVBASE)
VIEWBASE_W := $(VIEWBASE)
PROJECTBASE_W:=$(PROJECTBASE)
endif

FILELIST:=customfiles.make

# globally including the parent directory of the ThreadConfiguration.h file
export BOARDFLAGS += -I$(PROJECTBASE)/Source/Construction

# The flag USE_NO_MIN_STACK_SIZE controls minimum stack size during task creation in the release build only:
# If reset (0), the minimum task stack size defined by OSAL_MIN_STACK_SIZE is enforced if user stack 
# size is smaller than OSAL_MIN_STACK_SIZE.
# If   set (1), user defined stack size is used
export BOARDFLAGS += -DUSE_NO_MIN_STACK_SIZE=1


INCLUDEPATHS += -I$(DRVBASE_W) \
 -I$(PROJECTBASE_W)/Source/Application \
 -I$(VIEWBASE_W)/STCM_Application \
 -I$(VIEWBASE_W)/STCM_driver

# Bring in the list of source files and directories for this component
include $(FILELIST)

export BOARDFLAGS += -DDEBUG_SYSTEM_RESOURCE=0 -DDEBUG_MEMORY_PARTITION=0

# build type selection
include $(TOOLBASE)/buildtype.make

# generic build rules
include $(TOOLBASE)/rules.make


# header include paths and libs specific to this component
include $(TOOLBASE)/comp_stf.make
include $(TOOLBASE)/comp_vdr.make
include $(TOOLBASE)/comp_vdrsupport.make
include $(TOOLBASE)/comp_device.make

LIBS := $(DRIVEREXTGPLBASE)/libmpeg2-0.5.1/libmpeg2/.libs/libmpeg2.a $(LIBS)
LIBS := $(DRIVEREXTGPLBASE)/libmpeg2-0.5.1/libmpeg2/convert/.libs/libmpeg2convert.a $(LIBS)
LIBS := $(DRIVEREXTGPLBASE)/a52dec-0.7.4/liba52/.libs/liba52.a $(LIBS)

SUBDIRS:=\
 $(STFBASE_W)/Make \
 $(VDRBASE_W)/Make \
 $(VDRSUPPORTBASE_W)/Make \
 $(DEVICEBASE_W)/Make \
 $(DRIVEREXTGPLBASE)

# $$$ Should split "TARGET" up into BUILDTYPE=.., TARGETTYPE=.., CPU=.. ?
# $(MMEPLUSHOSTBASE_W)/Source/EMBX/Host/Make/STm8000Lib \

# Need to differentiante here between debug, release, ...
THISTARGET:=MediaPlayer

os21stp: dirs $(THISTARGET)

os21dbg: dirs $(THISTARGET)

os21rel: dirs $(THISTARGET)

os21prof: dirs $(THISTARGET)

os20dbg: dirs $(THISTARGET)

os20rel: dirs $(THISTARGET)

os20prof: dirs $(THISTARGET)

linuxpcusrdbg: dirs $(THISTARGET)

linuxst40usrdbg: dirs $(THISTARGET)


# Create the "build directory"
.PHONY: dirs

dirs:
	@mkdir -p $(OBJDIR)
	@list='$(SUBDIRS)'; for d in $$list; do \
	(echo "Making in $$d..." && cd $$d && $(MAKE) -s TARGET=$(TARGET)) || exit 5; \
	done ;
ifeq ($(wildcard .depend.$(TARGET)$(FEATURESTRING)),)
	@echo "==============================================================================="
	@echo "No .depend file for this config found - have you done 'make TARGET=xxx depend'?"
	@echo "==============================================================================="
endif

$(THISTARGET): $(OBJS) $(LIBS)
	@echo "***********************************"
	@echo "building for Linux platform (default)"
	@echo "***********************************"
	@echo Linking...
	@$(LD) -o $@ $(OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group -lstdc++ -lm -lpthread -lasound -la52 -lSDL2 -lSDL2main -lpulse -lpulse-simple

include $(TOOLBASE)/conflog.make
include $(TOOLBASE)/cleanrules.make

# It should be sufficient to "make dependall; make" to avoid recompiling.
dependall:
	@echo Rebuilding dependencies without cleaning. Please wait...
	@list='$(SUBDIRS)'; for d in $$list; do \
	(echo "Depending in $$d..." && cd $$d && $(MAKE) -s depend) || exit 5; \
	done ;
	@make -s depend	

# auxiliary variable, needed for dependency file list
DEPBASE_W:= $(VIEWBASE_W)/STCM_Application/Tools/MediaPlayer
include $(TOOLBASE)/deprules.make

