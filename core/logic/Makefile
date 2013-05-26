# (C)2004-2010 SourceMod Development Team
# Makefile written by David "BAILOPAN" Anderson

SMSDK = ../..
MMSOURCE19 = ../../../mmsource-central

#####################################
### EDIT BELOW FOR OTHER PROJECTS ###
#####################################

PROJECT = simillimum.logic

OBJECTS = common_logic.cpp smn_adt_array.cpp smn_sorting.cpp smn_maplists.cpp smn_adt_stack.cpp thread/ThreadWorker.cpp thread/BaseWorker.cpp \
          ThreadSupport.cpp smn_float.cpp TextParsers.cpp smn_textparse.cpp smn_adt_trie.cpp Profiler.cpp smn_functions.cpp smn_timers.cpp \
          smn_players.cpp MemoryUtils.cpp smn_admin.cpp smn_banning.cpp smn_filesystem.cpp stringutil.cpp Translator.cpp PhraseCollection.cpp \
          smn_lang.cpp smn_string.cpp smn_handles.cpp smn_datapacks.cpp smn_gameconfigs.cpp smn_fakenatives.cpp GameConfigs.cpp sm_crc32.cpp \
          smn_profiler.cpp ShareSys.cpp PluginSys.cpp HandleSys.cpp NativeOwner.cpp NativeInvoker.cpp ExtensionSys.cpp DebugReporter.cpp



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


LINK += -lpthread -m32 -ldl -lm
	
INCLUDE += -I. -I$(MMSOURCE19)/core/sourcehook -I$(SMSDK)/public -I$(SMSDK)/public/sourcepawn

CFLAGS += -D_LINUX -DPOSIX -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp \
	-D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp -Wall -Werror \
	-Wno-uninitialized -Wno-unused -mfpmath=sse -msse -DSOURCEMOD_BUILD -DHAVE_STDINT_H -DSM_DEFAULT_THREADER -m32 \
	-DSM_LOGIC -Wno-non-virtual-dtor -Wno-narrowing
CPPFLAGS += -Wno-non-virtual-dtor -fno-exceptions -fno-rtti

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

# Clang >= 3 || GCC >= 4.7
ifeq "$(shell expr $(IS_CLANG) \& $(CPP_MAJOR) \>= 3 \| $(CPP_MAJOR) \>= 4 \& $(CPP_MINOR) \>= 7)" "1"
	CFLAGS += -Wno-delete-non-virtual-dtor
endif

# OS is Linux and not using clang
ifeq "$(shell expr $(OS) \= Linux \& $(IS_CLANG) \= 0)" "1"
	LINK += -static-libgcc
endif

OBJ_BIN := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

# This will break if we include other Makefiles, but is fine for now. It allows
#  us to make a copy of this file that uses altered paths (ie. Makefile.mine)
#  or other changes without mucking up the original.
MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))


$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(BIN_DIR)/%.o: %.c
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all: 
	mkdir -p $(BIN_DIR)/thread
	$(MAKE) -f $(MAKEFILE_NAME) sourcemod

sourcemod: $(OBJ_BIN)
	$(CPP) $(INCLUDE) $(OBJ_BIN) $(LINK) -o $(BIN_DIR)/$(BINARY)

debug:
	$(MAKE) -f $(MAKEFILE_NAME) all DEBUG=true

default: all

clean: 
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/thread/*.o
	rm -rf $(BIN_DIR)/$(BINARY)
