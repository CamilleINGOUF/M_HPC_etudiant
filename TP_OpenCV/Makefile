
SRC = $(shell ls *.cpp)
BIN = $(SRC:.cpp=.out)

CXXFLAGS = -std=c++11 -Wall -Wextra -O2 `pkg-config --cflags opencv` 
LIBS = -lboost_system -lboost_filesystem `pkg-config --libs opencv`

.PHONY: all clean

all: $(BIN)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean:
	rm $(BIN)

