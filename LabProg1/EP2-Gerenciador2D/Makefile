CC=gcc
CFLAGS=-O2
LDFLAGS=-lglut -lGLU -lGL -lm

EP3-Daniel-Pedro: tInfo.o lista.o gerenciador.o navegacao.o main.o
	$(CC) $(LDFLAGS) $? -o $@

tInfo.o: lista/tInfo.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $? -o $@

lista.o: lista/lista.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $? -o $@

clean:
	rm -rf EP3-Daniel-Pedro *.o
