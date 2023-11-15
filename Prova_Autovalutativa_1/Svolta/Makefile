all: master lettore scrittore

master: master.o buffer.o semafori.o
	gcc -o master master.o buffer.o semafori.o

master.o: master.c buffer.h
	gcc -c -o master.o master.c

buffer.o: buffer.c buffer.h
	gcc -c -o buffer.o buffer.c

semafori.o: semafori.c semafori.h
	gcc -c -o semafori.o semafori.c

lettore: lettore.o buffer.o semafori.o
	gcc -o lettore lettore.o buffer.o semafori.o

scrittore: scrittore.o buffer.o semafori.o
	gcc -o scrittore scrittore.o buffer.o semafori.o

lettore.o: lettore.c buffer.h
	gcc -c -o lettore.o lettore.c

scrittore.o: scrittore.c buffer.h
	gcc -c -o scrittore.o scrittore.c

clean:
	rm -f *.o
	rm -f master
	rm -f lettore
	rm -f scrittore
