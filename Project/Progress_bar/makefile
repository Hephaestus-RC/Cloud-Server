.PHONY:all
all:bar cbar

bar:p_bar.c
	gcc -o $@ $^

cbar:color_bar.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f bar cbar
