#ifndef FILE_2_H
#define FILE_2_H

#include <stdbool.h>
#include "minimax.h"

typedef struct s_file_2 * File_2;

File_2 initeFile_2();

bool filePleine_2(File_2 fil);

bool fileVide_2(File_2 fil);

File_2 enfiler_2(File_2 fil, Node* val);

Node* defiler_2(File_2 fil);

#endif
