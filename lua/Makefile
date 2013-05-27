# (C)2004-20010 SourceMod Development Team
# Makefile written by David "BAILOPAN" Anderson


SMSDK = ..
MMSOURCE19 = ../../mmsource-central

#####################################
### EDIT BELOW FOR OTHER PROJECTS ###
#####################################

PROJECT = lua.jit.x86

OBJECTS = luajit/lib_aux.c luajit/lib_base.c luajit/lib_bit.c luajit/lib_debug.c luajit/lib_ffi.c luajit/lib_init.c luajit/lib_io.c \
          luajit/lib_jit.c luajit/lib_math.c luajit/lib_os.c luajit/lib_package.c luajit/lib_string.c luajit/lib_table.c luajit/lj_alloc.c \
          luajit/lj_api.c luajit/lj_asm.c luajit/lj_bc.c luajit/lj_bcread.c luajit/lj_bcwrite.c luajit/lj_carith.c luajit/lj_ccall.c \
          luajit/lj_ccallback.c luajit/lj_cconv.c luajit/lj_cdata.c luajit/lj_char.c luajit/lj_clib.c luajit/lj_cparse.c luajit/lj_crecord.c \
          luajit/lj_ctype.c luajit/lj_debug.c luajit/lj_dispatch.c luajit/lj_err.c luajit/lj_ffrecord.c luajit/lj_func.c luajit/lj_gc.c \
          luajit/lj_gdbjit.c luajit/lj_ir.c luajit/lj_lex.c luajit/lj_lib.c luajit/lj_load.c luajit/lj_mcode.c luajit/lj_meta.c luajit/lj_obj.c \
          luajit/lj_opt_dce.c luajit/lj_opt_fold.c luajit/lj_opt_loop.c luajit/lj_opt_mem.c luajit/lj_opt_narrow.c luajit/lj_opt_sink.c \
          luajit/lj_opt_split.c luajit/lj_parse.c luajit/lj_record.c luajit/lj_snap.c luajit/lj_state.c luajit/lj_str.c luajit/lj_strscan.c \
          luajit/lj_tab.c luajit/lj_trace.c luajit/lj_udata.c luajit/lj_vmevent.c luajit/lj_vmmath.c luajit/luajit.c LuaEngine.cpp

##############################################
### CONFIGURE ANY OTHER FLAGS/OPTIONS HERE ###
##############################################

C_OPT_FLAGS = -DNDEBUG -O3 -funroll-loops -pipe -fno-strict-aliasing
C_DEBUG_FLAGS = -D_DEBUG -DDEBUG -g -ggdb3
C_GCC4_FLAGS = -fvisibility=hidden
CPP_GCC4_FLAGS = -fvisibility-inlines-hidden
CPP = gcc


LINK = luajit/libluajit.a -m32 -ldl -lm -shared

INCLUDE = -I. -I.. -I$(SMSDK)/public -I$(SMSDK)/public/lua \
	-I$(SMSDK)/public/sourcepawn -I$(MMSOURCE19)/core/sourcehook -Iluajit -Idynasm

CFLAGS += -D_LINUX -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp \
	-D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp -Wall -DHAVE_STDINT_H \
	-m32 -Wno-uninitialized -Werror -msse -Wno-unused-but-set-variable
	
CPPFLAGS += -Wno-non-virtual-dtor -fno-exceptions -fno-rtti -Wno-delete-non-virtual-dtor


################################################
### DO NOT EDIT BELOW HERE FOR MOST PROJECTS ###
################################################

BINARY = $(PROJECT).so

ifeq "$(DEBUG)" "true"
	BIN_DIR = Debug
	CFLAGS += $(C_DEBUG_FLAGS)
else
	BIN_DIR = Release
	CFLAGS += $(C_OPT_FLAGS)
endif


IS_CLANG := $(shell $(CPP) --version | head -1 | grep clang > /dev/null && echo "1" || echo "0")

ifeq "$(IS_CLANG)" "1"
	CPP_MAJOR := $(shell $(CPP) --version | grep clang | sed "s/.*version /([0-9]/)*/.[0-9]*.*//1/")
	CPP_MINOR := $(shell $(CPP) --version | grep clang | sed "s/.*version [0-9]*/./([0-9]/)*.*//1/")
else
	CPP_MAJOR := $(shell $(CPP) -dumpversion >&1 | cut -b1)
	CPP_MINOR := $(shell $(CPP) -dumpversion >&1 | cut -b3)
endif

# If not clang
ifeq "$(IS_CLANG)" "0"
	CFLAGS += -mfpmath=sse
	LINK += -static-libgcc
endif

# Clang || GCC >= 4
ifeq "$(shell expr $(IS_CLANG) /| $(CPP_MAJOR) />= 4)" "1"
	CFLAGS += $(C_GCC4_FLAGS)
	CPPFLAGS += $(CPP_GCC4_FLAGS)
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
	mkdir -p $(BIN_DIR)/luajit
	$(MAKE) -f $(MAKEFILE_NAME) jit

jit: $(OBJ_BIN)
	$(CPP) $(INCLUDE) $(OBJ_BIN) $(LINK) -o $(BIN_DIR)/$(BINARY)

debug:
	$(MAKE) -f $(MAKEFILE_NAME) all DEBUG=true

clean:
	rm -rf $(BIN_DIR)/luajit/*.o
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/$(BINARY)

