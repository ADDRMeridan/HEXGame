/*----------------------------------------------
 *Auteur : MOHAMED Mourdas
 *Dêpendance : ensemble, element_g, file2,
 	graphe
 *Date de modification : 14/05/2017
 *---------------------------------------------*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "graphe.h"
#include "element_graphe.h"
#include "element_sommet.h"
#include "file.h"
#include "minimax.h"


struct node{
	struct node * parent;
	struct node ** fils;
	Graphe minimax_config;
	int couleur;
	int minimax_valeur;
	int nb_fils;

	/* Pour amelioré la complexité lors de la Recherche de la meilleur minimax_config */
	int etage;
};

typedef struct node Node;

struct minimax{
	Node* minimax_root;
};

typedef struct minimax * Minimax;

/*  */
void minimax_ligne_colonne(int n, int graphe_num_case, int *ligne, int *col){
    assert( graphe_num_case < (n * n) && graphe_num_case >= 0 );
    
    *ligne = graphe_num_case / n;
    *col = graphe_num_case % n;
}

/*  */
int minimax_num_case(int n, int ligne, int col){
    assert( ligne < n && ligne >= 0 && col < n && col >= 0 );
    
    return n * ligne + col;
}

Minimax minimax_initialisation(int n){
	Minimax m = (Minimax) malloc( sizeof( struct minimax ) );
	assert(m != NULL);

	m -> minimax_root = (Node*) malloc( sizeof( Node ) );
	assert(m -> minimax_root != NULL);	

	/* Configuration c0 aucun pion n'a était poser */
	m -> minimax_root -> minimax_config = graphe_initialisation(n);
	m -> minimax_root -> minimax_valeur = 1;
	m -> minimax_root -> nb_fils = 0;
	m -> minimax_root -> couleur = TRANSPARANT;
	m -> minimax_root -> etage = 0;
	m -> minimax_root -> parent = NULL;
	m -> minimax_root -> fils = NULL;

	return m;
}

Node* minimax_root(Minimax m){
	return m -> minimax_root;
}

Graphe minimax_config(Node* n){
	return n -> minimax_config;
}

int minimax_valeur(Node n){
	return n . minimax_valeur;
}

int minimax_nombre_fils(Node n){
	return n . nb_fils;
}

Graphe minimax_copie_config(Graphe g){
	Graphe h;
	Hexa sommet_g;
	int col,row;
	int couleur;
	int n = graphe_size(g);
	h = graphe_initialisation(n);
	
	for(int i=0; i<n*n; i++){
		minimax_ligne_colonne( n, i, &row, &col);
		sommet_g = graphe_hexagone(g, row, col);

		couleur = graphe_couleur_sommet(sommet_g);
		if(couleur != TRANSPARANT)
			graphe_ajout_hexagone(h, row, col, couleur);
	}

	return h;
}

/**
 *	@brief une fonction minimax_successeur qui associe à chaque 
 		conﬁguration de jeu, l’ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 *	@param minimax_config : une configaration (graphe).
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *  @return Ensemble : un ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 */
Ensemble minimax_successeur(Graphe minimax_config, int couleur){
	int n;
	int row,col;
	Ensemble ens_g = Vide();
	Graphe aux_g = NULL;

	Hexa sommet;

	if( graphe_chaine_gagnante( minimax_config, NOIR ) || graphe_chaine_gagnante( minimax_config, BLANC ) )
		return ens_g;

	n = graphe_size(minimax_config);

	for(int i=0; i<n*n; i++){
		minimax_ligne_colonne( n, i, &row, &col);
		aux_g = minimax_copie_config(minimax_config);
		sommet = graphe_hexagone(aux_g, row, col);

		if(graphe_couleur_sommet(sommet) == TRANSPARANT){
			graphe_ajout_hexagone(aux_g, row, col, couleur);
			ens_g = Ajout(ens_g, aux_g);
		}
	};

	return ens_g;
}

