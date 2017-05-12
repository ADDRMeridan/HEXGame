/*----------------------------------------------
 *Structure de Donnée Ensemble
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 11/05/2017
 *---------------------------------------------*/

#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "element.h"

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

typedef struct ensemble Ensemble;

struct ensemble{
	Element * element;
	int cardinal;
};

/* ----------------------------------
            Constructeurs
   --------------------------------*/

/**
 *	@brief Construit un Ensemble vide.
 *
 *  @return Ensemble : un ensemble Vide.
 *
 */
Ensemble Vide();

/**
 *	@brief Ajout d'un element a un ensemble.
 *
 *	@param ensemble : l'ensemble en question
 *	@param element : l'element concerner
 *
 *  @return Ensemble : un ensemble contenant un nouvele element.
 *
 */
Ensemble Ajout(Ensemble ensemble, Element element);

/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 *	@brief Verifie si un element appartient a un ensemble.
 *
 *	@param ens : l'ensemble en question
 *	@param element : l'element concerner
 *
 *  @return boolean : true si l'element est dans l'ensemble, sinon false.
 *
 */
bool Appartient(Ensemble ens, Element element);

/**
 *	@brief Verifie si un Ensemble est Vide .
 *
 *	@param ensemble : l'ensemble en question
 *
 *  @return boolean : true si l'ensemble est vide, sinon false.
 *
 */
bool Est_Vide(Ensemble ensemble);

/**
 *	@brief Donne le cardinal d'un ensemble.
 *
 *	@param ensemble : l'ensemble en question
 *
 *  @return int : entier correspondant au cardinal de l'ensemble.
 *
 */
int cardinal(Ensemble ensemble);

/**
 *	@brief Donne l'element à une certaine position de l'ensemble.
 *
 *	@param ensemble : l'ensemble en question
 *	@param position : la position de l'element dans l'ensemble, numero de l'element
 *
 *	@pre-condition  : 0 <= position < n; avec 'n' le cardinal de l'ensemble.
 *
 *  @return Element : un element correspondant a la posision donnée.
 *
 */
Element element(Ensemble ensemble, int position);



#endif
