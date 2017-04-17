/**************************************************************
* saveload.c - Last modified: 17/04/2017                      * *                                                             *
* Allows saving a Game in a file and loading a Game from file *
*                                                             *
* Mael "ADDRMeridan" MOULIN				      *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void saveGame(char *filename, Game g) {

	//Open file	
	FILE *f = fopen(filename, "wt");
	if(f == NULL) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	//File header
	fputs("\\hex\n", f);
	fprintf(f, "\\dim %d\n", getBoardDim(g));
	fputs("\\board\n", f);
	//Saving board
	for(int i = 0; i < getBoardDim(g); ++i) {
		for(int j = 0; j < getBoardDim(g); ++j) {
			switch(getCell(i, j, g)) {
				case EMPTY:
					fputs(".", f);
					break;
				case BLUE:
					fputs("B", f);
					break;
				case RED:
					fputs("R", f);
					break;
				default:
					fprintf(stderr, "saveGame: Unknowed"
						" Color in board.\n");
					break;
			}
			if(j == getBoardDim(g) - 1) {
				fputs("\n", f);
			} else {
				fputs(" ", f);
			}
		}
	}
	fputs("\\endboard\n", f);

	fputs("\\endhex\n", f);
	fclose(f);
}

//TO REMOVE BEFORE PULLING
int main(int argc, char *argv[]) {

	Game g = createGame(RED, 9);
	Coup cp = createCoup(RED, 5, 5);
	g = addCoupToBoard(cp, g);
	cp = createCoup(BLUE, 0, 0);
	g = addCoupToBoard(cp, g);
	char *filename = "../savegame/game1.txt";
	saveGame(filename, g);
	deleteGame(g);
	return 0;
}
