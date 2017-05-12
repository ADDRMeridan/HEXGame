#ifndef MINIMAX_H
#define MINIMAX_H

#include "graphe.h"
#include "element_g.h"
#include "ensemble.h"

typedef struct minimax * Minimax;
typedef struct node Node;

Minimax inite_minimax(int n);

Ensemble successeur(Graphe config, int couleur);

Graphe config(Node* n);

int valeur(Node n);

int nombre_configuration(Node n);

Node* ajout_successeur(Node* m, Ensemble ensemble, int couleur);

Node* minimax_suivant(Node n, int numero_branche);

Node* root(Minimax m);

Minimax build(Minimax m, int n);

void triIteratifMinmaxLargeur(Minimax abr);

#endif



