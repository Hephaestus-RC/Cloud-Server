.PHONY:all
all:server client

server:Server.cc
	g++ -o $@ $^ 
client:Client.cc
	g++ -o $@ $^

.PHONY:pool
pool:ThreadPool.hpp
	g++ -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f pool server client
