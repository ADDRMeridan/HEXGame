#include "GestionJeu.h"

void nouvellePartie(char couleur, int taille){
	initPlateau(couleur,taille);
	g_initialisation(taille);
}

char couleurCase(int x, int y){
	return couleurCellule(x,y);
}

bool coupValide(int x, int y, char couleur){
	if(couleurCellule(x,y)!='.') return false;
	else{
		int c;
		if(couleur=='x') c=0;
		else c=1;
		ajoutCoup(couleur,x,y);
		g_ajout_hexagone(x-1,y-1,c);
		return true;
	}
}

bool gagnant(char couleur){
	int c;
	if(couleur=='x') c=0;
	else c=1;
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
	g_supprime_hexagone(x-1,y-1);
	return true;
}

bool ContreOrdinateur(){
	return contreOrdinateur();
}

void SauvegarderPartie(char* nom){
	sauvegardePartie(nom);
}

bool ChargerPartie(char* nom){
	if(!chargerPartie(nom)) return false;
	int nbcoup=nbCoup();
	int x;
	int y;
	int couleur;
	if(!g_vide()) g_suppression();
	g_initialisation(getDim());
	for(int i=0; i<nbcoup;i++){
		getCoup(i,&x,&y,&couleur);
		g_ajout_hexagone(x-1,y-1,couleur);
	}
	return true;
}

char ProchainJoueur(){
	int x;
	int y;
	int couleur;
	getCoup(nbCoup()-1,&x,&y,&couleur);
	if(couleur) return 'x';
	else return 'o';
}
