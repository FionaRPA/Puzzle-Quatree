#ifndef __PUZZLE__H
#define __PUZZLE__H

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "quad.h"


typedef struct {
	int x;
	int y;
} Clic;

/*réprésente les données d'un puzzle */
typedef struct {
	MLV_Image* image;
	int nb_pieces;
	int level;
	Qtree quad;
    /* tableau contenant les noeuds de l'image mélangée */
	Qtree tabGame[64];
    /* tableau contenant les noeuds de l'image d'origine */
	Qtree tabFirst[64];
} Puzzle;



/* crée un puzzle de nbpieces éléments et retourne 1 en cas de succès et 0 sinon */
int creer_puzzle(Puzzle* puzzle, int nb_pieces);


/* déssine l'image représentée par le quadtree en paramètre */
void dessiner_image(MLV_Image* image, Qtree* tab, int nb_pieces);


/* mélange les noeuds du tableau */
void melanger_tab(Qtree* tab, int taille);

/* 
    retourne un nombre entier représentant le level (dans 
    la représentation d'une image par un quadtree) 
    qui contient nb_pieces noeuds.

    Par exemple nb_piece_en_level(16) renvoie 2
  */
int nb_piece_en_level(int nb_piece);

/*
    retourne un nombre entier correspondant à l'indice de la pièce cliquée
    dans un tableau à 'nbpiece' éléments.

    Cette fonction retourne la formule x + y * sqrt(nbpiece); 
    avec x valant clique.x / (TAILLE_IMAGE / sqrt(nbpiece))
    et y clique.y / (TAILLE_IMAGE / sqrt(nbpiece)).
*/
int indice_piece_cliquee(Clic clique, int nbpiece);

/* 
    découpe l'image en 4 sous parties tant que le level est plus grand que 0.
    La valeur de level diminue de 1 à chaque appel récursive de la fonction.
    et le nombre d'élément du quadtree se multiplie par 4.
 */
void decouper_auxiliaire(MLV_Image* image, Partie partie, Qtree* quad, int level);

/* échange 2 noeuds */
void echanger(Qtree *a, Qtree *b);

/* découpe l'image donnée en paramètre en nb_pieces éléments */
void decouper(MLV_Image* image, Qtree* quad, int nb_pieces);

/* 
    retourne une valeur indiquant si le puzzle 
    en paramètre est résolue
*/
int est_resolue(Puzzle* puzzle);



#endif
