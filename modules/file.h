#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include "minimax.h"

typedef struct s_file * File;

File initeFile();

bool filePleine_2(File fil);

bool fileVide_2(File fil);

File enfiler_2(File fil, Node* val);

Node* defiler_2(File fil);

#endif
