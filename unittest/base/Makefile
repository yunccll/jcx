include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include

PROJ_INC_PATHES 	+= $(GTEST_INC_PATH) \
					$(PROJ_ROOT_SRC_PATH)
PROJ_LIB_PATHES 	+=
PROJ_LIB_FULL_NAMES += $(GTEST_LIB_FULL_NAME)

PROJ_STATIC_LIBS 	+= pthread

UT_DEST_EXCLUDE_OBJS 	+= ../main.o
CXX_OBJS  				+= $(UT_DEST_OBJS)

all: $(UT_TARGET_BIN)

$(UT_TARGET_BIN): $(OBJS)
	$(EO_CPP_TARGET)
	$(DO_CPP_TARGET)

clean: clean.log
	$(EO_UT_CLEAN)
	$(DO_UT_CLEAN)

clean.log:
	$(EO_CLEAN_LOG)	
	$(DO_CLEAN_LOG)	
