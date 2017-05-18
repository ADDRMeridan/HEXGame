/*----------------------------------------------
 *Auteur : MOHAMED Mourdas
 *Dêpendance : ensemble
 *Date de modification : 13/05/2017
 *---------------------------------------------*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct et_cellule cellule;

struct et_liste{
	cellule* debut;
	cellule* fin;
};

typedef struct et_liste Liste;

Graphe graphe;

void graphe_initialisation(int n);

int graphe_size();

int graphe_couleur_sommet(int num_case);

int graphe_couleur_hexagone( int row, int colonne );

/* */
bool graphe_sommet_adjacent(int row_1, int col_1, int row_2, int col_2);


/* */
Graphe graphe_ajout_hexagone( int row, int colonne, int couleur);


bool graphe_chaine_gagnante(int couleur);


/* */
void graphe_affiche_row_col_sommet();


void graphe_affichage();


int graphe_distance_hexagones(int col_1, int row_1, int col_2,int row_2);


