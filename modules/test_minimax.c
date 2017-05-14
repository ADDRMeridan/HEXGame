#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "minimax.h"
#include "ensemble.h"

void copie_graphe(Graphe g, Graphe h, int couleur_ajout){
	Hexa sommet_g;
	Hexa sommet_h;
	int col,row;
	int couleur;
	int n = graphe_size(g);
	bool ajout_ok = false;

	assert( n == graphe_size(h) );
	
	for(int i=0; i<n*n && !ajout_ok; i++){
		minimax_ligne_colonne( n, i, &row, &col);
		sommet_g = graphe_hexagone(g, row, col);
		sommet_h = graphe_hexagone(h, row, col);

		couleur = graphe_couleur_sommet(sommet_g);
		if(couleur != graphe_couleur_sommet(sommet_h) ){
			graphe_ajout_hexagone(h, row, col, couleur_ajout);
			ajout_ok = true;
		}
	}
}

void ia_play(Graphe g, Minimax m, int nb_coup, int couleur){

	Node * n = minimax_search_graphe(m, g, nb_coup);

	Graphe grahe_a_jouer;
	int valeur_gagnante;
	assert( n != NULL );

	if( couleur == NOIR )
		valeur_gagnante = 1;
	else
		valeur_gagnante = -1;

	grahe_a_jouer = minimax_search_config_gagnant( n, valeur_gagnante);

	copie_graphe(grahe_a_jouer, g, couleur);
}

void test_construction(int n){
	Minimax m = minimax_initialisation(n);
	m = minimax_build(m, n);
	printf("------------------------\n\n");
	minimax_tri_iteratif_largeur(m);
	
	char name[10];
	sprintf(name, "min.dot");

    FILE * file = NULL;
    file = fopen(name, "w");

    printf("Creation du fichier %s en cours...\n", name);

    if( file == NULL ){
        printf("Erreur D'ouverture du fichier \n");
        exit(1);
    }

    minimax_export_dot(minimax_root(m), file);

    printf("Creation du fichier %s realiser avec succes !!\n", name);

    fclose(file);
}

void test_ia_minimax(int n){
	
    /* IA minimax */
    int row,col;
    bool ok;
    Hexa hex;

    int tour=0;
    int nb_tour = 0;

    Minimax m = minimax_initialisation(n);
	Graphe g = graphe_initialisation(2);
    
	m = minimax_build(m, n);

    while( !graphe_chaine_gagnante(g, BLANC) && !graphe_chaine_gagnante(g, NOIR) ){
    	if(tour == 1){
    		printf("A vous de jouer\n");
	    	ok = false;
	    	while( !ok ){
		    	printf("ligne : ");
		    	scanf("%d",&row);
		    	printf("colonne : ");
		    	scanf("%d",&col);

		    	if( row-1 >= 0 && row-1 < n && col-1 >= 0 && col-1 < n ){
			    	hex = graphe_hexagone(g, row-1, col-1);

			    	if( graphe_couleur_sommet(hex) == TRANSPARANT ){
			    		ok = true;
			    	}
			    }
		    }
		   
	    	graphe_ajout_hexagone(g, row-1, col-1, BLANC);
	    	tour = 0;
	    }
	    else{
	    	printf("L'IA joue\n");
	    	ia_play(g, m, nb_tour, NOIR);
	    	tour = 1;
	    }

		graphe_affichage(g);
		nb_tour++;
    }

    if( graphe_chaine_gagnante(g, BLANC) )
    	printf("Vous avez gagné !!\n");
    else if( graphe_chaine_gagnante(g, NOIR) )
    	printf("L'IA vous a battu, c'est normal avec l'algo minimax, et le fait qu'il \nsoit le 1er a jouer vous n'aviez aucune chance :P.\n");

}

void menu(){
	int choix;

	printf("1:\tTest de construction minimax\n");
	printf("2:\tTest jouer contre IA avec minimax\n");
	printf("Autre:\tPour quitter\n");
	printf("Choix ? : ");
	scanf("%d", &choix);

	switch (choix) {
        case 1 :
            test_construction(2);
            break;
        case 2 :
        	test_ia_minimax(2);
            break;
        default:
        	return;
    }
}

void usage(const char *command) {
    printf("usage : %s -id num\n", command);
    printf("ou id est :\n");
    printf("\tc : construit un arbre minimax, dont les configuration son de taille num, et cree un fichier min.dot de cette arbre\n");
    printf("\ti : lance une partie machine contre humain, avec la machine qui utilise l'abre minimax pour trouvé la meilleur solution\n");
    printf("ou num est la taille du graphe\n");
}

int main(int argc, const char *argv[]){

	if( argc < 2 )
		menu();
	else if( argc == 3 ){
		switch (argv[1][1]) {
	        case 'c' :
	            test_construction(atoi(argv[2]));
	            break;
	        case 'i' :
	            test_ia_minimax(atoi(argv[2]));
	            break;
	        default :
	            usage(argv[0]);
	            return 1;
	    }
	}
	else{
		usage(argv[0]);
	}

	return 0;
}



