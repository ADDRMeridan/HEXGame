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

//TO REMOVE BEFORE SHARING
int main(int argc, char *argv[]) {

	return 0;
}
