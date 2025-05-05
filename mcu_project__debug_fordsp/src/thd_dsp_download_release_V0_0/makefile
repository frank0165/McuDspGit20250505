TARGET := doCtrl
#当前目录
mkfile_path=$(abspath $(lastword $(MAKEFILE_LIST)))
CurDir=$(dir $(mkfile_path))
#代码库根目录
RootDir=$(CurDir)
OBJ_DIR=$(RootDir)/build
KE := make
CC   := gcc
CXX  := g++
CXXFLAGS := -Wall -fPIC -g
CFLAGS   := -Wall -fPIC -g
USERFLAGS ?= -DCHIP_TYPE=$(CHIP_TYPE)
DEVICEDEF ?= -D_USE_FTDI_ 
JTAGFLAG ?= #-D_JTAG_TOOL_
COMPVERSION ?= #-DPUB_VERSION
SHARED :=
DEFINE_FLAGS := -D_GCC_TOOLS_ 

INCLUDE :=
SOURCES :=
########################################################

#依赖库目录
LIBRARY := -L${RootDir}
LIBRARY += #-lmpsse #-lwsock32 -lws2_32#-lGinkgo_Driver 

#LIBRARY :=
INCLUDE += -I${RootDir}
SOURCES += ${RootDir}/main_demo.c
SOURCES += ${RootDir}/do_cmd_struct.c
SOURCES += ${RootDir}/ip_op.c
SOURCES += ${RootDir}/reg_op.c
SOURCES += ${RootDir}/sre_fw.c
SOURCES += ${RootDir}/dsp_hpll_init.c


SOURCES_C   := $(filter %.c, $(SOURCES))
SOURCES_CPP := $(filter %.cpp, $(SOURCES))
OBJECTS_C   := $(addsuffix .o, $(basename $(SOURCES_C)))
OBJECTS_CPP := $(addsuffix .o, $(basename $(SOURCES_CPP)))
 
OBJECTS :=$(OBJECTS_C) $(OBJECTS_CPP)
 
all:$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(USERFLAGS) $(JTAGFLAG) $(DEVICEDEF) $(COMPVERSION) $(DEFINE_FLAGS) $(INCLUDE) -c $< -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(USERFLAGS) $(JTAGFLAG) $(DEVICEDEF) $(COMPVERSION) $(DEFINE_FLAGS) $(INCLUDE) -c $< -o $@

$(TARGET):$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(USERFLAGS) $(JTAGFLAG) $(DEVICEDEF) $(COMPVERSION) $(OBJECTS) $(LIBRARY) -o $@
	python pyclean.py

.PHONY: clean
clean:
	python pyclean.py all