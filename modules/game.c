/**************************************************************
* game.c - Last modified: 15/04/2017                          * *                                                             *
* Defining struct Game, Coup and functions around those types *
*                                                             *
* Mael "ADDRMeridan" MOULIN				      *
**************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"

/***************************/
/*********Type Coup*********/
/***************************/

//Represents the action that a player wants/has performed

struct s_Coup {
	
	Color c;
	int x;
	int y;
};

Coup createCoup(Color player, int x, int y) {

	//Request memory
	Coup cp = malloc(sizeof(struct s_Coup));
	//Check pointer	
	if(cp == NULL) {
		fprintf(stderr, "createCoup: malloc returned null pointer.\n");
		exit(EXIT_FAILURE);
	}
	//Set c parameters
	cp->c = player;
	cp->x = x;
	cp->y = y;

	return cp;
}

void deleteCoup(Coup cp) {

	free(cp);
}

Color getCpColor(Coup cp) {

	return cp->c;
}

int getCpXAxis(Coup cp) {

	return cp->x;
}

int getCpYAxis(Coup cp) {

	return cp->y;
}

/***************************/
/*********Type Game*********/
/***************************/

struct s_Game{

	unsigned int dim;	//Board dimension
	Color nextP;		//Next player Color(Can be BLUE or RED)
	bool vsAI;		//False by default / True = against computer
	unsigned int nbCoup;	//Store the number of Coup played
	Color *board;		//Board of the game
	Coup *hist;		//History of the game
};

//Fills a board of a Game with EMPTY cell
//Returns the modified Game
static Game fillBoardWithEMPTY(Game g) {
	
	unsigned int nbCell = g->dim * g->dim;
	for(int i = 0; i < nbCell; ++i) {
		g->board[i] = EMPTY;
	}
	return g;
}

Game createGame(Color firstPlayer, unsigned int boardDim) {

	//Request Memory
	Game g = malloc(sizeof(struct s_Game));
	//Check pointer
	if(g == NULL) {
		fprintf(stderr, "createGame: malloc returned"
			" null for Game.\n");
		exit(EXIT_FAILURE);
	}

	//Set game parameters
	g->dim = boardDim;
	g->nextP = firstPlayer;
	g->vsAI = false;
	g->nbCoup = 0;

	//Malloc Board Size
	unsigned int nbCell = boardDim * boardDim;
	g->board = malloc(sizeof(Color) * nbCell);
	//Checking board pointer
	if(g->board == NULL) {
		fprintf(stderr, "createGame: malloc returned"
			" null for Board.\n");
		exit(EXIT_FAILURE);
	}
	//Filling board with EMPTY cell
	g = fillBoardWithEMPTY(g);
	
	//Malloc History Size
	g->hist = malloc(sizeof(struct s_Coup) * nbCell);
	//Checking hist pointer
	if(g->hist == NULL) {
		fprintf(stderr, "createGame: malloc returned"
			" null for History.\n");
		exit(EXIT_FAILURE);
	}

	return g;
}

//Frees the memory used by a Game history
static void deleteHistory(Game g) {

	for(int i = 0; i < g->nbCoup; ++i) {
		deleteCoup(g->hist[i]);
	}
	free(g->hist);
}

void deleteGame(Game g) {

	//Free History
	deleteHistory(g);
	//Free Board
	free(g->board);
	//Free Game
	free(g);
}

//Saves the Coup in the Game history
static Game addCoupToHist(Coup cp, Game g) {

	g->hist[g->nbCoup] = cp;
	return g;
}

//Based on the dimension of the board, returns a 2 axis representation
//of the board to one.
static int doubleAxisToUnique(int x, int y, unsigned int dim) {

	return ((x * dim) + y);
}

Game addCoupToBoard(Coup cp, Game g) {

	//Add Color to board
	g->board[doubleAxisToUnique(cp->x, cp->y, g->dim)] = cp->c;
	//Add Coup to History
	g = addCoupToHist(cp, g);
	//Increment nbCoup
	++g->nbCoup;
	//Swap the next Player
	if(cp->c == RED) {
		g->nextP = BLUE;
	} else if(cp->c == BLUE) {
		g->nextP = RED;
	}
	return g;
}

unsigned int getBoardDim(Game g) {

	return g->dim;
}

Color *getBoard(Game g) {

	return g->board;
}

Color getCell(int x, int y, Game g) {

	return g->board[doubleAxisToUnique(x, y, g->dim)];
}

bool isVsAI(Game g) {

	return g->vsAI;
}

Game undoLastCoup(Game g) {

	//Get last Coup played
	Coup cp = g->hist[g->nbCoup - 1];
	//Set cell of last Coup to Empty
	g->board[doubleAxisToUnique(cp->x, cp->y, g->dim)] = EMPTY;
	//Free Coup memory
	deleteCoup(cp);
	//Decreament nbCoup
	--g->nbCoup;
	
	return g;
}

unsigned int getTurn(Game g) {

	return (g->nbCoup / 2) + 1;
}

Coup getCoupFromHist(int i, Game g) {

	return (g->hist[i]);
}
