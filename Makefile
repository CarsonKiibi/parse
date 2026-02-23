# Compiler
CXX := g++
CXX_STANDARD := -std=c++23

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Flags
CXXFLAGS := $(CXX_STANDARD) -Wall -Wextra -Wpedantic -I$(INC_DIR)
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O3

# Target
TARGET := math_parser

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files (build/*.o)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Dependency files
DEPS := $(OBJS:.o=.d)

# Default build (debug)
all: debug

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR) $(TARGET)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all debug release clean
