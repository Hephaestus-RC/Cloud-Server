.PHONY:all
all:	p1 p2

p1:port1.c
	gcc -o $@ $^
	
p2:port2.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f p1 p2
