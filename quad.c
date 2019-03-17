#include "quad.h"


Qtree allouer_quadtree(Partie partie) {
	Qtree quad = (Qtree) malloc(sizeof(Noeud));
	quad->partie = partie;
	quad->couleur = 0;

	quad->x = NULL;
	quad->y = NULL;
	quad->z = NULL;
	quad->t = NULL;

	return quad;
}


void quad_en_fichier(Qtree quad, FILE* f) {
	if (quad == NULL)
		return;

	if (quad->couleur == -1) {
		fprintf(f, "0 ");
		quad_en_fichier(quad->x, f);
		quad_en_fichier(quad->y, f);
		quad_en_fichier(quad->z, f);
		quad_en_fichier(quad->t, f);
	} 
	else {
		fprintf(f, "1 %d ", quad->couleur);
	}
}


void image_en_nuance_de_gris(MLV_Image* image) {
	int i,j;
	int gris;
	for (i = 0; i < TAILLE_IMAGE; i++){
		for(j = 0; j < TAILLE_IMAGE; j++){
			gris = pixel_en_nuance_de_gris(image, i, j);
			MLV_set_pixel_on_image (i, j, MLV_rgba(gris, gris, gris, 255), image);
		}
	}		
}



int pixel_en_nuance_de_gris(MLV_Image* image, int i, int j) {
	int r, v, b;
	MLV_get_pixel_on_image (image, i, j, &r, &v, &b, NULL);
	return (r + v + b) /3;
}

int est_partie_monochrome(MLV_Image* image, Partie partie) {
	int i, j;
	int premier_pixel = pixel_en_nuance_de_gris(image, 0, 0);
	int pixel_courant;
	for(i = 0; i < partie.taille; i++){
		for(j = 0; j < partie.taille; j++){
			pixel_courant = pixel_en_nuance_de_gris(image, i, j);
			if (premier_pixel != pixel_courant)
				return 0;
		}
	}
	return 1;
}

void quad_en_tab(Qtree quad, Qtree* tab, int* taille) {
	if (quad == NULL)
		return;

	if (quad->level == 0) {
		tab[*taille] = quad;
		*taille = *taille + 1;
	}

	quad_en_tab((quad)->x, tab, taille);
	quad_en_tab((quad)->y, tab, taille);
	quad_en_tab((quad)->z, tab, taille);
	quad_en_tab((quad)->t, tab, taille);	
}

void image_en_quadtree(MLV_Image* image, Partie partie, Qtree* quad) {
	int taille;

	*quad = allouer_quadtree(partie);
	if (est_partie_monochrome(image, partie)) {
		(*quad)->couleur = pixel_en_nuance_de_gris(image, partie.pos_x, partie.pos_y);
		return;
	}
	(*quad)->couleur = -1;

	taille = partie.taille/2;

	Partie r1 = {partie.pos_x, partie.pos_y, taille};
	Partie r2 = {partie.pos_x + taille, partie.pos_y,taille};
	Partie r3 = {partie.pos_x, partie.pos_y + taille, taille};
	Partie r4 = {partie.pos_x + taille, partie.pos_y + taille, taille};

	image_en_quadtree(image, r1, &(*quad)->x);
	image_en_quadtree(image, r2, &(*quad)->y);
	image_en_quadtree(image, r3, &(*quad)->z);
	image_en_quadtree(image, r4, &(*quad)->t);	
}

