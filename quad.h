#ifndef __QUAD__H
#define __QUAD__H

#include "stdlib.h"
#include <MLV/MLV_all.h>


#define TAILLE_IMAGE 512

typedef struct Partie {
	int pos_x;
	int pos_y;
	int taille;
} Partie;


typedef struct noeud {
	int couleur;
	int level;
	Partie partie;
	struct noeud* x;
	struct noeud* y;
	struct noeud* z;
	struct noeud* t;
} Noeud, *Qtree;


Qtree allouer_quadtree(Partie partie);

/* retourne 1 si les pixels de l'image dans la région donnée sont de la même couleur 0 sinon */
int est_partie_monochrome(MLV_Image* image, Partie partie);

/* crée un quadtree à partir de l'image en paramètre */
void image_en_quadtree(MLV_Image* image, Partie partie, Qtree* quad);

/* transforme l'image donnée en nuance de gris */
void image_en_nuance_de_gris(MLV_Image* image);


/* retourne le level de gris représentant le pixel (i, j) de l'image */
int pixel_en_nuance_de_gris(MLV_Image* image, int i, int j);

/*	place tout les noeuds de level 0 de 'quad' dans 'tableau'
    et stocke la taille du tableau dans 'taille'
*/
void quad_en_tab(Qtree quad, Qtree* tab, int* taille);


/* crée un fichier représentant le quadtree en paramètre */
void quad_en_fichier(Qtree quad, FILE* f);

#endif
