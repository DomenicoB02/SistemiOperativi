all: main

main: main.o semafori.o
	gcc -o main main.o semafori.o

main.o: main.c semafori.h
	gcc -c main.c -o main.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean:
	rm -f *.o
	r, -f main