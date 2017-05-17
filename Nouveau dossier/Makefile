.PHONY: all clean maxclean

CC=gcc
CFLAGS= -Wall -std=c99
LDFLAGS=
EXEC=Jeu
OBJ=main.o GestionPlateau.o game.o saveload.o g.o graphe.o ensemble.o
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

ensemble.o: ensemble.c ensemble.h element_sommet.h
graphe.o: graphe.c graphe.h ensemble.h
g.o: g.c g.h graphe.h ensemble.h
saveload.o: saveload.c saveload.h game.h
game.o: game.c game.h
GestionPlateau.o: GestionPlateau.c GestionPlateau.h game.h saveload.h
GestionJeu.o: GestionJeu.c GestionJeu.h g.h GestionPlateau.h
main.o: main.c GestionJeu.h

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC)
