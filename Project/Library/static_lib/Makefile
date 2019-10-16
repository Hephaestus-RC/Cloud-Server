libmymath.a:add.o sub.o
	ar -rc $@ $^

add.o:add.c
	gcc -c add.c -o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o

.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp *.a ./lib/lib
	cp *.h ./lib/include

.PHONY:clean
clean:
	rm -rf *.o *.a lib 

