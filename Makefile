
all:
	gcc -Wall -O2 -o matrix.out matrix.c

clean:
	rm -f *.o
	rm -f *.out

