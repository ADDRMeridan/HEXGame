/*----------------------------------------------
 *Auteur : MOHAMED Mourdas
 *Dêpendance : graphe, ensemble 
 *Date de modification : 15/05/2017
 *---------------------------------------------*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graphe.h"
#include "g.h"
#include "ensemble.h"

Graphe g;

void g_initialisation(int n){
	g = graphe_initialisation(n);
}

int g_size(){
	return graphe_size(g);
}

int g_distance_hexagones(int row_1, int col_1, int row_2, int col_2){
	return graphe_distance_hexagones( graphe_hexagone(g, row_1, col_1),  graphe_hexagone(g, row_2, col_2));
}

void g_ajout_hexagone( int row, int colonne, int couleur){
	g = graphe_ajout_hexagone( g, row, colonne, couleur);
}

int g_couleur_sommet(int row, int col){
	return graphe_couleur_sommet( graphe_hexagone(g, row, col) );
}

bool g_chaine_gagnante( int couleur ){
	return graphe_chaine_gagnante(g, couleur);
}


bool g_sommet_adjacent(int row_1, int col_1, int row_2, int col_2){
	return graphe_sommet_adjacent(graphe_hexagone(g, row_1, col_1),  graphe_hexagone(g, row_2, col_2));
}

void g_affichage(){
	graphe_affichage(g);
}

void g_supprime_hexagone( int row, int col ){
	g = graphe_supprime_hexagone( g,  row, col );
}

void g_suppression(){
	graphe_suppression(&g);
}

bool g_vide(){
	return graphe_vide(g);
}


