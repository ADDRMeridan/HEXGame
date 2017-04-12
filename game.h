#ifndef GAME_H
#define GAME_H

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
void deleteCoup(Coup cp);

//Returns the color of a Coup
Color getCpColor(Coup cp);

//Returns the x Axis value of a Coup
int getCpXAxis(Coup cp);

//Returns the y Axis value of a Coup
int getCpYAxis(Coup cp);

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

Game addCoupToBoard(Coup cp, Game g);

#endif
