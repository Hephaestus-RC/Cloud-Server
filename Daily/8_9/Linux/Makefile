.PHONY:all
all: shell copy

shell:shell.c
	gcc -o $@ $^

copy:in_copy_out.c
	gcc -o $@ $^
	
.PHONY:clean
clean:
	rm -f shell copy
