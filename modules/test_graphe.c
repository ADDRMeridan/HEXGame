/*----------------------------------------------
 *module de test du graphe
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 13/05/2017
 *---------------------------------------------*/


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "graphe.h"

int distance_hexa(Graphe graphe, int row_1, int col_1, int row_2, int col_2){

	Hexa p = graphe_hexagone( graphe, row_1, col_1);
	Hexa q = graphe_hexagone( graphe, row_2, col_2);

	return graphe_distance_hexagones( p, q );
}

int couleur_hexagon(Graphe graphe, int row, int colonne){
	int n = graphe_size(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );

	Hexa hexa = graphe_hexagone(graphe, row, colonne);

	return graphe_couleur_sommet( hexa );
}

void test_construction(int n){
	printf("/* Test inite */\n");
	Graphe graphe = graphe_initialisation(n);

	printf("\n/* Test Ajout */\n");
	for(int e=3; e>=0; e--)
		graphe = graphe_ajout_hexagone( graphe, e, 2, NOIR );

	graphe = graphe_ajout_hexagone( graphe, 1, 1, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 1, 0, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 1, 3, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 2, 0, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 3, 1, BLANC );

	printf("\n/* Test Connexion forcer */\n");
	bool FC = graphe_connexion_forcer(graphe_hexagone(graphe , 2, 0), graphe_hexagone(graphe , 3, 1));
	printf("Connexion forcer = %d\n", FC);//doit etre = 1
	
	FC = graphe_connexion_forcer(graphe_hexagone(graphe , 0, 0), graphe_hexagone(graphe , 3, 1));
	printf("Connexion forcer = %d\n", FC);//doit etre = 0

	printf("NOIR  %d\n", graphe_chaine_gagnante(graphe, NOIR) );
	printf("BLANC  %d\n", graphe_chaine_gagnante(graphe, BLANC) );

	graphe_dot( graphe, "g.dot");

	graphe_affichage( graphe);

	graphe_affiche_row_col_sommet( graphe);

	printf("\n/* Test distance sommet */\n");
	printf("distance [3,0] - [2,1] = %d\n", distance_hexa( graphe, 3, 0, 2, 1));
	printf("distance [3,0] - [1,2] = %d\n", distance_hexa( graphe, 3, 0, 1, 2));
	printf("distance [1,0] - [3,3] = %d\n", distance_hexa( graphe, 1, 0, 3, 3));
	printf("distance [1,0] - [2,1] = %d\n", distance_hexa( graphe, 1, 0, 2, 1));
	printf("distance [1,0] - [3,2] = %d\n", distance_hexa( graphe, 1, 0, 3, 2));
}

void test_play(int n){
	/* Jouer */
	printf("/* Jouer */\n");
	Graphe graphe = graphe_initialisation(n);

	int tour = 0;
	int row, col;

	while( !graphe_chaine_gagnante( graphe, BLANC) && !graphe_chaine_gagnante( graphe, NOIR) ){
		printf("ligne : ");
		scanf("%d", &row);
		printf("colonne : ");
		scanf("%d", &col);
		if( tour == 0 ){
			if( couleur_hexagon( graphe,  row-1, col-1) == TRANSPARANT )
				graphe = graphe_ajout_hexagone( graphe, row-1, col-1, NOIR );
			tour = 1;
			printf("Jouer NOIR a jouer\n");
		}
		else{
			if(couleur_hexagon( graphe,  row-1, col-1) == TRANSPARANT)
				graphe = graphe_ajout_hexagone( graphe, row-1, col-1, BLANC );
			tour = 0;
			printf("Jouer BLANC a jouer\n");
		}
		graphe_affiche_row_col_sommet( graphe );
		graphe_affichage( graphe );
		printf("\n");
	}

	if( graphe_chaine_gagnante( graphe, BLANC) )
		printf("BLANC WINNER\n");
	else if( graphe_chaine_gagnante( graphe, NOIR) )
		printf("NOIR WINNER\n");
}

void test_suppression(int n){
	Graphe graphe = graphe_initialisation(n);

	for(int e=3; e>=0; e--)
		graphe = graphe_ajout_hexagone( graphe, e, 2, NOIR );

	graphe = graphe_ajout_hexagone( graphe, 1, 1, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 1, 0, BLANC );
	graphe = graphe_ajout_hexagone( graphe, 1, 3, BLANC );

	graphe_affichage( graphe );

	printf("\nsuppression de l'hexagone [0,2]\n");
	graphe_supprime_hexagone(graphe, 0, 2);
	graphe_affichage( graphe );

	printf("\nsuppression de tout les hexagones \n");
	for(int e=3; e>=0; e--)
		graphe = graphe_supprime_hexagone( graphe, e, 2 );
	printf("---\n");

	graphe = graphe_supprime_hexagone( graphe, 1, 1 );
	graphe = graphe_supprime_hexagone( graphe, 1, 0 );
	graphe = graphe_supprime_hexagone( graphe, 1, 3 );

	graphe_affichage( graphe );
	graphe_suppression( &graphe );

	if( graphe == NULL )
		printf("suppresion graphe [OK]\n");
}

void menu(){
	int choix;
	int taille = 0;

	printf("1:\tTest de construction Graphe.\n");
	printf("2:\tTest jouer humain contre humain.\n");
	printf("3:\tTest suppression d'hexagone et graphe.\n");
	printf("Autre:\tPour quitter.\n");
	printf("Choix ? : ");
	scanf("%d", &choix);

	switch (choix) {
        case 1 :
        	printf("Choisir une taille >= 4 ? : ");
			scanf("%d", &taille);
			if(taille > 3)
				test_construction(taille);
			else
            	test_construction(4);
            break;
        case 2 :
        	printf("Choisir une taille >= 2 ? : ");
			scanf("%d", &taille);
			if(taille > 1)
				test_play(taille);
			else
        		test_play(4);
            break;
        case 3 :
        	test_suppression(4);
        	break;
        default:
        	return;
    }
}

int main(){
	menu();

	return 0;
}