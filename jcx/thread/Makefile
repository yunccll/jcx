include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include

PROJ_CXXFLAGS 	+=
TARGET_LIB_NAME = jcx_thread

PROJ_INC_PATHES 		+= $(PROJ_ROOT_SRC_PATH)
PROJ_LIB_PATHES 		+= $(PROJ_ROOT_SRC_PATH)/jcx/base 
PROJ_LIB_FULL_NAMES 	+= 
PROJ_STATIC_LIBS 	+= jcx_base


all: $(TARGET_STATIC_LIB_BIN)

$(TARGET_STATIC_LIB_BIN): $(OBJS)
	$(EO_AR_TARGET)
	$(DO_AR_TARGET)

clean:
	$(EO_AR_CLEAN)
	$(DO_AR_CLEAN)
