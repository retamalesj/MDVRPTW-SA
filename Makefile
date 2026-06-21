ALPHA ?= 10
BETA ?= 10

INITIAL_TEMPERATURE ?= 1000
COOLING_RATE ?= 0.995

MAX_ITERATIONS ?= 1000000
COOLING_INTERVAL ?= 100
MAX_STAGNATION ?= 5000

SEED ?= 42

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = mdvrptw

SRC = src/main.cpp \
      src/Parser.cpp \
      src/InstanceProcessor.cpp \
      src/SA.cpp \
      src/Moves.cpp \
      src/Evaluator.cpp \
      src/SolutionBuilder.cpp \
      src/SolutionUtils.cpp \
      src/Helpers.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

debug: CXXFLAGS += -DDEBUG_MODE
debug: clean $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) \
	$(ALPHA) \
	$(BETA) \
	$(INITIAL_TEMPERATURE) \
	$(COOLING_RATE) \
	$(MAX_ITERATIONS) \
	$(COOLING_INTERVAL) \
	$(MAX_STAGNATION) \
	$(SEED)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all debug run clean