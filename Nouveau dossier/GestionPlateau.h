/*----------------------------------------------
 *Auteur : LENOIR Matthieu
 *Dêpendance : game, saveload
 *Date de modification : 16/05/2017
 *---------------------------------------------*/
#ifndef GESTION_PLATEAU_H
#define GESTION_PLATEAU_H
#include "game.h"
#include "saveload.h"
#include <stdio.h>
//initialise le plateau de taille taille et ayant comme premier joueur couleur
void initPlateau(char couleur, int taille);
//supprime le plateau
void supprPlateau();
//renvoie la couleur de la cellule de coordonées (x,y)
char couleurCellule(int x, int y);
//ajoute au plateau le coup du joueur couleur aux coordonnées (x,y)
void ajoutCoup(char couleur, int x, int y);
//retourne le nombre de tour 
int nbTour();
//annule le dernier coup
void annulerDernierCoup();
//sauvegarde la partie avec le nom nom
void sauvegardePartie(char* nom);
//charge la partie avec le nom nom et retourne true si il y a bien une partie avec ce nom sinon retourne false;
bool chargerPartie(char* nom);
//renvoie true si il s'agit d'une partie contre l'ordinateur false sinon
bool contreOrdinateur();
//renvoie les coordonnées (x,y) du dernier coup jouer et retourne true si au moin un our à était joué sinon retourne false
bool dernierCoup(int* x, int* y);
//renvoie le nombre de coup joué sur le plateau
int nbCoup();
//retourne les coordonnées (x,y) et la couleur du ième-1 coup
void getCoup(int i,int* x,int* y,int* couleur);
//donne la dimension du plateau
int getDim();
#endif
