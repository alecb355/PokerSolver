# Define variables
LIB_DIR := ../lib-PokerSolver
OBJ_DIR := obj
SOURCES := $(wildcard $(LIB_DIR)/*.cpp)
OBJECTS := $(patsubst $(LIB_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20
# CXXFLAGS := -fsanitize=address -std=c++20
TARGET := test test_best_hand test_deck test_simulator

# Default target
all: $(TARGET) 

test.o:
	$(CXX) $(CXXFLAGS) -c test.cpp

test_deck.o:
	$(CXX) $(CXXFLAGS) -c test_deck.cpp

test_best_hand.o:
	$(CXX) $(CXXFLAGS) -c test_best_hand.cpp

test_simulator.o:
	$(CXX) $(CXXFLAGS) -c test_simulator.cpp

# Rule to create the executable
test: test.o $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) test.o -o $@
	mv test.o $(OBJ_DIR)

test_best_hand: test_best_hand.o $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) test_best_hand.o -o $@
	mv test_best_hand.o $(OBJ_DIR)

test_deck: test_deck.o $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) test_deck.o -o $@
	mv test_deck.o $(OBJ_DIR)

test_simulator: test_simulator.o $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) test_simulator.o -o $@
	mv test_simulator.o $(OBJ_DIR)


# Rule to create object files in the object directory
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET) test test_best_hand test_deck

# Phony targets
.PHONY: all clean
