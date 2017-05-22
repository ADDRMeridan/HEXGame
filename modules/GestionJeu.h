/*----------------------------------------------
 *Auteur : LENOIR Matthieu
 *Dêpendance : GestionPlateau, g
 *Date de modification : 16/05/2017
 *---------------------------------------------*/
#ifndef GESTION_JEU_H
#define GESTION_JEU_H
#include "GestionPlateau.h"
#include "g.h"
//initialise le graphe et le plateau  
void nouvellePartie(char couleur, int taille);
//renvoie la couleur de la case de coordonées (x,y)
char couleurCase(int x, int y);
//ajoute au plateau et au graphe le coup et retourne true si le coup est valide sinon il retourne false
bool coupValide(int x, int y, char couleur);
//retourne true ou false selon si oui ou non il y a le joueur couleur qui a une chaine gagnante
bool gagnant(char couleur);
//supprime la partie courante
void supprPartie();
//retourne le nombre de tour
int nbTourPartie();
//annule le dernier coup et retourne true si c'est possible sinon retourne false
bool annuleCoup();
//retourne true si on joue contre l'odinateur retourne false sinon
bool ContreOrdinateur();
//sauvegarde la partie courante
void SauvegarderPartie(char* nom);
//charge la partie avec le nom nom et retourne true si il y a bien une partie avec ce nom sinon retourne false;
bool ChargerPartie(char* nom);
//renvoie la couleur du prochain joueur
char ProchainJoueur();
#endif
