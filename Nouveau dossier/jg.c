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

#include "jg.h"

typedef Hexa Element;

/* Sommet */
struct s_sommet{
	int col;
	int row;
};

typedef struct s_sommet Sommet;

/* Hexagone */
struct s_hexa{
	struct s_hexa ** aretes;
	Sommet sommet;
	int couleur;
	int nb_aretes;
};

typedef struct s_hexa * Hexa;

/* Graphe contient les 4 Sommet des bords */
struct s_Graphe{
	Hexa W1;
	Hexa W2;
	Hexa B1;
	Hexa B2;
	int size;

	/* Pour amelioré la complexité de recherche d'un graphe_hexagone */
	Hexa* tab;
};

/*Liste*/

struct et_cellule{
	Element elmt;
	struct et_cellule* pred;
	struct et_cellule* suiv;
};

typedef struct et_cellule cellule;

struct et_liste{
	cellule* debut;
	cellule* fin;
};

typedef struct et_liste Liste;

Graphe graphe;

/*  */
void graphe_ligne_colonne( int graphe_num_case, int *ligne, int *col){
    assert( graphe_num_case < (graphe -> size * graphe -> size) && graphe_num_case >= 0 );
    
    *ligne = graphe_num_case / graphe -> size;
    *col = graphe_num_case % graphe -> size;
}

/*  */
int graphe_num_case( int ligne, int col ){
    assert( ligne < graphe -> size && ligne >= 0 && col < graphe -> size && col >= 0 );
    
    return graphe -> size * ligne + col;
}

/* */
Hexa graphe_colorie_sommet(int row, int col, int couleur){
	
	Hexa hex = graphe -> tab[graphe_num_case(row, col)];
	hex -> couleur = couleur;
	return hex;
}

void graphe_initialisation(int n){
	graphe;
	Hexa hexa; 
	Hexa pred_hexa;

	/* inite Graphe */
	graphe = (Graphe) malloc( sizeof( struct s_Graphe ) );
	assert(graphe != NULL);

	/* inite Graphe W1 (lignes en debut de colonne) */
	graphe -> W1 = (Hexa) malloc( sizeof( struct s_hexa ) );
	assert(graphe -> W1 != NULL);

	graphe -> W1 -> aretes = (Hexa*) malloc( ( n + 1 ) * sizeof( Hexa ) );
	assert( graphe -> W1 -> aretes != NULL );

	graphe -> W1 -> couleur = BLANC;

	/* inite Graphe B1 (colonnes en debut de ligne) */
	graphe -> B1 = (Hexa) malloc( sizeof( struct s_hexa ) );
	assert(graphe -> B1 != NULL);

	graphe -> B1 -> aretes = (Hexa*) malloc( ( n + 1 ) * sizeof( Hexa ) );
	assert( graphe -> B1 -> aretes != NULL );

	graphe -> B1 -> couleur = NOIR;

	/* inite Graphe W2 (lignes en fin de colonne) */
	graphe -> W2 = (Hexa) malloc( sizeof( struct s_hexa ) );
	assert(graphe -> W2 != NULL);

	graphe -> W2 -> aretes = (Hexa*) malloc( ( n + 1 ) * sizeof( Hexa ) );
	assert( graphe -> W2 -> aretes != NULL );

	graphe -> W2 -> couleur = BLANC;

	/* inite Graphe B2 (colonnes en fin de ligne) */
	graphe -> B2 = (Hexa) malloc( sizeof( struct s_hexa ) );
	assert(graphe -> B2 != NULL);

	graphe -> B2 -> aretes = (Hexa*) malloc( ( n + 1 ) * sizeof( Hexa ) );
	assert( graphe -> B2 -> aretes != NULL );

	graphe -> B2 -> couleur = NOIR;

	graphe -> size =  n;

	graphe -> tab = (Hexa*) malloc( ( n * n ) * sizeof( Hexa ) );
	assert( graphe -> tab != NULL );

	/* Initialise les numero de ligne et de colonne des sommets */
	for( int row=0; row<n; row++ ){

		/* graphe_hexagone (Sommet) sur la 1er colonne de chaque ligne */
		hexa = (Hexa) malloc( sizeof( struct s_hexa ) );
		assert(hexa != NULL);

		graphe -> W1 -> aretes[row] = hexa;

		for( int col=0; col<n; col++ ){

			/* Initialisation des pointeurs 'aretes' */
			hexa -> aretes = (Hexa*) malloc( 7 * sizeof( Hexa ) );
			assert( hexa -> aretes != NULL );

			hexa -> nb_aretes = 6;

			if(row == 0)
				graphe -> B1 -> aretes[col] = hexa;

			if( row+1 == n ){
				graphe -> B2 -> aretes[col] = hexa;

				/* aretes du bas inexistantes */
				hexa -> aretes[1] = NULL;
				hexa -> aretes[2] = NULL;
			}

			hexa -> aretes[6] = NULL;

			if(pred_hexa != NULL)
				hexa -> aretes[3] = pred_hexa;

			hexa -> sommet.col = col;
			hexa -> sommet.row = row;

			graphe_colorie_sommet(row, col, TRANSPARANT);

			graphe -> tab[graphe -> size*row+col] = hexa;

			/*  */
			if( row > 0 ){
				/*	hexa-arrete ( haut gauche (4) ) <--> à l'hexa en haut à gauche
					hexa-arrete ( haut droite (5) ) <--> à l'hexa en haut à droite
					*/
				if( col == 0 ){
					hexa -> aretes[4] = graphe -> W1 -> aretes[row-1];
					graphe -> W1 -> aretes[row-1] -> aretes[1] = hexa;

					hexa -> aretes[5] = graphe -> W1 -> aretes[row-1] -> aretes[0];
					graphe -> W1 -> aretes[row-1] -> aretes[0] -> aretes[2] = hexa;
					
				}
				else{
					hexa -> aretes[4] = pred_hexa -> aretes[5];
					pred_hexa -> aretes[5] -> aretes[1] = hexa; 

					if( col < n-1 ){
						hexa -> aretes[5] = pred_hexa -> aretes[5] -> aretes[0];
						pred_hexa -> aretes[5] -> aretes[0] -> aretes[2] = hexa;
					}
					else
						hexa -> aretes[5] = NULL;
				}

			}
			else{
				/* aretes du haut inexistante */
				hexa -> aretes[4] = NULL;
				hexa -> aretes[5] = NULL;
			}

			if( col == 0 ){
				/* aretes de gauche inexistante */
				hexa -> aretes[3] = NULL;
				hexa -> aretes[2] = NULL;
			}

			/* Passe à l'Hexagone à sa droite (colonne suivante) */
			if( col+1 < n ){

				/* suiv = new_hexa; hexa -> suiv; */
				hexa -> aretes[0] = (Hexa) malloc( sizeof( struct s_hexa ) );
				assert(hexa -> aretes[0] != NULL);
				
				/* pred = hexa; hexa = suiv; pred<-hexa */
				pred_hexa = hexa;
				hexa = hexa -> aretes[0];
			}

		}

		graphe -> W2 -> aretes[row] = hexa;

		hexa -> aretes[0] = NULL;

	}

	return graphe;
}



