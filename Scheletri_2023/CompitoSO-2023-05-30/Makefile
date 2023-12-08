all: start

start: start.o worker.o monitor_signal_continue.o
	gcc -o start start.o worker.o monitor_signal_continue.o

start.o: start.c
	gcc -c -o start.o start.c

worker.o: worker.c worker.h
	gcc -c -o worker.o worker.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c -o monitor_signal_continue.o monitor_signal_continue.c

clean:
	rm -f *.o
	rm -f start