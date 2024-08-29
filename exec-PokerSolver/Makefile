# Define variables
LIB_DIR := ../lib-PokerSolver
OBJ_DIR := obj
SOURCES := $(wildcard $(LIB_DIR)/*.cpp)
OBJECTS := $(patsubst $(LIB_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20
TARGET := solver

# Default target
all: $(TARGET) 

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp
# Rule to create the executable
$(TARGET): main.o $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) main.o -o $@

# Rule to create object files in the object directory
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET) main.o

# Phony targets
.PHONY: all clean
