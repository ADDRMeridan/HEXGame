#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "minimax.h"
#include "file_2.h"

#define MAX 50

struct s_file_2{
	Node* file[MAX];
	int size;
};

File_2 initeFile_2(){
	File_2 file = (File_2) malloc( sizeof( struct s_file_2 ) );
	assert(file != NULL);
	
	file -> size = 0;
	return file;
}

bool filePleine_2(File_2 fil){
	return fil -> size == MAX;
}

bool fileVide_2(File_2 fil){
	return fil -> size == 0;
}

File_2 enfiler_2(File_2 fil, Node* val){

	assert( !filePleine_2(fil) );

	fil -> file[ fil -> size ] = val;
	fil -> size++;

	return fil;
}

Node* defiler_2(File_2 fil){

	assert( !fileVide_2(fil) );

	Node* val = fil -> file[0];
	
	/* Decalage */
	for(int i=0; i<fil -> size - 1; i++)
		fil -> file[i] = fil -> file[i+1];

	fil -> size--;

	return val;
}