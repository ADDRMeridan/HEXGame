

void g_initialisation(int n);

int g_size();

int g_distance_hexagones(int row_1, int col_1, int row_2, int col_2);

void g_ajout_hexagone( int row, int colonne, int couleur);

int g_couleur_sommet(int row, int col);

bool g_chaine_gagnante( int couleur );

bool g_sommet_adjacent(int row_1, int col_1, int row_2, int col_2);

void g_affichage();

/* l'hexagone redevient transparant */
void g_supprime_hexagone( int row, int col );


bool g_vide();

/* supprime le graphe g si il est vide (vide = tout les hexagone sont transparant)*/
void g_suppression();