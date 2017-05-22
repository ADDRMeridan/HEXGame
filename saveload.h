#ifndef SAVELOAD_H
#define SAVELOAD_H

/**************************************************************
* saveload.h - Last modified: 08/05/2017                      * *                                                             *
* Allows saving a Game in a file and loading a Game from file *
*                                                             *
* Mael "ADDRMeridan" MOULIN				      *
**************************************************************/

//Saves a currently existing game
//filename must be <= than 80 characters
void saveGame(char *filename, Game g);

//Loads a saved Game
//filename must be <= than 80 characters
//Returns NULL if something went wrong;
Game loadGame(char *filename);

#endif
