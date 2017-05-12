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

#endif
