.PHONY:all
all:server client

server:Server.cc
	g++ -o $@ $^
client:Client.cc

ss:SpecialSymbol.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f ss server client
