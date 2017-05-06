/**************************************************************
* saveload.c - Last modified: 06/05/2017                      * *                                                             *
* Allows saving a Game in a file and loading a Game from file *
*                                                             *
* Mael "ADDRMeridan" MOULIN				      *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "game.h"

void saveGame(char *filename, Game g) {

	mkdir("../savegame", S_IRWXU);
	//Open file
	FILE *f = fopen(strcat("../savegame/",filename), "wt"); //SEGMENTATION FAULT HERE
	if(f == NULL) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	//File header
	fprintf(f, "\\hex\n");
	fprintf(f, "\\dim %d\n", getBoardDim(g));
	fprintf(f, "\\board\n");
	//Saving board
	for(int i = 0; i < getBoardDim(g); ++i) {
		for(int j = 0; j < getBoardDim(g); ++j) {
			switch(getCell(i, j, g)) {
				case EMPTY:
					fprintf(f, ".");
					break;
				case BLUE:
					fprintf(f, "B");
					break;
				case RED:
					fprintf(f, "R");
					break;
				default:
					fprintf(stderr, "saveGame: Unknowed"
						" Color in board.\n");
					exit(EXIT_FAILURE);
			}
			if(j == getBoardDim(g) - 1) {
				fprintf(f, "\n");
			} else {
				fprintf(f, " ");
			}
		}
	}
	fprintf(f, "\\endboard\n");
	fprintf(f, "\\game\n");
	for(int i = 0; i < getNbCoup(g); ++i) {
		Coup cp = getCoupFromHist(i, g);
		fprintf(f, "\\play ");
		switch(getCpColor(cp)) {
			case EMPTY:
				fprintf(f, ".");
				break;
			case BLUE:
				fprintf(f, "B");
				break;
			case RED:
				fprintf(f, "R");
				break;
			default:
				fprintf(stderr, "saveGame: Unknowed"
					" Color in board.\n");
				exit(EXIT_FAILURE);
		}
		fprintf(f, " %d %d\n", getCpXAxis(cp), getCpYAxis(cp));
	}
	fprintf(f, "\\endgame\n");
	fprintf(f, "\\endhex\n");
	fclose(f);
}

//TO REMOVE BEFORE PULLING
int main(int argc, char *argv[]) {

	Game g = createGame(RED, 9);
	Coup cp = createCoup(RED, 5, 5);
	g = addCoupToBoard(cp, g);
	cp = createCoup(BLUE, 0, 0);
	g = addCoupToBoard(cp, g);
	char *filename = "game1.txt";
	saveGame(filename, g);
	deleteGame(g);
	return 0;
}
