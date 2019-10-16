.PHONY:all
all:read write


read:read_fifo.c
	gcc -o $@ $^


write:write_fifo.c
	gcc -o $@ $^


.PHONY:clean
clean:
	rm -f read write
