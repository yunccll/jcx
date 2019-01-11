include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include

PROJ_CXXFLAGS 	+= -g -std=c++0x	#cxx  compile flags
TARGET_LIB_NAME = jcx_thread

PROJ_INC_PATHES 		+= $(GTEST_INC_PATH) \
							$(PROJ_ROOT_SRC_PATH)

PROJ_LIB_PATHES 		+= $(PROJ_ROOT_SRC_PATH)/jcx/base 
PROJ_LIB_PATHES 		+= $(PROJ_ROOT_SRC_PATH)/jcx/logger

PROJ_LIB_FULL_NAMES 	+= $(GTEST_LIB_FULL_NAME)

PROJ_STATIC_LIBS 	+= pthread jcx_base jcx_logger


all: $(TARGET_STATIC_LIB_BIN)

$(TARGET_STATIC_LIB_BIN): $(OBJS)
	$(EO_AR_TARGET)
	$(DO_AR_TARGET)

clean:
	$(EO_AR_CLEAN)
	$(DO_AR_CLEAN)

ut:
	$(EO_CALL_MK_UT)
	$(DO_CALL_MK_UT)

clean.ut:
	$(EO_CALL_MK_UT_CLEAN)
	$(DO_CALL_MK_UT_CLEAN)
