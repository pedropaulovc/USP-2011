all: ep1
ep1: tInfo.o pilha.o matriz.o main.o
	gcc -O2 -o EP1-PedroPaulo main.o pilha.o matriz.o tInfo.o
tInfo.o: tInfo.c tInfo.h
	gcc -O2 -o tInfo.o -c tInfo.c -W -Wall -ansi -pedantic
pilha.o: pilha.c pilha.h tInfo.h
	gcc -O2 -o pilha.o -c pilha.c -W -Wall -ansi -pedantic
matriz.o: matriz.c matriz.h
	gcc -O2 -o matriz.o -c matriz.c -W -Wall -ansi -pedantic
main.o: main.c main.h matriz.h pilha.h
	gcc -O2 -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o EP1-PedroPaulo
