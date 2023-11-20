all: main p1 p2 p3

main: main.c
	gcc main.c -o main

p1: p1.c procedure.h procedure.o
	gcc p1.c -o p1 procedure.o

p2: p2.c procedure.h procedure.o
	gcc p2.c -o p2 procedure.o

p3: p3.c procedure.h procedure.o
	gcc p3.c -o p3 procedure.o

procedure.o: procedure.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f p1 p2 p3 main