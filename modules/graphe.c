#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "graphe.h"

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
};


/*Liste*/

typedef Hexa Element;

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
Hexa colorie_sommet(Hexa hex, int couleur){
	hex -> couleur = couleur;
	return hex;
}


/* Inite Graphe */
Graphe inite_graphe(int n){
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

	/* Initialise les numero de ligne et de colonne des sommets */
	for( int row=0; row<n; row++ ){

		/* hexagone (Sommet) sur la 1er colonne de chaque ligne */
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

			colorie_sommet(hexa, TRANSPARANT);

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

/* */
int size_graphe(Graphe graphe){
	return graphe -> size;
}

/* */
int couleur_sommet(Hexa hex){
	return hex -> couleur;
}

int couleur_hexagone(Graphe graphe, int row, int colonne){
	
	Hexa hexa = graphe -> W1 -> aretes[row];

	int n = size_graphe(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );

	/* */
	for( int col=0; col<colonne; col++ ){
		hexa = hexa -> aretes[0];
	}

	/*if( couleur_sommet(hexa) == NOIR )
		printf("NOIR ");
	else if( couleur_sommet(hexa) == BLANC ){
		printf("BLAN ");
	}
	else{
		printf("TRAN ");
	}*/

	return couleur_sommet( hexa );
}

/* */
bool hex_adjacent(Hexa hex_1, Hexa hex_2){

	/* Verifie que l'une des arretes de hex_1 pointe bien vers hex_2 */
	for(int i=0; i<6; i++){

		if( hex_1 != NULL && hex_1 -> aretes[i] != NULL && hex_2 != NULL && hex_1 -> aretes[i] == hex_2 ){
			//printf("[%d,%d] Connecter au sommet [%d,%d] \n", hex_1->sommet.row, hex_1->sommet.col, hex_2->sommet.row, hex_2->sommet.col);
			return true;
		}
	}

	return false;
}

/* */
void ajout_dans_groupe(Hexa hex_1, Hexa hex_2){

	Hexa groupe = NULL;
	Hexa groupe_2;
	int nb_hexa_groupe_2;

	if( hex_1 != NULL && hex_2 != NULL && hex_adjacent(hex_1, hex_2) && couleur_sommet(hex_1) != TRANSPARANT && couleur_sommet(hex_1) == couleur_sommet(hex_2) ){
		//printf("-1\n");
		/* Si ils n'appartiennent a aucun groupe */
		if( hex_1 -> aretes[6] == NULL && hex_2 -> aretes[6] == NULL ){
			//printf("--1 c %d \n", couleur_sommet(hex_1) );
			groupe = (Hexa) malloc( sizeof(struct s_hexa) );
			assert( groupe != NULL );

			groupe -> aretes = (Hexa*) malloc( 2 * sizeof(Hexa) );
			assert( groupe -> aretes != NULL );

			groupe -> aretes[0] = hex_1;
			groupe -> aretes[1] = hex_2;

			hex_1 -> aretes[6] = groupe;
			hex_2 -> aretes[6] = groupe;

			assert( groupe -> aretes[0] != NULL );

			groupe -> nb_aretes = 2;
			groupe -> couleur = couleur_sommet(hex_1);

		}

		/* Si hex_2 est deja dans un groupe mais pas hex_1 */
		else if( hex_2 -> aretes[6] != NULL && hex_1 -> aretes[6] == NULL ){
			//printf("--2 %d \n", couleur_sommet(hex_1) );
			groupe = hex_2 -> aretes[6];

			groupe -> aretes = (Hexa*) realloc(groupe -> aretes, ( groupe -> nb_aretes + 1 ) * sizeof(Hexa) );
			assert( groupe -> aretes != NULL );

			groupe -> aretes[groupe -> nb_aretes] = hex_1;
			hex_1 -> aretes[6] = groupe;

			groupe -> nb_aretes++;
		}

		/* Si hex_1 est deja dans un groupe mais pas hex_2 */
		else if( hex_1 -> aretes[6] != NULL && hex_2 -> aretes[6] == NULL ){
			//printf("--3 %d \n", couleur_sommet(hex_1) );
			groupe = hex_1 -> aretes[6];

			groupe -> aretes = realloc(groupe->aretes, groupe -> nb_aretes+1 * sizeof(Hexa) );
			assert( groupe -> aretes != NULL );

			groupe -> aretes[groupe -> nb_aretes] = hex_2;
			hex_2 -> aretes[6] = groupe;

			groupe -> nb_aretes++;
		}

		/* Si hex_1 et hex_2 sont deja dans un groupe */
		else if( hex_1 -> aretes[6] != NULL && hex_2 -> aretes[6] != NULL && hex_2 -> aretes[6] != hex_1 -> aretes[6]){
			//printf("--4\n");
			/* Privilégie le groupe de plus grande taille */
			if( hex_1 -> aretes[6] -> nb_aretes > hex_2 -> aretes[6] -> nb_aretes ){
				groupe = hex_1 -> aretes[6];
				groupe_2 = hex_2 -> aretes[6];
			}
			else{
				groupe = hex_2 -> aretes[6];
				groupe_2 = hex_1 -> aretes[6];
			}

			nb_hexa_groupe_2 = groupe_2 -> nb_aretes;

			groupe -> aretes = (Hexa*) realloc(groupe -> aretes, ( groupe -> nb_aretes + groupe_2 -> nb_aretes ) * sizeof(Hexa) );
			assert( groupe -> aretes != NULL );

			/* Ajout des element du groupe 2 dans le groupe 1 */
			for( int i=groupe -> nb_aretes; i<( groupe -> nb_aretes + groupe_2 -> nb_aretes ); i++ ){
				groupe -> aretes[i] = groupe_2 -> aretes[i - groupe -> nb_aretes];
				groupe -> aretes[i] -> aretes[6] = groupe;
			}

			/* Suppression du groupe 2 */
			for( int i=groupe_2 -> nb_aretes-1; i>=0; i-- ){
				groupe_2 -> aretes[i] = NULL;
				free( groupe_2 -> aretes[i] );
			}
			groupe_2 = NULL;
			free( groupe_2 );

			groupe -> nb_aretes += nb_hexa_groupe_2;
		}

	}
	//printf("-2-\n");
}


/* */
Graphe ajout_hexagone( Graphe graphe, int row, int colonne, int couleur){

	Hexa hexa = graphe->W1->aretes[row];

	int n = size_graphe(graphe);

	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );
	assert( couleur == NOIR || couleur == BLANC );

	/* */
	for( int col=0; col<colonne; col++ ){
		hexa = hexa->aretes[0];
	}


	assert( couleur_sommet( hexa ) == TRANSPARANT );
	hexa = colorie_sommet(hexa, couleur);

	for(int i=0; i<6; i++)
		ajout_dans_groupe( hexa, hexa -> aretes[i] );
	
	//printf("[%d,%d] \n", hexa->sommet.row, hexa->sommet.col);
	

	return graphe;

}


bool chaine_gagnante(Graphe graphe, int couleur){

	int n = size_graphe( graphe );
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

	/* Verifie que le bord_1 appartient à un meme groupe que le bord_2 Exemple w1 et w2 sont dans un meme groupe */
	while( i<n && !gagnant ){

		if( bord_1->aretes[i]->aretes[6] != NULL ){

			e = 0;

			while( e<n && !gagnant ){

				if( bord_2 -> aretes[e] -> aretes[6] != NULL && bord_2 -> aretes[e] -> aretes[6] == bord_1 -> aretes[i] -> aretes[6] )
					gagnant = true;

				e++;
			}
		}
		
		i++;
	}

	return gagnant;
}
		

Hexa groupe_en_sommet_unique(Graphe graphe, Hexa groupe){
	Hexa sommet_unique;
	Hexa grp = groupe;
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
		if(	(grp) -> aretes[i] -> sommet . col  == size_graphe(graphe)-1 ){
			graphe -> W2 -> aretes[ ((grp) -> aretes[i] -> sommet . row) ] = sommet_unique;
		}
		if(	(grp) -> aretes[i] -> sommet . col  == 0 ){
			graphe -> W1 -> aretes[ ((grp) -> aretes[i] -> sommet . row) ] = sommet_unique;
		}
		if( (grp) -> aretes[i] -> sommet . row  == size_graphe(graphe)-1 ){
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

				/* Liberation de la memoire sur les arretes des sommets du groupe */
				(grp) -> aretes[i] -> aretes[e] = NULL;
				free( (grp) -> aretes[i] -> aretes[e] );
				
			}
		}
		//printf("\n");
	}

	/* Liberation de la memoire sur les sommets du groupe */
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

	int n = size_graphe( graphe );
	
	for( int row=0; row<n; row++ ){

		Hexa hexa = g -> W1 -> aretes[row];

		for( int col=0; col<n; col++ ){
			if(hexa != NULL && col == hexa -> sommet.col && row == hexa -> sommet.row){
				if( hexa -> aretes[6] != NULL && hexa -> nb_aretes == 6 )
					hexa = groupe_en_sommet_unique(g ,(hexa -> aretes[6]) );
				
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
void affiche_sommet_hexa(Graphe graphe){

	int n = size_graphe( graphe );
	
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


void affiche_sommet_hexa_graph(Graphe graphe){

	int n = size_graphe( graphe );
	
	for( int row=0; row<n; row++ ){
		for (int i = 0; i < row; ++i)
			printf(" ");

		Hexa hexa = graphe -> W1 -> aretes[row];

		for( int col=0; col<n; col++ ){
			if(col == hexa -> sommet .col && row == hexa -> sommet.row){

				if( hexa->couleur == 2 )
					printf("T    ", hexa -> sommet.row, hexa -> sommet.col);
				else if( hexa->couleur == 1 )
					printf("B    ", hexa -> sommet.row, hexa -> sommet.col);
				else
					printf("N    ", hexa -> sommet.row, hexa -> sommet.col);

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

Hexa hexagone(Graphe graphe, int row, int colonne){
	
	Hexa hexa = graphe -> W1 -> aretes[row];

	int n = size_graphe(graphe);
	assert( row >= 0 && row < n && colonne >= 0 && colonne < n );

	/* */
	for( int col=0; col<colonne; col++ ){
		hexa = hexa -> aretes[0];
	}

	return hexa;
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

/* Valeur absolu */
int val_abs(int x){

	if( x < 0 ){
		return -x;
	}

	return x;

}

/**
 *	@brief cherche la distance minimal entre deux sommet.
 *
 *	@param p : le 1er sommet concernet
 *	@param q : le 2nd sommet concernet
 *
 *  @return int : un entier corespondant a la distance minimale.
 *
 */
int distance_hexagones(Hexa p, Hexa q){
	int d;
	int col_1,row_1,col_2,row_2;

	col_1 = p -> sommet.col;
	row_1 = p -> sommet.row;
	col_2 = q -> sommet.col;
	row_2 = q -> sommet.row;

	if( col_1 == col_2 || row_1 == row_2 )
	{	/* Meme ligne ou meme colonne */
		d = val_abs(row_1 - row_2) + val_abs(col_1 - col_2);
	}
	else if( val_abs(row_1 - row_2) == val_abs(col_1 - col_2) )
	{	/* Si diagonale */
		if( ( row_1 > row_2 && col_1 < col_2 ) || ( row_1 < row_2 && col_1 > col_2 ) ){
			d = val_abs(col_1 - col_2);
		}
		else{
			d = val_abs(col_1 - col_2) * 2;
		}
	}
	else
	{	/* Autre */
		if( ( row_1 > row_2 && col_1 < col_2 ) || ( row_1 < row_2 && col_1 > col_2 ) ){
			if( val_abs(col_1 - col_2) > val_abs(row_1 - row_2) ){
				d = val_abs(col_1 - col_2);
			}
			else{
				d = val_abs(row_1 - row_2);
			}
		}
		else{
			d = val_abs(col_1 - col_2) + val_abs(row_1 - row_2);
		}
	}

	return (d + 1);
}


int distance_hexa(Graphe graphe, int row_1, int col_1, int row_2, int col_2){
	Hexa p = hexagone( graphe, row_1, col_1);
	Hexa q = hexagone( graphe, row_2, col_2);

	return distance_hexagones( p, q);
}

/**
 *	@brief cherche la distance minimal entre un sommet et un groupe.
 *
 *	@param p : le sommet concernet
 *	@param groupe : le groupe concernet
 *
 *  @return int : un entier corespondant a la distance minimale.
 *
 */
int distance_hexagone_groupe( Hexa p, Hexa groupe){
	int d = distance_hexagones( p, groupe -> aretes[0] );

	for(int i=1; i<groupe -> nb_aretes; i++){
		if( distance_hexagones( p, groupe -> aretes[i] ) < d ){
			d = distance_hexagones( p, groupe -> aretes[i] );
		}
	}

	return d;
}


/* Ensemble */

typedef struct ensemble Ensemble;

struct ensemble{
	Hexa * element;
	int cardinal;
};

Ensemble Vide(){
    Ensemble ens;
    ens . element = (Hexa*) malloc( sizeof( Hexa ) );
	assert( ens . element != NULL );

    ens.cardinal = 0;
    return ens;
}

bool Appartient(Ensemble ens, Hexa el){
    int i;
    for(i=0; i<ens.cardinal; i++){
        if( el == ens.element[i] ){
            return true;
        }
    }
    
    return false;
}

/*Ajout d'un element a un ensemble*/
Ensemble Ajout(Ensemble ensemble, Hexa element){

    if( !Appartient(ensemble, element) ){
    	ensemble.element = (Hexa*) realloc(ensemble.element, ( ensemble.cardinal + 1 ) * sizeof(Hexa) );
    	assert( ensemble.element != NULL );

        ensemble.element[ ensemble.cardinal ] = element;
        ensemble.cardinal++;
    }

    return ensemble;
}


/*Verifie si un Ensemble est Vide */
bool Est_Vide(Ensemble ens){
    return ( ens.cardinal == 0 );
}

Ensemble ensemble_adjacent(Hexa u){
	Ensemble ensemble_u = Vide();

	assert( u != NULL );
	Hexa groupe = u -> aretes[6];

	if( groupe == NULL ){
		for(int i=0; i<6; i++){
			ensemble_u = Ajout(ensemble_u, u -> aretes[i]);
		}
	}
	else{
		for(int i=0; i<groupe -> nb_aretes; i++){
			for(int e=0; e<6; e++){
				ensemble_u = Ajout(ensemble_u, groupe -> aretes[i] -> aretes[e]);
			}
		}
	}

	return ensemble_u;
}

/*Fourni l'intersection de deux Ensemble*/
Ensemble Intersection(Ensemble ens_1, Ensemble ens_2){
    Ensemble ens_temp;
    int i, e;
    
    for(i=0; i<ens_1.cardinal; i++){
        for(e=0; e<ens_2.cardinal; e++){
            if( ens_1.element[i] == ens_2.element[e] ){
                Ajout(ens_temp, ens_1.element[i] );
            }
        }
    }

    return ens_temp;
}


/**
 *	@brief cree un ensemble d'intersection entre un ensemble U et V.
 *
 *	@param u : un sommet qui contient l'ensemble des element adjacent a celui-ci
 *	@param v : un sommet qui contient l'ensemble des element adjacent a celui-ci
 *
 *  @return Intersection : Structure qui contient un tableau contenant l'ensemble et le cardinal de cette ensemble.
 *
 */
Ensemble intersection(Hexa u, Hexa v){
	Ensemble ens_u = ensemble_adjacent(u);
	Ensemble ens_v = ensemble_adjacent(v);
	Ensemble intersec = Intersection(ens_u, ens_v);

	printf("intersec . cardinal = %d\n", intersec . cardinal);

	return intersec;
}



bool connexion_forcer(Hexa u, Hexa v){
	Ensemble i;

	if( couleur_sommet( u ) ==  couleur_sommet( v ) && ( u -> aretes[6] == NULL || u -> aretes[6] != v -> aretes[6] ) ){
		i = intersection( u, v );
		if( i . cardinal >= 2 ){
			return true;
		}
		
	}

	return false;
}