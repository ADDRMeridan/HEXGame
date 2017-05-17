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

#include "graphe.h"
#include "ensemble.h"

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

/* */
Hexa graphe_colorie_sommet(Hexa hex, int couleur){
	hex -> couleur = couleur;
	return hex;
}

Graphe graphe_initialisation(int n){
	Graphe graphe;
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

			graphe_colorie_sommet(hexa, TRANSPARANT);

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

bool graphe_vide(Graphe graphe){
	int n = graphe -> size;

	for(int i=0; i<n*n; i++){
		if(graphe -> tab[i] -> couleur != TRANSPARANT)
			return false;
	}

	return true;
}

void graphe_suppression(Graphe *graphe){
	int n = (*graphe) -> size;

	if( graphe_vide((*graphe)) ){

		for(int i=0; i<n*n; i++){
			(*graphe) -> tab[i] = NULL;
			free((*graphe) -> tab[i]);
		}

		(*graphe) -> tab = NULL;
		free((*graphe) -> tab);

		for(int e=0; e<n; e++){
			(*graphe) -> W1 -> aretes[e] = NULL;
			(*graphe) -> W2 -> aretes[e] = NULL;
			(*graphe) -> B1 -> aretes[e] = NULL;
			(*graphe) -> B2 -> aretes[e] = NULL;
			free((*graphe) -> W1 -> aretes[e]);
			free((*graphe) -> W2 -> aretes[e]);
			free((*graphe) -> B1 -> aretes[e]);
			free((*graphe) -> B2 -> aretes[e]);
		}

		(*graphe) -> W1 = NULL;
		(*graphe) -> W2 = NULL;
		(*graphe) -> B1 = NULL;
		(*graphe) -> B2 = NULL;

		free((*graphe) -> W1);
		free((*graphe) -> W2);
		free((*graphe) -> B1);
		free((*graphe) -> B2);

		(*graphe) = NULL;
		free((*graphe));
	}
}

/*  */
void graphe_ligne_colonne(Graphe g, int graphe_num_case, int *ligne, int *col){
    assert( graphe_num_case < (g -> size * g -> size) && graphe_num_case >= 0 );
    
    *ligne = graphe_num_case / g -> size;
    *col = graphe_num_case % g -> size;
}

/*  */
int graphe_num_case(Graphe g, int ligne, int col){
    assert( ligne < g -> size && ligne >= 0 && col < g -> size && col >= 0 );
    
    return g -> size * ligne + col;
}

int graphe_size(Graphe graphe){
	return graphe -> size;
}

int graphe_couleur_sommet(Hexa hex){
	return hex -> couleur;
}

Hexa graphe_hexagone(Graphe graphe, int row, int colonne){
	int n = graphe_size(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );
	Hexa hexa = graphe -> tab[graphe_num_case(graphe, row, colonne)];
	return hexa;
}

int graphe_couleur_hexagone(Graphe graphe, int row, int colonne){
	int n = graphe_size(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );

	Hexa hexa = graphe_hexagone(graphe, row, colonne);

	return graphe_couleur_sommet( hexa );
}

/* */
bool graphe_sommet_adjacent(Hexa hex_1, Hexa hex_2){

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
void graphe_ajout_dans_groupe(Hexa hex_1, Hexa hex_2){

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
	//printf("-2-\n");
}

/* */
Graphe graphe_ajout_hexagone( Graphe graphe, int row, int colonne, int couleur){

	int n = graphe_size(graphe);

	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );
	assert( couleur == NOIR || couleur == BLANC );

	Hexa hexa = graphe_hexagone(graphe, row, colonne);

	assert( graphe_couleur_sommet( hexa ) == TRANSPARANT );
	hexa = graphe_colorie_sommet(hexa, couleur);

	for(int i=0; i<6; i++)
		graphe_ajout_dans_groupe( hexa, hexa -> aretes[i] );
	
	//printf("[%d,%d]-- \n", hexa->sommet.row, hexa->sommet.col);

	return graphe;
}

Graphe graphe_supprime_hexagone( Graphe graphe, int row, int col ){
	
	Hexa hex = graphe_hexagone( graphe, row, col );
	Hexa groupe;
	int n;

	if( hex -> couleur != TRANSPARANT ){
		if( hex -> aretes[6] != NULL ){
			groupe = hex -> aretes[6];
			n = groupe -> nb_aretes;

			for(int i=0; i<n; i++){

				/* Recherche l'emplacement du sommet du groupe */
				if( groupe -> aretes[i] == hex ){

					/* Decalage */
					for(int e=i; e<n - 1; e++){
						groupe -> aretes[e] = groupe -> aretes[e+1];
					}

					/* Suppression de l'arete du groupe vers le sommet */
					groupe -> aretes[n - 1] = NULL;
					hex -> aretes[6] = NULL;

					free(groupe -> aretes[n-1]);
					groupe -> nb_aretes--;

					/* Si il n'ya plus de sommet dans le groupe, on le supprime */
					if( groupe -> nb_aretes == 0 ){
						groupe = NULL;
						free(groupe);
					}

					hex = graphe_colorie_sommet(hex, TRANSPARANT);
					return graphe;
				}
			}
		}
		else{
			hex = graphe_colorie_sommet(hex, TRANSPARANT);
			return graphe;
		}
	}

	return graphe;
}


bool graphe_chaine_gagnante(Graphe graphe, int couleur){

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
		

Hexa graphe_groupe_en_sommet_unique(Graphe graphe, Hexa graphe_groupe){
	Hexa sommet_unique;
	Hexa grp = graphe_groupe;
	int couleur = (grp) -> couleur;

	assert( grp != NULL );

	sommet_unique = (Hexa) malloc( sizeof( struct s_hexa ) );
	assert( sommet_unique != NULL );

	sommet_unique -> aretes = (Hexa*) malloc( sizeof( Hexa ) );
	assert( sommet_unique -> aretes != NULL );

	assert( (grp) -> aretes[0] != NULL );

	sommet_unique -> sommet . col = (grp) -> aretes[0] -> sommet . col;
	sommet_unique -> sommet . row = (grp) -> aretes[0] -> sommet . row;
	sommet_unique -> couleur = couleur;
	sommet_unique -> nb_aretes = 0;

	printf("-----%d %d\n", sommet_unique -> sommet . row, sommet_unique -> sommet . col);

	for(int i=0; i<(grp) -> nb_aretes; i++){

		printf("pour %d %d\n", (grp) -> aretes[i] -> sommet . row, (grp) -> aretes[i] -> sommet . col );

		/* Mise à jour des bords */
		if(	(grp) -> aretes[i] -> sommet . col  == graphe_size(graphe)-1 ){
			graphe -> W2 -> aretes[ ((grp) -> aretes[i] -> sommet . row) ] = sommet_unique;
		}
		if(	(grp) -> aretes[i] -> sommet . col  == 0 ){
			graphe -> W1 -> aretes[ ((grp) -> aretes[i] -> sommet . row) ] = sommet_unique;
		}
		if( (grp) -> aretes[i] -> sommet . row  == graphe_size(graphe)-1 ){
			graphe -> B2 -> aretes[ ((grp) -> aretes[i] -> sommet . col) ] = sommet_unique;
		}
		if( (grp) -> aretes[i] -> sommet . row  == 0 ){
			graphe -> B1 -> aretes[ ((grp) -> aretes[i] -> sommet . col) ] = sommet_unique;
		}


		for (int e = 0; e < 6; e++){
			if( (grp) -> aretes[i] -> aretes[e] != NULL && ( (grp) -> aretes[i] -> aretes[e] -> couleur != couleur ) ){
				sommet_unique -> nb_aretes++;
				//printf("ok   %d %d\n", (grp) -> aretes[i] -> aretes[e] -> sommet . row, (grp) -> aretes[i] -> aretes[e] -> sommet . col );

				sommet_unique -> aretes = (Hexa*) realloc(sommet_unique -> aretes, ( sommet_unique -> nb_aretes + 1 ) * sizeof(Hexa) );
				assert( sommet_unique -> aretes != NULL );

				sommet_unique -> aretes[ sommet_unique -> nb_aretes-1 ] = (grp) -> aretes[i] -> aretes[e];
				(grp) -> aretes[i] -> aretes[e] -> aretes[(e+3) % 6] = sommet_unique;

				/* Liberation de la memoire sur les aretes des sommets du graphe_groupe */
				(grp) -> aretes[i] -> aretes[e] = NULL;
				free( (grp) -> aretes[i] -> aretes[e] );
				
			}
		}
		//printf("\n");
	}

	/* Liberation de la memoire sur les sommets du graphe_groupe */
	for (int i = 0; i < (grp) -> nb_aretes; i++){
		(grp) -> aretes[i] = NULL;
		free((grp) -> aretes[i]);
	}

	grp = NULL;
	free(grp);

	return sommet_unique;
}

Graphe graphe_reduit( Graphe graphe ){
	Graphe g = graphe;

	int n = graphe_size( graphe );
	
	for( int row=0; row<n; row++ ){

		Hexa hexa = g -> W1 -> aretes[row];

		for( int col=0; col<n; col++ ){
			if(hexa != NULL && col == hexa -> sommet.col && row == hexa -> sommet.row){
				if( hexa -> aretes[6] != NULL && hexa -> nb_aretes == 6 )
					hexa = graphe_groupe_en_sommet_unique(g ,(hexa -> aretes[6]) );
				
				printf("nb_aretes %d\n", hexa -> nb_aretes);
				/* Passe à l'Hexagone à sa droite (colonne suivante) */
				if( col + 1 < n && hexa->aretes[0] != NULL)
					hexa = hexa->aretes[0];
				else
					col = n;
			}
			printf("---\n");
		}
		printf("-\n");

	}

	return g;
}


/* */
void graphe_affiche_row_col_sommet(Graphe graphe){

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


void graphe_affichage(Graphe graphe){

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



/*Liste*/

Liste initialier_liste(){
	Liste li;
	li.debut = NULL;
	li.fin = NULL;
	return li;
}

bool vide_liste(Liste li){
	return (li.debut == NULL && li.fin == NULL);
}

void trouver_position(Liste li, cellule **avant, cellule **apres){
	cellule *cour = li.debut;
	while( cour != NULL ){
		cour = cour->suiv;
	}
	
	if( cour == NULL ){
		*apres = NULL;
		*avant = li.fin;
	}
	else{
		*apres = cour;
		*avant = cour->pred;
	}	
}

bool est_premier(Liste li, Element el){
	return (li.debut -> elmt == el );
}

bool est_dernier(Liste li, Element el){
	return (li.fin -> elmt == el );
}


Liste ajoute_element( Liste li, Element el ){
	
	cellule * avant;
	cellule * apres;
	cellule * cour = NULL;

	cour = (cellule*) malloc(sizeof(cellule));
	assert( cour != NULL );

	trouver_position(li, &avant, &apres);

	cour -> pred = avant;
	cour -> suiv = apres;

	if( avant == NULL ) li.debut = cour;
	else avant -> suiv = cour;
	if( apres == NULL ) li.fin = cour;
	else apres -> pred = cour;
	
	return li;
}

Liste supprime_element( Liste li, Element el ){
	
	cellule *avant;
	cellule *apres;
	cellule *cour;
	cour = li.debut;
	
	while( cour != NULL ){
		if( cour -> elmt == el ){
			avant = cour->pred;
			apres = cour->suiv;

			if( est_dernier(li, cour -> elmt) )
				li.fin = avant;

			if( est_premier(li, cour -> elmt) )
				li.debut = apres;

			if( !vide_liste(li) && !est_premier(li, cour -> elmt) && !est_dernier(li, cour -> elmt) ){
				
				if( avant != NULL )
					avant->suiv = apres;
				if( apres != NULL )
					apres->pred = avant;	
			}
			free(cour);
			break;
		}
		cour = cour->suiv;
	}

	return li;
	
}

/* Fourni la Valeur absolu de x */
int graphe_valeur_absolu(int x){

	if( x < 0 ){
		return -x;
	}

	return x;
}

Hexa graphe_groupe(Hexa sommet){
	return sommet -> aretes[6];
}


int graphe_distance_hexagones(Hexa p, Hexa q){
	int d;
	int col_1,row_1,col_2,row_2;

	col_1 = p -> sommet.col;
	row_1 = p -> sommet.row;
	col_2 = q -> sommet.col;
	row_2 = q -> sommet.row;

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

int graphe_distance_hexagone_groupe( Hexa p, Hexa graphe_groupe){

	assert(graphe_groupe != NULL);

	int d = graphe_distance_hexagones( p, graphe_groupe -> aretes[0] );

	for(int i=1; i<graphe_groupe -> nb_aretes; i++){
		if( graphe_distance_hexagones( p, graphe_groupe -> aretes[i] ) < d ){
			d = graphe_distance_hexagones( p, graphe_groupe -> aretes[i] );
		}
	}

	return d;
}


Ensemble graphe_ensemble_adjacent(Hexa u){
	Ensemble ensemble_u = Vide();

	assert( u != NULL );
	Hexa graphe_groupe = u -> aretes[6];

	if( graphe_groupe == NULL ){
		for(int i=0; i<6; i++){
			ensemble_u = Ajout(ensemble_u, u -> aretes[i]);
		}
	}
	else{
		for(int i=0; i<graphe_groupe -> nb_aretes; i++){
			for(int e=0; e<6; e++){
				ensemble_u = Ajout(ensemble_u, graphe_groupe -> aretes[i] -> aretes[e]);
			}
		}
	}

	return ensemble_u;
}


/* Fourni l'graphe_build_intersection de deux Ensemble */
Ensemble graphe_intersection(Ensemble ens_1, Ensemble ens_2){
    Ensemble ens_temp;
    int i, e;
    
    for(i=0; i<ens_1.cardinal; i++){
        for(e=0; e<ens_2.cardinal; e++){
            if( graphe_couleur_sommet( ens_1.element[i] ) == TRANSPARANT && ens_1.element[i] == ens_2.element[e] ){
                Ajout(ens_temp, ens_1.element[i] );
            }
        }
    }

    return ens_temp;
}


/**
 *	@brief cree un ensemble d'graphe_build_intersection entre un ensemble U et V.
 *
 *	@param u : un sommet qui contient l'ensemble des element adjacent a celui-ci
 *	@param v : un sommet qui contient l'ensemble des element adjacent a celui-ci
 *
 *  @return graphe_intersection : Structure qui contient un tableau contenant l'ensemble et le cardinal de cette ensemble.
 *
 */
Ensemble graphe_build_intersection(Hexa u, Hexa v){
	Ensemble ens_u = graphe_ensemble_adjacent(u);
	Ensemble ens_v = graphe_ensemble_adjacent(v);
	Ensemble intersec = graphe_intersection(ens_u, ens_v);

	printf("intersec . cardinal = %d\n", intersec . cardinal);

	return intersec;
}


bool graphe_connexion_forcer(Hexa u, Hexa v){
	Ensemble i;

	if( graphe_couleur_sommet( u ) != TRANSPARANT && graphe_couleur_sommet( u ) ==  graphe_couleur_sommet( v ) 
		&& ( u -> aretes[6] == NULL || u -> aretes[6] != v -> aretes[6] ) ){

		i = graphe_build_intersection( u, v );
		if( i . cardinal >= 2 ){
			return true;
		}
		
	}

	return false;
}

void couleur(int i, char *color){
	switch(i){
		case 0:
			strcpy(color, "black");
			break ;
		case 1:
			strcpy(color, "white");
			break ;
		case 2:
			strcpy(color, "chartreuse3");
			break ;
		case 3:
			strcpy(color, "brown2");
			break ;
		case 4:
			strcpy(color, "gold1");
			break ;
		default:
			strcpy(color, "deeppink2");
	}
}

/* -------------------------------------------- */
/*	Export the tree as a dot file				*/
/* -------------------------------------------- */

void graphe_printNode(Hexa n, FILE *file){
	
	if(n -> couleur == BLANC)
		fprintf(file, "\tn%d [style=filled, fillcolor=gold1, label=\"%d , %d\"];\n",
			n, n -> sommet.row, n -> sommet.col);
	else if(n -> couleur == NOIR)
		fprintf(file, "\tn%d [style=filled, fillcolor=navyblue, fontcolor=gold1, label=\"%d , %d\"];\n",
			n, n -> sommet.row, n -> sommet.col);
	else
		fprintf(file, "\tn%d [style=filled, fillcolor=white, label=\"%d , %d\"];\n",
			n, n -> sommet.row, n -> sommet.col);
	
	char color[20];

	for(int i=0; i<6; i++){
		if(n -> aretes[i] != NULL){
			
			if( i == 0 ){
				fprintf(file, "\t{rank=same n%d n%d}\n",
					n, n -> aretes[i]);
			}
			couleur(i, color);

			fprintf(file, "\tn%d -> n%d [penwidth = 2, label=\"%d\" color=%s]\n",
				n, n -> aretes[i], i, color);
		}
	}
}

void graphe_export_dot(Graphe g, FILE *file) {

	fprintf(file, "digraph Graphe {\n\tgraph [\n\tbgcolor= blue\n\tranksep=0.5];\n\tnode [shape = doublecircle, fon_size = 6];\n\n");
	int n = graphe_size(g);

	for(int i=0; i<n*n; i++){
		graphe_printNode(g -> tab[i], file);
	}
	
	fprintf(file, "\n}\n");
}

void graphe_dot(Graphe g, char * name){
	FILE * file = NULL;
    file = fopen(name, "w");

    printf("Creation du fichier %s en cours...\n", name);

    if( file == NULL ){
        printf("Erreur D'ouverture du fichier \n");
        exit(1);
    }

    graphe_export_dot(g , file);

    printf("Creation du fichier %s realiser avec succes !!\n", name);

    fclose(file);
} 

void graphe_chaine_daffichage(Graphe graphe, char* chaine){
	strcpy(chaine, "");
	int n = graphe_size( graphe );
	
	for( int row=0; row<n; row++ ){
		for (int i = 0; i < row; ++i)
			strcat(chaine, "  ");

		Hexa hexa = graphe -> W1 -> aretes[row];

		for( int col=0; col<n; col++ ){
			if(col == hexa -> sommet .col && row == hexa -> sommet.row){

				if( hexa->couleur == 2 )
					strcat(chaine, "<FONT COLOR=\"white\">d</FONT> ");/* transparant */
				else if( hexa->couleur == 1 )
					strcat(chaine, "<FONT COLOR=\"white\">k</FONT> ");/* Pion blanc */
				else
					strcat(chaine, "<FONT COLOR=\"black\">k</FONT> ");/* Pion noir */

				/* Passe à l'Hexagone à sa droite (colonne suivante) */
				if( col + 1 < n && hexa -> aretes[0] != NULL )
					hexa = hexa -> aretes[0];
				else
					col = n;
			}

		}
		strcat(chaine, "\n<br/>");
	}
}