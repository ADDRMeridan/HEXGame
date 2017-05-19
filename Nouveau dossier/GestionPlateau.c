#include "GestionPlateau.h"
Game ga;

void initPlateau(char couleur, int taille){
	Color c;
	if(couleur=='x') c=BLUE;
	else c=RED;
	ga=createGame(c,taille);
}

void supprPlateau(){
	deleteGame(ga);
}

char couleurCellule(int x, int y){
	Color c=getCell(x,y,ga);
	if(c==BLUE) return 'x';
	else if(c==RED) return 'o';
	else return '.';
}

void ajoutCoup(char couleur, int x, int y){
	Color c;
	if(couleur=='x') c=BLUE;
	else c=RED;
	Coup coup=createCoup(c,x,y);
	ga=addCoupToBoard(coup,ga);
}

int nbTour(){
	return getTurn(ga);	
}

void annulerDernierCoup(){
	ga=undoLastCoup(ga);
}

void sauvegardePartie(char* nom){
	saveGame(nom,ga);
}

bool contreOrdinateur(){
	return isVsAI(ga);
}

bool chargerPartie(char* nom){
	ga=loadGame(nom);
	return (ga!=NULL);
}

bool dernierCoup(int* x, int* y){
	int nbcoup=getNbCoup(ga);
	if(nbcoup<1) return false;
	Coup cp=getCoupFromHist(nbcoup-1,ga);
	*x=getCpXAxis(cp);
	*y=getCpYAxis(cp);
	return true;
}

int nbCoup(){
	return getNbCoup(ga);
}

void getCoup(int i,int* x,int* y,int* couleur){
	Coup cp=getCoupFromHist(i,ga);
	*x=getCpXAxis(cp);
	*y=getCpYAxis(cp);
	if(couleurCellule(*x,*y)=='x') *couleur=0;
	else *couleur=1;
}

int getDim(){
	return getBoardDim(ga);
}
