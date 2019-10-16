.PHONY:all
all: client server

clinet:client.c
	gcc -o  $@ $^

server:server.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f server client
