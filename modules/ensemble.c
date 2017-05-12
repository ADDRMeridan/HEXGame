/*----------------------------------------------
 *Auteur : MOHAMED Mourdas
 *Dêpendance : element
 *Date de modification : 11/05/2017
 *---------------------------------------------*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "ensemble.h"

/* Ensemble */

typedef struct ensemble Ensemble;

Ensemble Vide(){
    Ensemble ens;
    ens . element = (Element*) malloc( sizeof( Element ) );
    assert( ens . element != NULL );

    ens.cardinal = 0;
    return ens;
}

bool Appartient(Ensemble ens, Element el){
    int i;
    for(i=0; i<ens.cardinal; i++){
        if( el == ens.element[i] ){
            return true;
        }
    }
    
    return false;
}

/*Ajout d'un element a un ensemble*/
Ensemble Ajout(Ensemble ensemble, Element element){

    if( !Appartient(ensemble, element) ){
        ensemble.element = (Element*) realloc(ensemble.element, ( ensemble.cardinal + 1 ) * sizeof(Element) );
        assert( ensemble.element != NULL );

        ensemble.element[ ensemble.cardinal ] = element;
        ensemble.cardinal++;
    }

    return ensemble;
}

bool Est_Vide(Ensemble ens){
    return ( ens.cardinal == 0 );
}

int cardinal(Ensemble ensemble){
    return ensemble.cardinal;
}

Element element(Ensemble ensemble, int position){
    assert(position >= 0 && position < ensemble.cardinal);

    return ensemble . element[position];
}



