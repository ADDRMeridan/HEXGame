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
	int couleur;
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
	m -> root -> couleur = TRANSPARANT;
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

int nombre_fils(Node n){
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

/**
 *	@brief une fonction successeur qui associe à chaque 
 		conﬁguration de jeu, l’ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 *	@param config : une configaration (graphe).
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *  @return Ensemble : un ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 */
Ensemble successeur(Graphe config, int couleur){
	int n;
	int row,col;
	Ensemble ens_g = Vide();
	Graphe aux_g = NULL;

	Hexa sommet;

	if( chaine_gagnante( config, NOIR ) || chaine_gagnante( config, BLANC ) )
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

		el = element( ensemble, i );
		add -> config = el;

		add -> couleur = couleur;

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

		/* Enfile les fils si ils en existe */
		for(int i=0; i<nodeCour -> nb_fils; i++){
			if(nodeCour -> fils[i] != NULL){
				enfiler_2(file, nodeCour -> fils[i]);
			}
		}
		printf("\n");
	}
}


#define MAXFILE 4096
typedef struct s_queue {
	Node* queue[MAXFILE];
	int head;
	int tail;
} *QueueOfBinaryTrees;

QueueOfBinaryTrees queue_create() {
	QueueOfBinaryTrees f = (QueueOfBinaryTrees) malloc(sizeof(struct s_queue));
	f->head = 0;
	f->tail = 0;
	return f;
}

void queue_push(QueueOfBinaryTrees f, Node* a) {
	f->queue[f->head] = a;
	f->head = (f->head + 1) % MAXFILE;
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

void printNode(Node* n, FILE *file){
	char chaine[100];
	chaine_hexa_graph( n -> config, chaine);
	if(n -> couleur == BLANC)
		fprintf(file, "\tn%d [fillcolor = ghostwhite, label=\"%s\"];\n",
			n, chaine);
	else if(n -> couleur == NOIR)
		fprintf(file, "\tn%d [fillcolor = deepskyblue1, label=\"%s\"];\n",
			n, chaine);
	else
		fprintf(file, "\tn%d [fillcolor = gold1, label=\"%s\"];\n",
			n, chaine);

	for(int i=0; i<n -> nb_fils; i++){
		if(n -> fils[i] != NULL){
			fprintf(file, "\tn%d -> n%d [penwidth = 2]\n",
				n, n -> fils[i]);
		}
	}
}

void rbtree_export_dot(Node* t, FILE *file) {
	QueueOfBinaryTrees q = queue_create();
	fprintf(file, "digraph Minimax {\n\tgraph [\n\t\trankdir = LR\n\t\tbgcolor= aliceblue\n\t];\n\tnode [\n\t\tshape = doublecircle\n\t\tfontsize = \"10\"\n\t\tfontname=\"Harry P\"\n\t\tstyle = \"rounded,filled\"\n\t];\n\n");

	queue_push(q, t);
	while (!queue_empty(q)) {
		t = queue_pop(q);
		printNode(t, file);
		for(int i=0; i<t -> nb_fils; i++){
			if(t -> fils[i] != NULL){
				queue_push(q, t -> fils[i]);
			}
		}
	}
	
	fprintf(file, "\n}\n");
}