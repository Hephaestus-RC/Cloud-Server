FLAG=-std=c++11 -lboost_filesystem -lboost_system -I ../../cppjieba/include -ljsoncpp 

test:test.cc searcher.h searcher.cc 
	g++ -o $@ $^ $(FLAG) 
.PHONY:clean
clean:
	rm test -f
