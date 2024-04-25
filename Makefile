CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

run: demo
	./$<

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f demo *.o