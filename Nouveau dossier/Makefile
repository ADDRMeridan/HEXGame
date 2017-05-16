.PHONY: all clean maxclean

CC=gcc
CFLAGS= -Wall -std=c99
LDFLAGS=
EXEC=Interface
OBJ=main.o GestionPlateau.o game.o saveload.o
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

saveload.o: saveload.c saveload.h game.h
game.o: game.c game.h
GestionPlateau.o: GestionPlateau.c GestionPlateau.h game.h saveload.h
main.o: main.c GestionPlateau.h

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC)
