#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "graphe.h"
#include "element_g.h"
#include "ensemble.h"
#include "minimax.h"
#include "file_2.h"

struct node{
	struct node * parent;
	struct node ** fils;
	Graphe config;
	int valeur;
	int nb_fils;
};

typedef struct node Node;

struct minimax{
	Node* root;
};

typedef struct minimax * Minimax;

/*  */
void ligne_cole(int n, int num_case, int *ligne, int *col){
    assert( num_case < (n * n) && num_case >= 0 );
    
    *ligne = num_case / n;
    *col = num_case % n;
}

/*  */
int num_casee(int n, int ligne, int col){
    assert( ligne < n && ligne >= 0 && col < n && col >= 0 );
    
    return n * ligne + col;
}

Minimax inite_minimax(int n){
	Minimax m = (Minimax) malloc( sizeof( struct minimax ) );
	assert(m != NULL);

	m -> root = (Node*) malloc( sizeof( Node ) );
	assert(m -> root != NULL);	

	/* Configuration c0 aucun pion n'a était poser */
	m -> root -> config = inite_graphe(n);
	m -> root -> valeur = 1;
	m -> root -> nb_fils = 0;
	m -> root -> parent = NULL;
	m -> root -> fils = NULL;

	return m;
}

Node* root(Minimax m){
	return m -> root;
}

Graphe config(Node* n){
	return n -> config;
}

int valeur(Node n){
	return n . valeur;
}

int nombre_configuration(Node n){
	return n . nb_fils;
}

Graphe copie_config(Graphe g, Graphe h){
	Hexa sommet_g;
	Hexa sommet_h;
	int col,row;
	int couleur;
	int n = size_graphe(g);
	h = inite_graphe(n);
	
	for(int i=0; i<n*n; i++){
		ligne_cole( n, i, &row, &col);
		sommet_g = hexagone(g, row, col);
		sommet_h = hexagone(h, row, col);

		couleur = couleur_sommet(sommet_g);
		colorie_sommet(sommet_h, couleur);
	}

	return h;
}

Ensemble successeur(Graphe config, int couleur){
	int n;
	int row,col;
	Ensemble ens_g = Vide();
	Graphe aux_g = NULL;

	Hexa sommet;

	if( chaine_gagnante( config, NOIR) || chaine_gagnante( config, BLANC) )
		return ens_g;

	n = size_graphe(config);

	for(int i=0; i<n*n; i++){
		ligne_cole( n, i, &row, &col);
		aux_g = copie_config(config, aux_g);
		sommet = hexagone(aux_g, row, col);

		if(couleur_sommet(sommet) == TRANSPARANT){
			ajout_hexagone(aux_g, row, col, couleur);
			ens_g = Ajout(ens_g, aux_g);
		}
	};

	return ens_g;
}


Node* ajout_successeur(Node* n, Ensemble ensemble, int couleur){
	
	Node* aux = n;
	Element el;
	Node* add;
	int c;

	if( Est_Vide( ensemble ) )
		return n;

	c = cardinal(ensemble);

	aux -> fils = (Node**) malloc( c * sizeof( Node* ) );
	assert(aux -> fils != NULL);

	aux -> nb_fils = c;
	printf("c == %d\n", cardinal(ensemble));

	for(int i=0; i<aux -> nb_fils; i++){

		add = (Node*) malloc( sizeof( Node ) );
		assert(add != NULL);

		add -> nb_fils = 0;
		add -> valeur = 1;
		//printf("cardinal == %d i == %d c==%d\n", cardinal(ensemble), i, c );
		el = element( ensemble, i );
		add -> config = el;

		add -> fils = NULL;
		add -> parent = aux; 

		aux -> fils[i] = add;
		
		if(couleur == NOIR){
			ajout_successeur(add, successeur( add -> config, BLANC), BLANC);
		}
		else{
			ajout_successeur(add, successeur( add -> config, NOIR), NOIR);
		}

		printf("-\n");
		affiche_sommet_hexa_graph(add -> config);
		
		
	}

	return aux;
}

Minimax build(Minimax m, int n){
	m = inite_minimax(n);
	Node * aux = m -> root;
	Ensemble ensemble;

	ensemble = successeur( aux -> config, NOIR);
	ajout_successeur(aux, ensemble, NOIR);

	return m;
}



void triIteratifMinmaxLargeur(Minimax abr){
	File_2 file;
	Node* nodeCour = abr -> root;

	file = initeFile_2();

	/* Enfile la racine */
	enfiler_2(file, nodeCour);

	while( !fileVide_2( file ) ){
		nodeCour = defiler_2(file);

		/* Effectue une action sur le noeud concerner */
		affiche_sommet_hexa_graph(nodeCour -> config);

		/* Enfile le fils gauche et droit si il existe */
		for(int i=0; i<nodeCour -> nb_fils; i++){
			if(nodeCour -> fils[i] != NULL){
				enfiler_2(file, nodeCour -> fils[i]);
			}
		}
		printf("\n");
	}
}