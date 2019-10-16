.PHONY:all
all: pat mem

pat:someClass.cc
	g++ -std=c++11 -o $@ $^

mem:memory.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f pat mem
