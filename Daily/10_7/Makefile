.PHONY:all
all: server client

client:Client.cc
	g++ -o $@ $^ -std=c++11
server:Server.cc
	g++ -o $@ $^ -std=c++11

.PHONYL:clean
clean:
	rm -f server client
