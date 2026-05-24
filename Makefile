# Compiler settings
CXX      := clang++
# Added -I/usr/include/SDL3 so it finds the headers
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -I/usr/include/SDL3

# Linker settings
# Directly link against the lowercase sdl3 library
LDFLAGS  := -lSDL3


# Directory structures
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# Target executable
TARGET   := $(BIN_DIR)/main

# Automatically find all .cpp, .cc, or .cxx files in src/
SRCS     := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.cc) $(wildcard $(SRC_DIR)/*.cxx)
# Map source files to object files in the obj/ directory
OBJS     := $(SRCS:$(SRC_DIR)/%=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link rule
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compilation rule for source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/% | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they do not exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
