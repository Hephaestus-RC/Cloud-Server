.PHONY:all
all:  libmymath,a libmymath.so


libmymath.a:add.o sub.o
	ar -rc $@ $^ -I./lib/include -L./lib/lib -lmymath
libmymath.so:add.o sub.o
	gcc -shared -o $@ $^

add.o:add.c
	gcc -c add.c
sub.o:sub.c
	gcc -c sub.c
mul.o:mul.c
	gcc -fPIC -c mul.c
div.o:div.c
	gcc -fPIC -c div.c

.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp -rf *.h lib/include
	cp -rf *.so lib/lib
	cp -rf *.a lib.lib

.PHONY:clean
clean:
	rm -rf *.o *.a *.so lib
