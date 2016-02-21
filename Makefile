src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)


CXXFLAGS = -g -Wall -std=c++11
main: $(obj)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) main
