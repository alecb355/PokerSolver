# === Configuration ===
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -Iinclude

# Source, object, and target definitions
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=build/%.o)
TARGET := build/solver

# === Default target ===
all: $(TARGET)

# === Link step ===
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ) -o $@

# === Compile step ===
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Utilities ===
clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
