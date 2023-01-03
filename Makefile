all: darts

darts: darts.c darts.h
	gcc -O -Wall -o darts darts.c -lncurses

clean:
	rm -f darts

distclean: clean
