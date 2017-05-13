/*----------------------------------------------
 *Structure de Donnée Minimax
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 13/05/2017
 *---------------------------------------------*/

#ifndef MINIMAX_H
#define MINIMAX_H

#include "graphe.h"
#include "element_g.h"
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
 *	@param n : taille du graphe des differente config du minimax
 *
 *  @return Minimax : un arbre avec une configuration initiale c0.
 *
 */
Minimax inite_minimax(int n);

/**
 *	@brief ajoute des succeseur (fils) nouvel config dans un noeud fourni.
 *
 *	@param m : le noeud concerner
 *	@param ensemble : l'ensemble contenant les nouvel config a ajouter.
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *	@pre-condition : 0 <= couleur <= 2 
 *
 *  @return Node : un noeud avec ces nouveau fils, si elle peut en avoir.
 *
 */
Node* ajout_successeur(Node* m, Ensemble ensemble, int couleur);

/**
 *	@brief construit un abre minimaxe.
 *
 *	@param m : minimax a partir du quel on shouaite construire, 
 		ajouter les nouveau Noeud.
 *	@param n : taille du graphe des differente config du minimax
 *
 *  @return Minimax : un arbre avec une configuration initiale c0.
 *
 */
Minimax build(Minimax m, int n);


/**
 *	@brief une fonction successeur qui associe à chaque 
 		conﬁguration de jeu, l’ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 *	@param config : une configaration (graphe).
 *	@param couleur : la couleur que l'on shouaite associer au nouvel element, 
 		la configuration.
 *
 *	@pre-condition : 0 <= couleur <= 2
 *
 *  @return Ensemble : un ensemble des conﬁgurations accessibles 
 		en un coup.
 *
 */
Ensemble successeur(Graphe config, int couleur);

/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 *	@brief fournie le graphe d'un noead
 *
 *	@param n : Noeud concerner.
 *
 */
Graphe config(Node* n);

/**
 *	@brief fournie la valeur d'un noeud
 *
 *	@param n : Noeud concerner.
 *
 */
int valeur(Node n);

/**
 *	@brief fournie le nombre de fils, d'un noeud
 *
 *	@param n : Noeud concerner.
 *
 */
int nombre_fils(Node n);

/**
 *	@brief fournie la racine d'un abre Minimax
 *
 *	@param m : arbre concerner.
 *
 */
Node* root(Minimax m);

/**
 *	@brief affiche les noeud de l'abre minimax en parcourant l'abre en largeur
 *
 *	@param abr : l'abre minimax concerner.
 *
 */
void triIteratifMinmaxLargeur(Minimax abr);


void minimax_export_dot(Node* t, FILE *file);

#endif



