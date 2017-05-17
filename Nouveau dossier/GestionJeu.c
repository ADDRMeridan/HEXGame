#include "GestionJeu.h"

void nouvellePartie(char couleur, int taille){
	initPlateau(couleur,taille);
	g_initialisation(taille);
}

char couleurCase(int x, int y){
	return couleurCellule(x, y);
}

bool coupValide(int x, int y, char couleur){
	if(couleurCellule(x,y)!='.') return false;
	else{
		int c;
		if(couleur=='x') c=NOIR;
		else c=BLANC;
		ajoutCoup(couleur,x,y);
		g_ajout_hexagone(x,y,c);
		return true;
	}
}

bool gagnant(char couleur){
	int c;
	if(couleur=='x') c=NOIR;
	else c=BLANC;
	return g_chaine_gagnante(c);
}

void supprPartie(){
	supprPlateau();
	g_suppression();
}

int nbTourPartie(){
	return nbTour();
}

bool annuleCoup(){
	int x;
	int y;
	bool possible=dernierCoup(&x,&y);
	if(!possible) return false;
	annulerDernierCoup();
	g_supprime_hexagone(x,y);
}

bool ContreOrdinateur(){
	contreOrdinateur();
}

void SauvegarderPartie(char* nom){
	sauvegardePartie(nom);
}

bool ChargerPartie(char* nom){
	if(!chargerPartie(nom)) return false;
	return true;
}

