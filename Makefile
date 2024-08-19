# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output binary
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
