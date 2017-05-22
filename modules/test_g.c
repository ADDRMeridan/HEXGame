#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "g.h"

int main(){
	g_initialisation(3);
	printf("%d--\n", g_size());
	g_affichage();
	return 0;
}