.PHONY:all
all:	client server

client:Client.cc
	g++ -std=c++11 -o $@ $^
server:Server.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f client server
