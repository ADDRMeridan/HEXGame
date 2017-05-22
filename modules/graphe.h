/*----------------------------------------------
 *Structure de Donnée Graphe
 *Dêpendance : ensemble
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
Graphe graphe_initialisation(int n);

/**
 *	@brief colorie un Hexagone (sommet).
 *
 *	@param sommet : le sommet à colorier
 *	@param couleur : la couleur de l'graphe_hexagone, 0 = NOIR; 1 = BLANC. 
 *
 *	@pre-cond : couleur = 0 ou couleur = 1 (BLANC ou NOIR ou TRANSPARANT)
 *
 *  @return un Hexa (sommet) modifier.
 *
 */
Hexa graphe_colorie_sommet(Hexa sommet, int couleur);

/**
 *	@brief ajout un graphe_hexagone de la couleur indiquer.
 *
 *	@param graphe : le Graphe au quelle on shouaite ajouter un graphe_hexagone
 *	@param row : la ligne correspondante
 *	@param colonne : la colonne correspondante
 *	@param couleur : la couleur de l'graphe_hexagone, 0 = NOIR; 1 = BLANC. 
 *
 *	@pre-cond : couleur = 0 ou couleur = 1 (BLANC ou NOIR)
	 	graphe_couleur_hexagone( graphe, row, colonne) == 2 (TRANSPARANT);
	 	la couleur de graphe_hexagone a l'emplacement [row,colonne] doit etre egale à 2 = TRANSPARANT
	 	0 <= row < graphe_size( graphe ); && 0 <= col < graphe_size( graphe );
 *
 *  @return un graphe modifier.
 *
 */
Graphe graphe_ajout_hexagone(Graphe graphe, int row, int colonne, int couleur);

/**
 *	@brief Supprime un graphe si il est vide(tout les pion son transparent).
 *
 *	@param graphe : le graphe concerner
 *
 *  @axiome : graphe_suppression(graphe_initialisation(n)) -> NULL;
 		graphe_suppression(graphe_ajout_hexagone(g, row, col, coul)) ->  g = graphe_ajout_hexagone(g, row, col, coul);
 *
 */
void graphe_suppression(Graphe *graphe);

/**
 *	@brief Fournie un graphe reduit.
 *
 *	@param graphe : le graphe concerner
 *
 *  @return Graphe : un graphe reduit.
 *
 */
Graphe graphe_reduit( Graphe graphe );

/**
 *	@brief forme un groupe si les pion son adjacent.
 *
 *	@param hex_1 : premier graphe_hexagone concerner
 *	@param hex_2 : second graphe_hexagone concerner
 *
 *  @return Hexa : deux sommet dans un groupe si adjacent, sinon deux sommet
 		distinct.
 *
 */
void graphe_ajout_dans_groupe(Hexa hex_1, Hexa hex_2);

/**
 *	@brief supprime un hexagone (le colrie en transparant, et le supprime de son groupe si il en existe un) 
 		a l'emplacement ligne colonne indiqué.
 *
 *	@param graphe : le Graphe en question
 *	@param row : la ligne
 *	@param colonne : la colonne
 *
 *	@pre-cond : 0 <= row < graphe_size( graphe ); && 0 <= colonne < graphe_size( graphe );
 *
 *  @return Graphe : le graphe avec un sommet tranparant (hexagone supprimé) en plus ou pas.
 *
 */
Graphe graphe_supprime_hexagone( Graphe graphe, int row, int col );



/* ----------------------------------
            Accesseurs
   --------------------------------*/

bool graphe_vide(Graphe graphe);

/**
 *	@brief indique la taille d'un Graphe.
 *
 *	@param graphe : le Graphe au quelle on shouaite connaitre la taille
 *
 *  @return un entier indiquant la taille.
 *
 */
int graphe_size(Graphe graphe);

/**
 *	@brief renvoie un graphe_hexagone (sommet), d'un graphe 
 	selon la ligne et la colonne donnée.
 *
 *	@param graphe : le Graphe en question
 *	@param row : la ligne
 *	@param colonne : la colonne
 *
 *	@pre-cond : 0 <= row < graphe_size( graphe ); && 0 <= colonne < graphe_size( graphe );
 *
 *  @return Hexa : un sommet a la position [row, colonne] dans le graphe.
 *
 */
Hexa graphe_hexagone(Graphe graphe, int row, int colonne);

/**
 *	@brief indique la couleur d'un graphe_hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param hex : l'graphe_hexagone (sommet) en question
 *
 *  @return un entier ( 0, 1 ou 2 ) indiquant la couleur, : 2 = TRANSPARANT; 1 = BLANC; 0 = NOIR.
 *
 */
int graphe_couleur_sommet(Hexa hex);

/**
 *	@brief fourni le groupe d'un sommet.
 *
 *	@param sommet : le sommet en question
 *
 *  @return Hexa : un groupe (sommet) si il en a un, sinon retourne NULL.
 *
 */
Hexa graphe_groupe(Hexa sommet);

/**
 *	@brief indique la couleur d'un graphe_hexagone se trouvant dans un 
 	Graphe à un certain emplacement.
 *
 *	@param graphe : le Graphe en question
 *	@param couleur : la couleur des graphe_hexagone des chaines voulue
 *
 *	@pre-cond : couleur = 0 ou couleur = 1, (BLANC ou NOIR)
 *
 *  @return boolean : true si la couleur est gagnante, sinon false.
 *
 */
bool graphe_chaine_gagnante(Graphe graphe, int couleur);

/**
 *	@brief : indique la distance entre deux hexagones (sommet)
 		correspond au nombre d’hexagones qui les séparent par le chemin le plus court.
 *
 *	@param p : premier graphe_hexagone
 *	@param q : second graphe_hexagone
 *
 *  @return int : un entier indiquant la distance entre les deux hexagones (p,q),
 		notez d(p,q)
 		d(p,q) = au nombre d’hexagones qui les séparent par le chemin le plus court.
 *
 */
int graphe_distance_hexagones(Hexa p, Hexa q);

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
int graphe_distance_hexagone_groupe( Hexa p, Hexa groupe);

/**
 *	@brief indique si deux graphe_hexagone sont adjacent (se touche).
 *
 *	@param hex_1 : le premier graphe_hexagone
 *	@param hex_2 : le second graphe_hexagone 
 *
 *  @return boolean : true si il sont adjacent sinon false.
 *
 */
bool graphe_sommet_adjacent(Hexa hex_1, Hexa hex_2);


/**
 *	@brief ecris un fichier dot de la structure d'un Graphe.
 *
 *	@param g : le Graphe concerner
 *	@param name : le nom du fichier dans lequel ecrire
 *
 */
void graphe_dot(Graphe g, char * name);

/**
 *	@brief Affiche chaque coordonée ligne colonne corespondant 
 		au element d'un graphe.
 *
 *	@param graphe : le Graphe à afficher
 *
 */
void graphe_affiche_row_col_sommet(Graphe graphe);

/**
 *	@brief Affiche chaque element d'un graphe sous forme de lettre
 		coresponndant à leur couleur.
 *
 *	@param graphe : le Graphe à afficher
 *
 */
void graphe_affichage(Graphe graphe);

/**
 *	@brief fournie une chaine d'affichage d'un graphe (pour le module minimax)
 *
 *	@param graphe : le Graphe conecerné
 *	@param chaine : la chaine à modifier
 *
 *	@return char* chaine : une chaine corespondant a un affichage du graphe
 *
 */
void graphe_chaine_daffichage(Graphe graphe, char* chaine);



bool graphe_connexion_forcer(Hexa u, Hexa v);

#endif
