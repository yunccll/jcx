include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include

PROJ_INC_PATHES += $(GTEST_INC_PATH)
PROJ_LIB_PATHES += $(GTEST_LIB_PATH)
PROJ_LIB_NAMES 	+= $(GTEST_LIB_NAME)


PROJ_LIB_PATHES 	+= $(PROJ_ROOT_SRC_PATH)/jcx/base 
PROJ_LIB_PATHES 	+= $(PROJ_ROOT_SRC_PATH)/jcx/logger
PROJ_LIB_PATHES 	+= $(PROJ_ROOT_SRC_PATH)/jcx/thread

PROJ_STATIC_LIBS 	+= pthread jcx_thread jcx_logger jcx_base

UT_DEST_EXCLUDE_OBJS 	+= ../main.o
CXX_OBJS  				+= $(UT_DEST_OBJS)

all: $(UT_TARGET_BIN)

$(UT_TARGET_BIN): $(OBJS)
	$(DO_CPP_TARGET)

clean:
	$(DO_UT_CLEAN)

clean.log:
	$(DO_CLEAN_LOG)	

ut:$(UT_TARGET_BIN)
	./$(UT_TARGET_BIN)
