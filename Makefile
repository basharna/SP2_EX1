CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: demo test

run: demo
	./$<

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean run

clean:
	rm -f demo *.o test