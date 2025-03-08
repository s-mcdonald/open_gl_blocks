TRG_DIR = ./bin
SRC_DIR = ./src
LIB_DIR = ../../vendor
INC_DIR = ../../includes

#
# BUILD_MODE
# 
# Available options are DEBUG, RELEASE
#
BUILD_MODE = DEBUG 

CXX = g++
CXXFLAGS = -Wall -std=c++20

TARGET = $(TRG_DIR)/blocks

#
# Src files
#
SRC = $(SRC_DIR)/blocks.cpp 

#
# Link against libs
#
LIBS = -lGL 
LIBS += -lGLU 
LIBS += -lglut


all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	@echo ""
	@echo Build complete "blocks" \;\)
	@echo ""
clean:
	rm -f $(TARGET) $(OBJS) $(TRG_PKG)