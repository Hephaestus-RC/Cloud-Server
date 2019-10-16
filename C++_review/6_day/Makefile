.PHONY:all
all:io mem

io:in_out.cc
	g++ -std=c++11 -o $@ $^
mem:memory.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f mem io
