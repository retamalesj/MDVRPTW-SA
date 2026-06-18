ALPHA ?= 10
BETA ?= 10
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
	./$(TARGET) $(ALPHA) $(BETA) $(SEED)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all debug run clean