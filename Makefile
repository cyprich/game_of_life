# compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# directories
SRC_DIR := src
BUILD_DIR := build

# find all .cpp files in the source directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# default target (runs the program)
run: $(BUILD_DIR)/main
	@echo "Running..."
	@echo ""
	@./$(BUILD_DIR)/main

# run the program
$(BUILD_DIR)/main: $(SRCS)
	@echo "Compiling..."
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $@

# clean the build directory
clear:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)
	@echo "All clear!"
