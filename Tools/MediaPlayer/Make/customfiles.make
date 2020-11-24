
# Please add new source files at the end of this list. Do not forget the "\"
# as a line continuation character on ALL BUT THE LAST lines.

SRCS_CPP += \
Source/Application/StreamingEngine.cpp \
Source/Construction/BoardUnits.cpp \
Source/Construction/ThreadConfiguration.cpp \
Source/Startup/Startup.cpp


# If a new directory is used under Source/, add it to the
# following search path:
VPATH +=\
$(PROJECTBASE)/:\
$(PROJECTBASE)/Source:\
$(PROJECTBASE)/Source/Application:\
$(PROJECTBASE)/Source/Construction:\
$(PROJECTBASE)/Source/Startup:\
$(PROJECTBASE)/../../Source:
