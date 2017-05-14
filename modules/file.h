/*----------------------------------------------
 *Structure de Donnée File
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 12/05/2017
 *---------------------------------------------*/

#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

typedef struct node Node;
typedef struct s_file * File;

/* ----------------------------------
            Constructeurs
   --------------------------------*/

/**
 *	@brief Cree une file vide.
 *
 *  @return File : une file ne contenant aucun element.
 *
 */
File file_initialisation();

/**
 *	@brief ajoute un element (Node) a la file.
 *
 *  @return File : une file avec un nouvel element (Node).
 *
 */
File file_enfiler(File fil, Node* val);

/**
 *	@brief supprime un element (Node) a la file.
 *
 *  @return File : une file avec un element (Node) en moins (situer en tete de file).
 *
 */
Node* file_defiler(File fil);


/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 *	@brief indique si une file est pleine.
 *
 *  @return boolean : true si la file est pleine, sinon false.
 *
 */
bool file_pleine(File fil);

/**
 *	@brief indique si une file est vide.
 *
 *  @return boolean : true si la file est vide, sinon false.
 *
 */
bool file_vide(File fil);


#endif