int graphe_size(){
	return graphe -> size;
}

int graphe_couleur_sommet(int num_case){
	return graphe -> tab[num_case] -> color;
}


int graphe_couleur_hexagone( int row, int colonne ){
	int n = graphe_size(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );
	
	int num_case = graphe_num_case( row, colonne );
	Hexa hexa = graphe -> tab[num_case];

	return graphe_couleur_sommet( hexa );
}

/* */
bool graphe_sommet_adjacent(int row_1, int col_1, int row_2, int col_2){
	int num_case_1 = graphe_num_case( row_1, col_1 );
	int num_case_2 = graphe_num_case( row_2, col_2 );
	Hexa hex_1 = graphe -> tab[num_case_1];
	Hexa hex_2 = graphe -> tab[num_case_2];
	/* Verifie que l'une des aretes de hex_1 pointe bien vers hex_2 */
	for(int i=0; i<6; i++){

		if( hex_1 != NULL && hex_1 -> aretes[i] != NULL 
			&& hex_2 != NULL && hex_1 -> aretes[i] == hex_2 ){
			//printf("[%d,%d] Connecter au sommet [%d,%d] \n", hex_1->sommet.row, hex_1->sommet.col, hex_2->sommet.row, hex_2->sommet.col);
			return true;
		}
	}

	return false;
}


