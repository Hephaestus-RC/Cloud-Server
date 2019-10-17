.PHONY:all
all: client server

client:Client.cc
	g++ -o $@ $^
server:Server.cc
	g++ -o $@ $^ -lpthread -std=c++11

.PHONY:clean
clean:
	rm -f server client
