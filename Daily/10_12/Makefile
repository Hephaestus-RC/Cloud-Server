.PHONY:all
all: client server pool

pool:ThreadPool.cc
	g++ -o $@ $^ -std=c++11 -plthread
client:Client.cc
	g++ -o $@ $^ -std=c++11 -plthread
server:Server.cc
	g++ -o $@ $^ -std=c++11 -plthread

.PHONY:clean
clean:
	rm -f server client pool
