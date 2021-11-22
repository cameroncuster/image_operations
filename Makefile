SOURCE_DIR = src

SOURCE = $(SOURCE_DIR)/imageOperations.cpp \
		 $(SOURCE_DIR)/imageFileIO.cpp \
		 $(SOURCE_DIR)/memory.cpp \
		 $(SOURCE_DIR)/main.cpp

INCLUDE_DIR = inc

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O3 -I $(INCLUDE_DIR)
CXXFLAGS = $(CFLAGS)

.PHONY: clean

# Targets include all, clean, debug, tar

all : image_operations

image_operations: $(OBJS)
	$(LINK) -o $@ $^

clean:
	rm -rf $(SOURCE_DIR)/*.o $(SOURCE_DIR)/*.d image_operations

debug: CXXFLAGS = -DDEBUG -Wall -g -I $(INCLUDE_DIR)
debug: image_operations

tar: clean
	tar zcvf image_operations.tgz $(SOURCE) $(INCLUDE_DIR)/*.h Makefile

help:
	@echo " make all   - builds the main target"
	@echo " make       - same as make all"
	@echo " make clean - remove .o .d core main"
	@echo " make debug - make all with -g and -DDEBUG"
	@echo " make tar   - make a tarball of .cpp and .h files"
	@echo " make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@