/* */
Graphe graphe_ajout_hexagone( int row, int colonne, int couleur){

	int n = graphe_size(graphe);

	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );
	assert( couleur == NOIR || couleur == BLANC );

	int num_case = graphe_num_case( row, colonne );
	Hexa hexa = graphe -> tab[num_case];

	assert( graphe_couleur_sommet( hexa ) == TRANSPARANT );
	hexa = graphe_colorie_sommet(row, colonne, couleur);

	/* Ajout dans groupe */
	for(int i=0; i<6; i++){
		graphe_ajout_dans_groupe( hexa, hexa -> aretes[i] );
	
		Hexa hex_1 = hexa;
		Hexa hexa -> aretes[i];

		Hexa graphe_groupe = NULL;
		Hexa groupe_2;
		int nb_hexa_groupe_2;

		if( hex_1 != NULL && hex_2 != NULL && graphe_sommet_adjacent(hex_1, hex_2) && graphe_couleur_sommet(hex_1) != TRANSPARANT && graphe_couleur_sommet(hex_1) == graphe_couleur_sommet(hex_2) ){
			//printf("-1\n");
			/* Si ils n'appartiennent a aucun graphe_groupe */
			if( hex_1 -> aretes[6] == NULL && hex_2 -> aretes[6] == NULL ){
				//printf("--1 c %d \n", graphe_couleur_sommet(hex_1) );
				graphe_groupe = (Hexa) malloc( sizeof(struct s_hexa) );
				assert( graphe_groupe != NULL );

				graphe_groupe -> aretes = (Hexa*) malloc( 2 * sizeof(Hexa) );
				assert( graphe_groupe -> aretes != NULL );

				graphe_groupe -> aretes[0] = hex_1;
				graphe_groupe -> aretes[1] = hex_2;

				hex_1 -> aretes[6] = graphe_groupe;
				hex_2 -> aretes[6] = graphe_groupe;

				assert( graphe_groupe -> aretes[0] != NULL );

				graphe_groupe -> nb_aretes = 2;
				graphe_groupe -> couleur = graphe_couleur_sommet(hex_1);

			}

			/* Si hex_2 est deja dans un graphe_groupe mais pas hex_1 */
			else if( hex_2 -> aretes[6] != NULL && hex_1 -> aretes[6] == NULL ){
				//printf("--2 %d \n", graphe_couleur_sommet(hex_1) );
				graphe_groupe = hex_2 -> aretes[6];

				graphe_groupe -> aretes = (Hexa*) realloc(graphe_groupe -> aretes, ( graphe_groupe -> nb_aretes + 1 ) * sizeof(Hexa) );
				assert( graphe_groupe -> aretes != NULL );

				graphe_groupe -> aretes[graphe_groupe -> nb_aretes] = hex_1;
				hex_1 -> aretes[6] = graphe_groupe;

				graphe_groupe -> nb_aretes++;
			}

			/* Si hex_1 est deja dans un graphe_groupe mais pas hex_2 */
			else if( hex_1 -> aretes[6] != NULL && hex_2 -> aretes[6] == NULL ){
				//printf("--3 %d \n", graphe_couleur_sommet(hex_1) );
				graphe_groupe = hex_1 -> aretes[6];

				graphe_groupe -> aretes = realloc(graphe_groupe->aretes, graphe_groupe -> nb_aretes+1 * sizeof(Hexa) );
				assert( graphe_groupe -> aretes != NULL );

				graphe_groupe -> aretes[graphe_groupe -> nb_aretes] = hex_2;
				hex_2 -> aretes[6] = graphe_groupe;

				graphe_groupe -> nb_aretes++;
			}

			/* Si hex_1 et hex_2 sont deja dans un graphe_groupe */
			else if( hex_1 -> aretes[6] != NULL && hex_2 -> aretes[6] != NULL && hex_2 -> aretes[6] != hex_1 -> aretes[6]){
				//printf("--4\n");
				/* Privilégie le graphe_groupe de plus grande taille */
				if( hex_1 -> aretes[6] -> nb_aretes > hex_2 -> aretes[6] -> nb_aretes ){
					graphe_groupe = hex_1 -> aretes[6];
					groupe_2 = hex_2 -> aretes[6];
				}
				else{
					graphe_groupe = hex_2 -> aretes[6];
					groupe_2 = hex_1 -> aretes[6];
				}

				nb_hexa_groupe_2 = groupe_2 -> nb_aretes;

				graphe_groupe -> aretes = (Hexa*) realloc(graphe_groupe -> aretes, ( graphe_groupe -> nb_aretes + groupe_2 -> nb_aretes ) * sizeof(Hexa) );
				assert( graphe_groupe -> aretes != NULL );

				/* Ajout des element du graphe_groupe 2 dans le graphe_groupe 1 */
				for( int i=graphe_groupe -> nb_aretes; i<( graphe_groupe -> nb_aretes + groupe_2 -> nb_aretes ); i++ ){
					graphe_groupe -> aretes[i] = groupe_2 -> aretes[i - graphe_groupe -> nb_aretes];
					graphe_groupe -> aretes[i] -> aretes[6] = graphe_groupe;
				}

				/* Suppression du graphe_groupe 2 */
				for( int i=groupe_2 -> nb_aretes-1; i>=0; i-- ){
					groupe_2 -> aretes[i] = NULL;
					free( groupe_2 -> aretes[i] );
				}
				groupe_2 = NULL;
				free( groupe_2 );

				graphe_groupe -> nb_aretes += nb_hexa_groupe_2;
			}

		}
	}
	
	return graphe;
}


