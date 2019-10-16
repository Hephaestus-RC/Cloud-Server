libmymath.so:div.o mul.o
	gcc -shared -o $@ $^

div.o:div.c
	gcc -fPIC -c div.c
mul.o:mul.c
	gcc -fPIC -c mul.c -o mul.o

.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp -rf *.h ./lib/include
	cp -rf *.so ./lib/lib

.PHONY:clean
clean:
	rm -rf *.o *.so lib
