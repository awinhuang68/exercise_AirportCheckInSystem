# Makefile for Airport Check-In System
# C++17 Project for MSYS2/MinGW

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDE_DIR = include
LIB_DIR = lib
SRC_DIR = src
OUTPUT_DIR = output
INTERMEDIATE_DIR = intermediate

# Target executable
TARGET = $(OUTPUT_DIR)/AirportCheckInSystem.exe

# Find all source files in src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file names from source files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(INTERMEDIATE_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(INTERMEDIATE_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INTERMEDIATE_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Create output directory if it doesn't exist
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Create intermediate directory if it doesn't exist
$(INTERMEDIATE_DIR):
	mkdir -p $(INTERMEDIATE_DIR)

# Clean build artifacts
clean:
	rm -rf $(INTERMEDIATE_DIR)/*.o $(TARGET)

# Clean everything including executable
clean-all:
	rm -rf $(INTERMEDIATE_DIR) $(OUTPUT_DIR)

# Run the executable
run: $(TARGET)
	$(TARGET)

.PHONY: all clean clean-all run
