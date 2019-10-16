.PHONY:all
all: pipe1 pipe2

pipe1:pipe_test1.c
	gcc -o $@ $^

pipe2:pipe_test2.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f pipe1 pipe2
