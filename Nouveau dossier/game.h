#ifndef GAME_H
#define GAME_H

/**************************************************************
* game.c - Last modified: 06/05/2017                          * *                                                             *
* Defining types Game, Coup and the headers of functions      *
*                                                             *
* Mael "ADDRMeridan" MOULIN				      *
**************************************************************/

#include <stdbool.h>
#include <stdlib.h>

/***************************/
/********Type Color*********/
/***************************/

//Define a type named Color to represent a Player.
//A player can either be BLUE or RED.
//Empty must only be used for a cell in the board.

enum s_Color {EMPTY, BLUE, RED};
typedef enum s_Color Color;

/***************************/
/*********Type Coup*********/
/***************************/

//Defining Coup
typedef struct s_Coup *Coup;

//Mallocs and return the created Coup
Coup createCoup(Color player, int x, int y);

//Free the memory used by a Coup (destroys it)
//MUST NOT BE USED on a Coup already placed in a game:
//deleteGame will free it. 
void deleteCoup(Coup cp);

//Returns the color of a Coup
Color getCpColor(Coup cp);

//Returns the x Axis value of a Coup
int getCpXAxis(Coup cp);

//Returns the y Axis value of a Coup
int getCpYAxis(Coup cp);

//Prints the Coup info
void printCoup(Coup cp);

/***************************/
/*********Type Game*********/
/***************************/

//Defining Game
typedef struct s_Game *Game;

//Mallocs, initializes all the cells of the board to EMPTY
//and return the created Game
Game createGame(Color firstPlayer, unsigned int boardDim);

//Free the memory used by a Game (destroys it)
void deleteGame(Game g);

//Adds a Coup to the history and board of the Game.
//Doesn't check if Coup is legal
Game addCoupToBoard(Coup cp, Game g);

//Return board dimension
unsigned int getBoardDim(Game g);

//Returns the Game board
Color *getBoard(Game g);

//Return the Color of the cell of coordinates (x, y) 
Color getCell(int x, int y, Game g);

//Return true if the game is against computer, false otherwise
bool isVsAI(Game g);

//Removes the last Coup done in the Game.
//Removes it from the history, the board and frees the memory used by it
Game undoLastCoup(Game g);

//Returns the turn number
unsigned int getTurn(Game g);


//Returns the number of Coup played
unsigned int getNbCoup(Game g);

//Returns the Coup of index i form the Game g history
//PRE: 0 <= i < getTurn(g)
Coup getCoupFromHist(int i, Game g);

#endif
