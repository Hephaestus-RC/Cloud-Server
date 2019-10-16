.PHONY:all
all: server client


client:Client.cc
	g++ -o $@ $^
server:Server.cc
	g++  -o $@ $^

.PHONY:clean
clean:
	rm -f client server
