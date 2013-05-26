# (C)2004-2008 SourceMod Development Team
# Makefile written by David "BAILOPAN" Anderson

SMSDK = ../..
MMSOURCE19 = ../../../mmsource-central

#####################################
### EDIT BELOW FOR OTHER PROJECTS ###
#####################################

PROJECT = simillimum.jit.x86

OBJECTS = BaseRuntime.cpp engine2.cpp dll_exports.cpp jit_function.cpp sp_vm_basecontext.cpp sp_vm_engine.cpp \
          sp_vm_function.cpp x86/jit_x86.cpp x86/opcode_helpers.cpp zlib/adler32.c zlib/compress.c zlib/crc32.c \
          zlib/deflate.c zlib/gzio.c zlib/infback.c zlib/inffast.c zlib/inflate.c zlib/inftrees.c zlib/trees.c \
          zlib/uncompr.c zlib/zutil.c md5/md5.cpp ../../knight/shared/KeCodeAllocator.cpp



##############################################
### CONFIGURE ANY OTHER FLAGS/OPTIONS HERE ###
##############################################

C_OPT_FLAGS = -DNDEBUG -O3 -funroll-loops -pipe -fno-strict-aliasing
C_DEBUG_FLAGS = -D_DEBUG -DDEBUG -g -ggdb3
C_GCC4_FLAGS = -fvisibility=hidden
CPP_GCC4_FLAGS = -fvisibility-inlines-hidden
CPP = gcc
CPP_OSX = clang

OS := $(shell uname -s)

ifeq "$(OS)" "Darwin"
	LIB_EXT = dylib
else
	LIB_EXT = so
endif


LINK = -m32 -ldl -lm

INCLUDE = -I. -I.. -I$(SMSDK)/public -I$(SMSDK)/public/jit -I$(SMSDK)/public/jit/x86 \
	-I$(SMSDK)/public/sourcepawn -I$(MMSOURCE19)/core/sourcehook -I$(SMSDK)/knight/shared -Ix86

CFLAGS += -D_LINUX -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp \
	-D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp -Wall -DHAVE_STDINT_H \
	-m32 -Wno-uninitialized -Werror -msse -Wno-unused-but-set-variable
CPPFLAGS += -Wno-non-virtual-dtor -fno-exceptions -fno-rtti -Wno-delete-non-virtual-dtor

################################################
### DO NOT EDIT BELOW HERE FOR MOST PROJECTS ###
################################################

BINARY = $(PROJECT).$(LIB_EXT)

ifeq "$(DEBUG)" "true"
	BIN_DIR = Debug
	CFLAGS += $(C_DEBUG_FLAGS)
else
	BIN_DIR = Release
	CFLAGS += $(C_OPT_FLAGS)
endif

ifeq "$(USEMETA)" "true"
	BIN_DIR := $(BIN_DIR).$(ENGINE)
endif

ifeq "$(OS)" "Darwin"
	CPP = $(CPP_OSX)
	LIB_EXT = dylib
	CFLAGS += -DOSX -D_OSX
	LINK += -dynamiclib -lstdc++ -mmacosx-version-min=10.5
else
	LIB_EXT = so
	CFLAGS += -D_LINUX
	LINK += -shared
endif

IS_CLANG := $(shell $(CPP) --version | head -1 | grep clang > /dev/null && echo "1" || echo "0")

ifeq "$(IS_CLANG)" "1"
	CPP_MAJOR := $(shell $(CPP) --version | grep clang | sed "s/.*version \([0-9]\)*\.[0-9]*.*/\1/")
	CPP_MINOR := $(shell $(CPP) --version | grep clang | sed "s/.*version [0-9]*\.\([0-9]\)*.*/\1/")
else
	CPP_MAJOR := $(shell $(CPP) -dumpversion >&1 | cut -b1)
	CPP_MINOR := $(shell $(CPP) -dumpversion >&1 | cut -b3)
endif

# If not clang
ifeq "$(IS_CLANG)" "0"
	CFLAGS += -mfpmath=sse
endif

# Clang || GCC >= 4
ifeq "$(shell expr $(IS_CLANG) \| $(CPP_MAJOR) \>= 4)" "1"
	CFLAGS += $(C_GCC4_FLAGS)
	CPPFLAGS += $(CPP_GCC4_FLAGS)
endif


# OS is Linux and not using clang
ifeq "$(shell expr $(OS) \= Linux \& $(IS_CLANG) \= 0)" "1"
	LINK += -static-libgcc
endif

OBJ_BIN := $(OBJECTS:../../knight/shared/%.cpp=$(BIN_DIR)/knight/%.o)
OBJ_BIN := $(OBJ_BIN:%.cpp=$(BIN_DIR)/%.o)
OBJ_BIN := $(OBJ_BIN:%.c=$(BIN_DIR)/%.o)

# This will break if we include other Makefiles, but is fine for now. It allows
#  us to make a copy of this file that uses altered paths (ie. Makefile.mine)
#  or other changes without mucking up the original.
MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))



default: all

$(BIN_DIR)/%.o: %.c
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(BIN_DIR)/knight/%.o: ../../knight/shared/%.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)/x86
	mkdir -p $(BIN_DIR)/zlib
	mkdir -p $(BIN_DIR)/knight
	mkdir -p $(BIN_DIR)/md5
	$(MAKE) -f $(MAKEFILE_NAME) jit

jit: $(OBJ_BIN)
	$(CPP) $(INCLUDE) $(OBJ_BIN) $(LINK) -o $(BIN_DIR)/$(BINARY)

debug:
	$(MAKE) -f $(MAKEFILE_NAME) all DEBUG=true

clean:
	rm -rf $(BIN_DIR)/x86/*.o
	rm -rf $(BIN_DIR)/zlib/*.o
	rm -rf $(BIN_DIR)/knight/*.o
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/$(BINARY)