bool graphe_chaine_gagnante(int couleur){

	int n = graphe_size( graphe );
	int i,e;
	bool gagnant = false;
	
	Hexa bord_1;
	Hexa bord_2;

	assert( couleur == NOIR || couleur == BLANC );

	if( couleur == NOIR){
		bord_1 = graphe -> B1;
		bord_2 = graphe -> B2;
	}
	else{
		bord_1 = graphe -> W1;
		bord_2 = graphe -> W2;
	}

	i=0;

	/* Verifie que le bord_1 appartient à un meme graphe_groupe que 
	   le bord_2 Exemple w1 et w2 sont dans un meme graphe_groupe */
	while( i<n && !gagnant ){

		if( bord_1 -> aretes[i] -> aretes[6] != NULL ){

			e = 0;

			while( e<n && !gagnant ){

				if( bord_2 -> aretes[e] -> aretes[6] != NULL && bord_2 -> aretes[e] -> aretes[6] == bord_1 -> aretes[i] -> aretes[6] 
					&& graphe_couleur_sommet( bord_2 -> aretes[e] -> aretes[6] ) == couleur )
					gagnant = true;

				e++;
			}
		}
		
		i++;
	}

	return gagnant;
}


/* */
void graphe_affiche_row_col_sommet(){

	int n = graphe_size( graphe );
	
	for( int row=0; row<n; row++ ){

		Hexa hexa = graphe->W1->aretes[row];

		for( int col=0; col<n; col++ ){
			if(col == hexa -> sommet .col && row == hexa -> sommet .row){
				if( hexa != NULL )
					printf("[%d,%d] ", hexa->sommet.row, hexa->sommet.col);

				/* Passe à l'Hexagone à sa droite (colonne suivante) */
				if( col + 1 < n && hexa->aretes[0] != NULL)
					hexa = hexa->aretes[0];
				else
					col = n;
			}

		}
		printf("\n");

	}
}


void graphe_affichage(){

	int n = graphe_size( graphe );
	
	for( int row=0; row<n; row++ ){
		for (int i = 0; i < row; ++i)
			printf(" ");

		Hexa hexa = graphe -> W1 -> aretes[row];

		for( int col=0; col<n; col++ ){
			if(col == hexa -> sommet .col && row == hexa -> sommet.row){

				if( hexa->couleur == 2 )
					printf("T    ");
				else if( hexa->couleur == 1 )
					printf("B    ");
				else
					printf("N    ");

				/* Passe à l'Hexagone à sa droite (colonne suivante) */
				if( col + 1 < n && hexa -> aretes[0] != NULL )
					hexa = hexa -> aretes[0];
				else
					col = n;
			}

		}
		printf("\n");
		
	}
}

/* Fourni la Valeur absolu de x */
int graphe_valeur_absolu(int x){

	if( x < 0 ){
		return -x;
	}

	return x;
}


int graphe_distance_hexagones(int col_1, int row_1, int col_2,int row_2){
	int d;

	if( col_1 == col_2 || row_1 == row_2 )
	{	/* Meme ligne ou meme colonne */
		d = graphe_valeur_absolu(row_1 - row_2) + graphe_valeur_absolu(col_1 - col_2);
	}
	else if( graphe_valeur_absolu(row_1 - row_2) == graphe_valeur_absolu(col_1 - col_2) )
	{	/* Si diagonale */
		if( ( row_1 > row_2 && col_1 < col_2 ) || ( row_1 < row_2 && col_1 > col_2 ) ){
			d = graphe_valeur_absolu(col_1 - col_2);
		}
		else{
			d = graphe_valeur_absolu(col_1 - col_2) * 2;
		}
	}
	else
	{	/* Autre */
		if( ( row_1 > row_2 && col_1 < col_2 ) || ( row_1 < row_2 && col_1 > col_2 ) ){
			if( graphe_valeur_absolu(col_1 - col_2) > graphe_valeur_absolu(row_1 - row_2) ){
				d = graphe_valeur_absolu(col_1 - col_2);
			}
			else{
				d = graphe_valeur_absolu(row_1 - row_2);
			}
		}
		else{
			d = graphe_valeur_absolu(col_1 - col_2) + graphe_valeur_absolu(row_1 - row_2);
		}
	}

	return (d + 1);
}
