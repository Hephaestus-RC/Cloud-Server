FLAG=-std=c++11 -lboost_filesystem -lboost_system -I ../../cppjieba/include -ljsoncpp 

.PHONY:all
all:test libSearcher.so

test:test.cc searcher.h searcher.cc 
	g++ -o $@ $^ $(FLAG) 

libSearcher.so:searcher.h searcher.cc 
	g++ -o $@ $^ -shared -fPIC  $(FLAG)

.PHONY:clean
clean:
	rm test libSearcher.so -f
