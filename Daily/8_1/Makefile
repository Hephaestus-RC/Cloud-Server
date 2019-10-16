test:sigtest.c
	gcc -o $@ $^

.PHONY:wait
wait:
	gcc -o wait waitCheck.c

.PHONY:clean
clean:
	rm -f test wait
