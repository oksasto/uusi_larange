CC=gcc
CFLAGS=-I.



lagrange:main.c polynomit.o testailu.o
	$(CC) -o lagrange main.c polynomit.c testailu.c

clean:
	rm lagrange
