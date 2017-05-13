#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "minimax.h"
#include "file.h"

#define MAX 500

struct s_file{
	Node* file[MAX];
	int size;
};

File initeFile(){
	File file = (File) malloc( sizeof( struct s_file ) );
	assert(file != NULL);
	
	file -> size = 0;
	return file;
}

bool filePleine_2(File fil){
	return fil -> size == MAX;
}

bool fileVide_2(File fil){
	return fil -> size == 0;
}

File enfiler_2(File fil, Node* val){

	assert( !filePleine_2(fil) );

	fil -> file[ fil -> size ] = val;
	fil -> size++;

	return fil;
}

Node* defiler_2(File fil){

	assert( !fileVide_2(fil) );

	Node* val = fil -> file[0];
	
	/* Decalage */
	for(int i=0; i<fil -> size - 1; i++)
		fil -> file[i] = fil -> file[i+1];

	fil -> size--;

	return val;
}