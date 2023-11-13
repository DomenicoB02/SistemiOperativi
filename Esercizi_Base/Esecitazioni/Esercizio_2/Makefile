main: main.o processi.o semafori.o
	gcc -o main main.o processi.o semafori.o

main.o: main.c
	gcc -c -g -o main.o main.c

processi.o: processi.c
	gcc -c -g -o processi.o processi.c
	
semafori.o: semafori.c
	gcc -c -g -o semafori.o semafori.c

clean:
	rm -f *.o
	rm -f main