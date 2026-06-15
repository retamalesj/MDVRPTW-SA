ALPHA ?= 100
BETA ?= 100

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = mdvrptw

SRC = src/main.cpp \
      src/Parser.cpp \
      src/InstanceProcessor.cpp \
      src/Evaluator.cpp \
      src/SolutionBuilder.cpp \
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
	./$(TARGET) $(ALPHA) $(BETA)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all debug run clean