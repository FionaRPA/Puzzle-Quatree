#include "puzzle.h"


void decouper(MLV_Image* image, Qtree* quad, int nb_pieces) {
	Partie partie = {0, 0, TAILLE_IMAGE};
    int level = nb_piece_en_level(nb_pieces);
	decouper_auxiliaire(image, partie, quad, level);
}

void dessiner_image(MLV_Image* image, Qtree* tab, int nb_pieces) {
	int x, y, i = 0;
	int t = tab[0]->partie.taille;
	int pieces_en_lignes = sqrt(nb_pieces);
	for (x = 0; x < pieces_en_lignes; x++) {
		for (y = 0; y < pieces_en_lignes; y++) {
            MLV_draw_partial_image(image, tab[i]->partie.pos_x, tab[i]->partie.pos_y, tab[i]->partie.taille, tab[i]->partie.taille, t * y, t * x);
			i++;
		}
	}
}


void echanger(Qtree *a, Qtree *b) {
	Qtree tmp = *a;
	*a = *b;
	*b = tmp;
}

void melanger_tab(Qtree* tab, int taille) {
	int i, j;
	for (i = 0; i < taille - 1; i++) {
		j = rand() % taille;
		echanger(&tab[i], &tab[j]);
	}
}


int est_resolue(Puzzle* puzzle) {
   	int i;
   	Partie a, b;
	for(i = 0; i < puzzle->nb_pieces; i++) {
		a = puzzle->tabFirst[i]->partie;
		b = puzzle->tabGame[i]->partie;
		if (!( a.pos_x == b.pos_x && a.pos_y == b.pos_y && a.taille == b.taille))
			return 0;
	}
	return 1; 
}


int indice_piece_cliquee(Clic clique, int nbpiece) {
	int r = sqrt(nbpiece);
	clique.x /= (TAILLE_IMAGE / r);
	clique.y /= (TAILLE_IMAGE / r);
	return clique.x + (nbpiece / r) * clique.y;
}


int nb_piece_en_level(int nb_piece) {
	int i = 0 ;
	while (nb_piece > 0) {
		nb_piece /= 4;
		i++;
	}
	return i-1;
}


void decouper_auxiliaire(MLV_Image* image, Partie partie, Qtree* quad, int level) {	
	*quad = allouer_quadtree(partie);
	(*quad)->level = level;

	if (level > 0) {
		int taille = partie.taille/2;

		Partie r1 = {partie.pos_x, partie.pos_y, taille};
		Partie r2 = {partie.pos_x + taille, partie.pos_y,taille};
		Partie r3 = {partie.pos_x, partie.pos_y + taille, taille};
		Partie r4 = {partie.pos_x + taille, partie.pos_y + taille, taille};

		decouper_auxiliaire(image, r1, &(*quad)->x, level - 1);
		decouper_auxiliaire(image, r2, &(*quad)->y, level - 1);
		decouper_auxiliaire(image, r3, &(*quad)->z, level - 1);
		decouper_auxiliaire(image, r4, &(*quad)->t, level - 1);
	}
}


int creer_puzzle(Puzzle* puzzle, int nb_pieces) {
    if (puzzle->image == NULL)
        return 0;

    int taille;
    puzzle->nb_pieces = nb_pieces;
    decouper(puzzle->image, &puzzle->quad, puzzle->nb_pieces);
    
    taille = 0;
    quad_en_tab(puzzle->quad, puzzle->tabFirst, &taille);
    
    taille = 0;
    quad_en_tab(puzzle->quad, puzzle->tabGame, &taille);	
    
    melanger_tab(puzzle->tabGame, puzzle->nb_pieces);

    return 1;
}
