
SRC = $(shell find . -name "*.cpp")
BIN = $(SRC:.cpp=.out)

all: $(BIN)

%.out: %.cpp
	$(CXX) -std=c++11 -Wall -Wextra -fopenmp -O2 -o $@ $< 

.PHONY: clean

clean:
	rm $(BIN)
