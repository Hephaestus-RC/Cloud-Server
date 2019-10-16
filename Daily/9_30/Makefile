.PHONY:all
all:client server

client:Client.cc
	g++ -o $@ $^ -std=c++11
server:Server.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f client server