void minimax( Node * n ){
	int min = 1;
	int max = -1;
	
	if( n -> fils == NULL )
	{	/* Si n est une feuille */

		if( graphe_chaine_gagnante( n -> minimax_config, NOIR ) )
			n -> minimax_valeur = 1;
		else if( graphe_chaine_gagnante( n -> minimax_config, BLANC ) )
			n -> minimax_valeur = -1;
	}

	else if( n -> fils )
	{	/* Si n est un Noeud */

		/* Recherche du minimum et du maximum */
		for(int i=0; i<n -> nb_fils; i++){
			if( n -> fils[i] -> minimax_valeur < min)
				min = n -> fils[i] -> minimax_valeur;
			if( n -> fils[i] -> minimax_valeur > max)
				max = n -> fils[i] -> minimax_valeur;
		}

		/* Affectation de la minimax_valeur */
		if( n -> couleur == NOIR ){
			n -> minimax_valeur = min;
		}
		else{
			n -> minimax_valeur = max;
		}
	}
}

Node* minimax_ajout_successeur(Node* n, Ensemble ensemble, int couleur){
	
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

	//printf("c == %d n = %d\n", cardinal(ensemble), aux);

	for(int i=0; i<aux -> nb_fils; i++){

		add = (Node*) malloc( sizeof( Node ) );
		assert(add != NULL);

		add -> nb_fils = 0;
		add -> minimax_valeur = 1;

		el = element( ensemble, i );
		add -> minimax_config = el;

		add -> couleur = couleur;

		add -> fils = NULL;
		add -> parent = aux; 

		add -> etage = add -> parent -> etage + 1;

		aux -> fils[i] = add;
		
		if(couleur == NOIR){
			minimax_ajout_successeur(add, minimax_successeur( add -> minimax_config, BLANC), BLANC);
		}
		else{
			minimax_ajout_successeur(add, minimax_successeur( add -> minimax_config, NOIR), NOIR);
		}

		minimax( add );
		//printf("-\n");
		//graphe_affichage(add -> minimax_config);
	}

	return aux;
}

Minimax minimax_build(Minimax m, int n){
	m = minimax_initialisation(n);
	Node * aux = m -> minimax_root;
	Ensemble ensemble;

	ensemble = minimax_successeur( aux -> minimax_config, NOIR);
	minimax_ajout_successeur(aux, ensemble, NOIR);

	return m;
}


void minimax_tri_iteratif_largeur(Minimax abr){
	File file;
	Node* nodeCour = abr -> minimax_root;

	file = file_initialisation();

	/* Enfile la racine */
	file_enfiler(file, nodeCour);

	while( !file_vide( file ) ){
		nodeCour = file_defiler(file);

		/* Effectue une action sur le noeud concerner */
		graphe_affichage(nodeCour -> minimax_config);

		/* Enfile les fils si ils en existe */
		for(int i=0; i<nodeCour -> nb_fils; i++){
			if(nodeCour -> fils[i] != NULL){
				file_enfiler(file, nodeCour -> fils[i]);
			}
		}
	}
}


Node* minimax_search_graphe(Minimax abr, Graphe g, int nivau){
	File file;
	Node* nodeCour = abr -> minimax_root;
	file = file_initialisation();

	/* Enfile la racine */
	file_enfiler(file, nodeCour);

	while( !file_vide( file ) ){
		nodeCour = file_defiler(file);

		/* Effectue une action sur le noeud concerner */
		if( nodeCour -> etage == nivau && minimax_graphe_identique( g, nodeCour -> minimax_config ) ){
			return nodeCour;
		}

		/* Enfile les fils si ils en existe */
		for(int i=0; i<nodeCour -> nb_fils; i++){
			if(nodeCour -> fils[i] != NULL){
				file_enfiler(file, nodeCour -> fils[i]);
			}
		}
	}

	return NULL;
}

