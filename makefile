all: interface.o worker.o
	gcc -o interface interface.o
	gcc -o worker worker.o

interface.o: interface.c
	gcc -c interface.c

worker.o: worker.c
	gcc -c worker.c

clean: 
	rm *.o
	rm interface
	rm worker
