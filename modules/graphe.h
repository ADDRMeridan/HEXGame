#ifndef GRAPHE_H
#define GRAPHE_H


/* Couleur */
#define TRANSPARANT 2
#define BLANC 		1
#define NOIR 		0


typedef struct s_Graphe * Graphe;


/** 
 *  @brief Construit un Graphe Vide.
 *
 *  @param n la taille du graphe.
 *
 *  @return un Graphe de taille NxN (N = n).
 */
Graphe inite_graphe(int n);

/**
 *	@brief ajout un hexagone de la couleur indiquer.
 *
 *	@param graphe : le Graphe au quelle on shouaite ajouter un hexagone
 *	@param row : la ligne correspondante
 *	@param colonne : la colonne correspondante
 *	@param couleur : la couleur de l'hexagone, 0 = NOIR; 1 = BLANC. 
 *
 *	@axiome : couleur = 0 ou couleur = 1 (BLANC ou NOIR)
	 	couleur_hexagone( graphe, row, colonne) == 2 (TRANSPARANT);
	 	la couleur de hexagone a l'emplacement [row,colonne] doit etre egale à 2 = TRANSPARANT
	 	0 <= row < size_graphe( graphe ); && 0 <= col < size_graphe( graphe );
 *
 *  @return un graphe modifier.
 *
 */
Graphe ajout_hexagone(Graphe graphe, int row, int colonne, int couleur);

/**
 *	@brief indique la taille d'un Graphe.
 *
 *	@param graphe : le Graphe au quelle on shouaite connaitre la taille
 *
 *  @return un entier indiquant la taille.
 *
 */
int size_graphe(Graphe graphe);

/**
 *	@brief indique la couleur d'un hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param graphe : le Graphe en question
 *	@param row : la ligne
 *	@param colonne : la colonne
 *
 *	@axiome : 0 <= row < size_graphe( graphe ); && 0 <= col < size_graphe( graphe );
 *
 *  @return un entier ( 0, 1 ou 2 ) indiquant la couleur, : 2 = TRANSPARANT; 1 = BLANC; 0 = NOIR.
 *
 */
int couleur_hexagone(Graphe graphe, int row, int colonne);

/**
 *	@brief indique la couleur d'un hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param graphe : le Graphe en question
 *	@param couleur : la couleur des hexagone des chaines voulue
 *
 *	@axiome : couleur = 0 ou couleur = 1, (BLANC ou NOIR)
 *
 *  @return boolean : true si la couleur est gagnante, sinon false.
 *
 */
bool chaine_gagnante(Graphe graphe, int couleur);


Graphe graphe_reduit( Graphe graphe );


int distance_hexa(Graphe graphe, int row_1, int col_1, int row_2, int col_2);

/* */
void affiche_sommet_hexa(Graphe graphe);

void affiche_sommet_hexa_graph(Graphe graphe);


#endif
