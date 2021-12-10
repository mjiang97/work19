all: work18.o
	gcc -o program work18.o

work18.o: work18.c
	gcc -c work18.c

run:
	./program

clean: 
	rm *.o
	rm program