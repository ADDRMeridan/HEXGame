.PHONY: all clean maxclean 

CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm
EXEC = main
OBJ = graphe.o file.o ensemble.o GestionJeu.o g.o game.o saveload.o 

chemin="E:\Programmes\Java32\jdk1.8.0_131\include"
chemin2="E:\Programmes\Java32\jdk1.8.0_131\include\win32"
nom="JavaGestionJeu"

linux:	$(OBJ)	
	gcc -I$chemin -I$chemin2 gcc -shared -o "lib$nom".so $nom.o

## Windows/gcc 
windows:
	gcc -c -I $(chemin) -I $(chemin2) -o $(nom).o test.c
	gcc -shared -o $(nom).dll $(nom).c $(nom).c $(nom).def

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf *.exe
