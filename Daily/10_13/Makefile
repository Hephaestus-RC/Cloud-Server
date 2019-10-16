.PHONY:all
all:  server client

client:Client.cc
	g++ -o $@ $^ -std=c++11 -lpthread
server:Server.cc
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f server client

