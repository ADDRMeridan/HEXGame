/*----------------------------------------------
 *Structure de Donnée Graphe
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 09/05/2017
 *---------------------------------------------*/

#ifndef GRAPHE_H
#define GRAPHE_H

/* Couleur */
#define TRANSPARANT	2
#define BLANC 		1
#define NOIR 		0

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

typedef struct s_Graphe * Graphe;
typedef struct s_hexa * Hexa;


/* ----------------------------------
            Constructeurs
   --------------------------------*/

/** 
 *  @brief Construit un Graphe Vide.
 *
 *  @param n la taille du graphe.
 *
 *  @return un Graphe de taille NxN (N = n).
 */
Graphe inite_graphe(int n);

/**
 *	@brief colorie un Hexagone (sommet).
 *
 *	@param sommet : le sommet à colorier
 *	@param couleur : la couleur de l'hexagone, 0 = NOIR; 1 = BLANC. 
 *
 *	@pre-cond : couleur = 0 ou couleur = 1 (BLANC ou NOIR ou TRANSPARANT)
 *
 *  @return un Hexa (sommet) modifier.
 *
 */
Hexa colorie_sommet(Hexa sommet, int couleur);

/**
 *	@brief ajout un hexagone de la couleur indiquer.
 *
 *	@param graphe : le Graphe au quelle on shouaite ajouter un hexagone
 *	@param row : la ligne correspondante
 *	@param colonne : la colonne correspondante
 *	@param couleur : la couleur de l'hexagone, 0 = NOIR; 1 = BLANC. 
 *
 *	@pre-cond : couleur = 0 ou couleur = 1 (BLANC ou NOIR)
	 	couleur_hexagone( graphe, row, colonne) == 2 (TRANSPARANT);
	 	la couleur de hexagone a l'emplacement [row,colonne] doit etre egale à 2 = TRANSPARANT
	 	0 <= row < size_graphe( graphe ); && 0 <= col < size_graphe( graphe );
 *
 *  @return un graphe modifier.
 *
 */
Graphe ajout_hexagone(Graphe graphe, int row, int colonne, int couleur);


Graphe graphe_reduit( Graphe graphe );

/**
 *	@brief forme un groupe si les pion son adjacent.
 *
 *	@param hex_1 : premier hexagone concerner
 *	@param hex_2 : second hexagone concerner
 *
 *  @return Hexa : deux sommet dans un groupe si adjacent, sinon deux sommet
 		distinct.
 *
 */
void ajout_dans_groupe(Hexa hex_1, Hexa hex_2);

/* ----------------------------------
            Accesseurs
   --------------------------------*/

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
 *	@brief renvoie un hexagone (sommet), d'un graphe 
 	selon la ligne et la colonne donnée.
 *
 *	@param graphe : le Graphe en question
 *	@param row : la ligne
 *	@param colonne : la colonne
 *
 *	@pre-cond : 0 <= row < size_graphe( graphe ); && 0 <= colonne < size_graphe( graphe );
 *
 *  @return Hexa : un sommet a la position [row, colonne] dans le graphe.
 *
 */
Hexa hexagone(Graphe graphe, int row, int colonne);

/**
 *	@brief indique la couleur d'un hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param hex : l'hexagone (sommet) en question
 *
 *  @return un entier ( 0, 1 ou 2 ) indiquant la couleur, : 2 = TRANSPARANT; 1 = BLANC; 0 = NOIR.
 *
 */
int couleur_sommet(Hexa hex);

/**
 *	@brief fourni le groupe d'un sommet.
 *
 *	@param sommet : le sommet en question
 *
 *  @return Hexa : un groupe (sommet) si il en a un, sinon retourne NULL.
 *
 */
Hexa groupe(Hexa sommet);

/**
 *	@brief indique la couleur d'un hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param graphe : le Graphe en question
 *	@param couleur : la couleur des hexagone des chaines voulue
 *
 *	@pre-cond : couleur = 0 ou couleur = 1, (BLANC ou NOIR)
 *
 *  @return boolean : true si la couleur est gagnante, sinon false.
 *
 */
bool chaine_gagnante(Graphe graphe, int couleur);

/**
 *	@brief : indique la distance entre deux hexagones (sommet)
 		correspond au nombre d’hexagones qui les séparent par le chemin le plus court.
 *
 *	@param p : premier hexagone
 *	@param q : second hexagone
 *
 *  @return int : un entier indiquant la distance entre les deux hexagones (p,q),
 		notez d(p,q)
 		d(p,q) = au nombre d’hexagones qui les séparent par le chemin le plus court.
 *
 */
int distance_hexagones(Hexa p, Hexa q);

/**
 *	@brief cherche la distance minimal entre un sommet et un groupe.
 *
 *	@param p : le sommet concernet
 *	@param groupe : le groupe concernet
 *
 *	@pre-condition : groupe != NULL
 *
 *  @return int : un entier corespondant a la distance minimale.
 *
 */
int distance_hexagone_groupe( Hexa p, Hexa groupe);

/**
 *	@brief indique si deux hexagone sont adjacent (se touche).
 *
 *	@param hex_1 : le premier hexagone
 *	@param hex_2 : le second hexagone 
 *
 *  @return boolean : true si il sont adjacent sinon false.
 *
 */
bool hex_adjacent(Hexa hex_1, Hexa hex_2);


void graphe_dot(Graphe g, char * name);

/* */
void affiche_sommet_hexa(Graphe graphe);

void affiche_sommet_hexa_graph(Graphe graphe);

void chaine_hexa_graph(Graphe graphe, char* chaine);


#endif
