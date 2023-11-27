programma: main.o prodcons.o monitor_hoare.o
	gcc -o programma  main.o prodcons.o monitor_hoare.o

main.o: main.c prodcons.h
	gcc -c main.c

prodcons.o: prodcons.c prodcons.h monitor_hoare.h
	gcc -c prodcons.c

monitor_hoare.o: monitor_hoare.c monitor_hoare.h
	gcc -c monitor_hoare.c
      
clean:
	rm -f *.o
	rm -f programma
