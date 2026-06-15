ALPHA ?= 100
BETA ?= 100

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = mdvrptw

SRC = main.cpp Parser.cpp ModelBuilder.cpp Evaluator.cpp SolutionBuilder.cpp Helpers.cpp
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