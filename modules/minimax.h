/*----------------------------------------------
 *Structure de Donnée Minimax
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 14/05/2017
 *---------------------------------------------*/

#ifndef MINIMAX_H
#define MINIMAX_H

#include "graphe.h"
#include "element_graphe.h"
#include "ensemble.h"

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

typedef struct minimax * Minimax;
typedef struct node Node;


/* ----------------------------------
            Constructeurs
   --------------------------------*/

/**
 *	@brief initialise un abre minimaxe.
 *
 *	@param n : taille du graphe des differente minimax_config du minimax
 *
 *  @return Minimax : un arbre avec une configuration initiale c0.
 *
 */
Minimax minimax_initialisation(int n);

/**
 *	@brief ajoute des succeseur (fils) nouvel minimax_config dans un noeud fourni.
 *
 *	@param m : le noeud concerner
 *	@param ensemble : l'ensemble contenant les nouvel minimax_config a ajouter.
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *	@pre-condition : 0 <= couleur <= 2 
 *
 *  @return Node : un noeud avec ces nouveau fils, si elle peut en avoir.
 *
 */
Node* minimax_ajout_successeur(Node* m, Ensemble ensemble, int couleur);

/**
 *	@brief construit un abre minimaxe.
 *
 *	@param m : minimax a partir du quel on shouaite construire, 
 		ajouter les nouveau Noeud.
 *	@param n : taille du graphe des differente minimax_config du minimax
 *
 *  @return Minimax : un arbre avec une configuration initiale c0.
 *
 */
Minimax minimax_build(Minimax m, int n);


/**
 *	@brief une fonction minimax_successeur qui associe à chaque 
 		conﬁguration de jeu, l’ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 *	@param minimax_config : une configaration (graphe).
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *	@pre-condition : 0 <= couleur <= 2
 *
 *  @return Ensemble : un ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 */
Ensemble minimax_successeur(Graphe minimax_config, int couleur);

/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 *	@brief fournie le graphe d'un noead
 *
 *	@param n : Noeud concerner.
 *
 */
Graphe minimax_config(Node* n);

/**
 *	@brief fournie la minimax_valeur d'un noeud
 *
 *	@param n : Noeud concerner.
 *
 */
int minimax_valeur(Node n);

/**
 *	@brief fournie le nombre de fils, d'un noeud
 *
 *	@param n : Noeud concerner.
 *
 */
int minimax_nombre_fils(Node n);

/**
 *	@brief fournie la racine d'un abre Minimax
 *
 *	@param m : arbre concerner.
 *
 */
Node* minimax_root(Minimax m);

/**
 *	@brief affiche les noeud de l'abre minimax en parcourant l'abre en largeur
 *
 *	@param abr : l'abre minimax concerner.
 *
 */
void minimax_tri_iteratif_largeur(Minimax abr);

/**
 *	@brief ecris un fichier dot de la structure d'un Noeud, corespondant 
 		a un arbre minimax il est preferable d'avoir la 
 		police de caratere "dPoly Imperial" installer sur sa machine pour utiliser, cette fonction
 		(Permet de mieux differencier les configuration)
 *
 *	@param t : le Noeud concerner
 *	@param file : le fichier dans lequel ecrire
 *
 */
void minimax_export_dot(Node* t, FILE *file);

/**
 *	@brief fourni la ligne et la colonne, corespondant a un numero de case donné
 *
 *	@param n : la taille du tableau de case concerner
 *	@param num_case : le numero de la case concerner
 *	@param ligne : ou l'on shouaite recupere la ligne
 *	@param col : ou l'on shouaite recupere la colonne
 *
 *	@return ligne, col : deux entier corespondant a la ligne et a la colonne
 */
void minimax_ligne_colonne(int n, int num_case, int *ligne, int *col);

/**
 *	@brief verifie si d'un graphe son identique
 *
 *	@param g : premier graphe
 *	@param h : second graphe
 *
 *	@return bool : true si il sont identique, sinon false
 *
 */
bool minimax_graphe_identique(Graphe g, Graphe h);


Node* minimax_search_graphe(Minimax abr, Graphe g, int nivau);

Graphe minimax_search_config_gagnant(Node* n, int valeur_gagnante);

#endif