bool minimax_graphe_identique(Graphe g, Graphe h){
	bool identique = true;
	Hexa sommet_g;
	Hexa sommet_h;
	int col,row;
	int n = graphe_size(g);
	assert(n == graphe_size(h));
	if( n != graphe_size(h) )
		return false;
	
	for(int i=0; (i<n*n && identique); i++){
		minimax_ligne_colonne( n, i, &row, &col);
		sommet_g = graphe_hexagone(g, row, col);
		sommet_h = graphe_hexagone(h, row, col);

		if( graphe_couleur_sommet(sommet_g) != graphe_couleur_sommet(sommet_h) )
			identique = false;
	}

	return identique;
}

Graphe minimax_search_config_gagnant(Node* n, int valeur_gagnante){
	File file;
	Node* nodeCour = n;
	file = file_initialisation();

	/* Enfile la racine */
	file_enfiler(file, nodeCour);

	while( !file_vide( file ) ){
		nodeCour = file_defiler(file);

		/* Effectue une action sur le noeud concerner */
		if( nodeCour != n && nodeCour -> minimax_valeur == valeur_gagnante )
			return nodeCour -> minimax_config;

		/* Enfile les fils si ils en existe */
		for(int i=0; i<nodeCour -> nb_fils; i++){
			if(nodeCour -> fils[i] != NULL){
				file_enfiler(file, nodeCour -> fils[i]);
			}
		}
	}

	return NULL;
}

#define MAXFILE 9000000
typedef struct s_queue {
	Node* queue[MAXFILE];
	int head;
	int tail;
} *QueueOfBinaryTrees;

QueueOfBinaryTrees queue_create() {
	QueueOfBinaryTrees f = (QueueOfBinaryTrees) malloc(sizeof(struct s_queue));
	f -> head = 0;
	f -> tail = 0;
	return f;
}

void queue_push(QueueOfBinaryTrees f, Node* a) {
	f -> queue[f->head] = a;
	f -> head = (f->head + 1) % MAXFILE;
}

Node* queue_pop(QueueOfBinaryTrees f) {
	Node* a = f->queue[f->tail];
	f->tail = (f->tail + 1) % MAXFILE;
	return (a);
}

int queue_empty(QueueOfBinaryTrees f) {
	return (f->tail == f->head);
}

void queue_delete(QueueOfBinaryTrees f) {
	free(f);
}


/* -------------------------------------------- */
/*	Export the tree as a dot file				*/
/* -------------------------------------------- */

void minimax_printNode(Node* n, FILE *file){
	char chaine[100];
	graphe_chaine_daffichage( n -> minimax_config, chaine);
	if(n -> couleur == BLANC)
		fprintf(file, "\tn%d [fillcolor = ghostwhite, label=\"%sValeur de jeu = %d\"];\n",
			n, chaine, n -> minimax_valeur);
	else if(n -> couleur == NOIR)
		fprintf(file, "\tn%d [fillcolor = deepskyblue1, label=\"%sValeur de jeu = %d\"];\n",
			n, chaine, n -> minimax_valeur);
	else
		fprintf(file, "\tn%d [fillcolor = gold1, label=\"%sValeur de jeu = %d\"];\n",
			n, chaine, n -> minimax_valeur);

	for(int i=0; i<n -> nb_fils; i++){
		if(n -> fils[i] != NULL){
			fprintf(file, "\tn%d -> n%d [penwidth = 3, color=white]\n",
				n, n -> fils[i]);
		}
	}
}

void minimax_export_dot(Node* t, FILE *file) {
	QueueOfBinaryTrees q = queue_create();
	fprintf(file, "digraph Minimax {\n\tgraph [\n\t\trankdir = TD\n\t\tbgcolor = blue\n\t];\n\tnode [\n\t\tshape = doublecircle\n\t\tfontsize = \"12\"\n\t\tfontname=\"Harry P\"\n\t\tstyle = \"filled\"\n\t];\n\n");

	queue_push(q, t);
	while (!queue_empty(q)) {
		t = queue_pop(q);
		minimax_printNode(t, file);
		for(int i=0; i<t -> nb_fils; i++){
			if(t -> fils[i] != NULL){
				queue_push(q, t -> fils[i]);
			}
		}
	}
	
	fprintf(file, "\n}\n");
}