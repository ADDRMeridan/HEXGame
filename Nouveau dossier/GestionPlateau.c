#include "GestionPlateau.h"
Game g;

void initPlateau(char couleur, int taille){
	Color c;
	if(couleur=='x') c=BLUE;
	else c=RED;
	g=createGame(c,taille);
}

void supprPlateau(){
	deleteGame(g);
}

char couleurCellule(int x, int y){
	Color c=getCell(x,y,g);
	if(c==BLUE) return 'x';
	else if(c==RED) return 'o';
	else return '.';
}

void ajoutCoup(char couleur, int x, int y){
	Color c;
	if(couleur=='x') c=BLUE;
	else c=RED;
	Coup coup=createCoup(c,x,y);
	g=addCoupToBoard(coup,g);
}

int nbTour(){
	return getTurn(g);	
}

void annulerDernierCoup(){
	g=undoLastCoup(g);
}

void sauvegardePartie(char* nom){
	saveGame(nom,g);
}

bool contreOrdinateur(){
	return isVsAI(g);
}

bool chargerPartie(char* nom){
	g=loadGame(nom);
	return (g!=NULL);
}

bool dernierCoup(int* x, int* y){
	int nbtour=getTurn(g);
	if(nbtour<1) return false;
	Coup cp=getCoupFromHist(nbtour,g);
	*x=getCpXAxis(cp);
	*y=getCpYAxis(cp);
	return true;
}
