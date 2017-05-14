/*----------------------------------------------
 *Structure de Donnée File
 *
 *Auteur : MOHAMED Mourdas
 *Date de modification : 12/05/2017
 *---------------------------------------------*/


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "file.h"

#define MAX 50000

typedef struct node Node;

struct s_file{
	Node* file[MAX];
	int size;
};

File file_initialisation(){
	File file = (File) malloc( sizeof( struct s_file ) );
	assert(file != NULL);
	
	file -> size = 0;
	return file;
}

bool file_pleine(File fil){
	return fil -> size == MAX;
}

bool file_vide(File fil){
	return fil -> size == 0;
}

File file_enfiler(File fil, Node* val){

	assert( !file_pleine(fil) );

	fil -> file[ fil -> size ] = val;
	fil -> size++;

	return fil;
}

Node* file_defiler(File fil){

	assert( !file_vide(fil) );

	Node* val = fil -> file[0];
	
	/* Decalage */
	for(int i=0; i<fil -> size - 1; i++)
		fil -> file[i] = fil -> file[i+1];

	fil -> size--;

	return val;
}