/**************************************************************
* saveload.c - Last modified: 08/05/2017                      * *                                                             *
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
#include "saveload.h"

void saveGame(char *filename, Game g) {

	mkdir("../savegame", S_IRWXU);
	//making path name
	char path[97];	//filename <= 80 char
	strcpy(path, "../savegame/");
	strcat(path, filename);
	strcat(path, ".txt");
	//Open file
	FILE *f = fopen(path, "wt");
	if(f == NULL) {
		perror(path);
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
	//Saving History
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

//Returns NULL if something's wrong
static Coup loadCoup(char *line) {

	Coup cp;
	char *wrd = NULL;	
	wrd = strtok(line, " ");
	if(strcmp(wrd, "\\play")) {
		return NULL;
	} else {
		//Get color
		wrd = strtok(NULL, " ");
		Color tmpC;
		switch(wrd[0]) {
			case 'R':
				tmpC = RED;
				break;
			case 'B':
				tmpC = BLUE;
				break;
			default:
				return NULL;
		}
		//Get X Axis
		wrd = strtok(NULL, " ");
		if(wrd == NULL) {
			return NULL;
		}
		int tmpX = strtol(wrd, NULL, 10);
		//Get Y Axis
		wrd = strtok(NULL, " ");
		if(wrd == NULL) {
			return NULL;
		}
		int tmpY = strtol(wrd, NULL, 10);
		//Create Coup
		cp = createCoup(tmpC, tmpX, tmpY);	
	}
	return cp;
}

Game loadGame(char *filename) {

	//making path name
	char path[97];	//filename <= 80 char
	strcpy(path, "../savegame/");
	strcat(path, filename);
	strcat(path, ".txt");
	//Open File
	FILE *f = fopen(path, "rt");
	if(f == NULL) {
		perror(path);
		return NULL;
	}
	//Init readline
	char *line = NULL;
	size_t len = 0;
	ssize_t nbChar;
	//Check if hex
	nbChar = getline(&line, &len, f);
	if(nbChar == -1 || strcmp(line, "\\hex\n")) {
		fprintf(stderr, "loadGame: Wrong file type.\n");
		return NULL;
	}
	//Get dimension
	nbChar = getdelim(&line, &len, ' ', f);
	if(nbChar == -1 || strcmp(line, "\\dim ")) {
		fprintf(stderr, "loadGame: corrupted save.\n");
		return NULL;
	}
	int tmp;
	fscanf(f, "%d", &tmp);
	if(tmp < 2) {
		fprintf(stderr, "loadGame: board size too small.\n");
		return NULL;
	}
	nbChar = getline(&line, &len, f); //Flush '\n'
	//Check board
	nbChar = getline(&line, &len, f);
	if(nbChar == -1 || strcmp(line, "\\board\n")) {
		printf("Here\n");
		fprintf(stderr, "loadGame: corrupted save.\n");
		return NULL;
	}
	//Skipping board representation
	for(int i = 0; i < tmp; ++i) {
		nbChar = getline(&line, &len, f);
	}
	//Checking end board
	nbChar = getline(&line, &len, f);
	if(nbChar == -1 || strcmp(line, "\\endboard\n")) {
		fprintf(stderr, "loadGame: corrupted save.\n");
		return NULL;
	}
	//Check history
	nbChar = getline(&line, &len, f);
	if(nbChar == -1 || strcmp(line, "\\game\n")) {
		fprintf(stderr, "loadGame: corrupted save.\n");
		return NULL;
	}
	Game g = createGame(EMPTY, tmp);
	//EMPTY is changed when the first Coup is added
	nbChar = getline(&line, &len, f);
	while(nbChar != -1 && strcmp(line, "\\endgame\n")) {
		Coup cp = loadCoup(line);
		if(cp == NULL) {
			nbChar = -1;
		} else {
			g = addCoupToBoard(cp, g);
			nbChar = getline(&line, &len, f);
		}
	}
	if(nbChar == -1 || strcmp(line, "\\endgame\n")) {
		fprintf(stderr, "loadGame: corrupted save.\n");
		deleteGame(g);
		return NULL;
	}
	//Check end of hex
	nbChar = getline(&line, &len, f);
	if(nbChar == -1 || strcmp(line, "\\endhex\n")) {
		fprintf(stderr, "loadGame: corrupted save.\n");
		deleteGame(g);
		return NULL;
	}
	fclose(f);
	return g;
}
