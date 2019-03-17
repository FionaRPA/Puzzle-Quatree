#include "quadTree.h"


int rect_contient_point(Rect r, int px, int py) {
	return r.x < px && r.x + r.l >= px && r.y < py && r.y + r.h >= py;
}


int bouton(Rect r, char* texte, Event* e) {
	
	int sourisSurvolRect = rect_contient_point(r, e->sx, e->sy);
   	
	MLV_Color bordure = sourisSurvolRect ? MLV_COLOR_RED : MLV_COLOR_WHITE;
    
	MLV_draw_text_box(
			r.x, r.y,
			r.l, r.h,
			texte,
			1,
			bordure, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
			MLV_TEXT_LEFT,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);

	return e->event == MLV_MOUSE_BUTTON && e->state == MLV_PRESSED && sourisSurvolRect;
}


void jeu(){
	
	Partie partie = {0, 0, TAILLE_IMAGE};
	Qtree quad;
	Puzzle puzzle;
	puzzle.image = NULL;

	Clic clique1;
	Clic clique2;

	int i, j;
	int jeuEnCours = 0;
	char* cheminImage;

	Event e;
	
	srand(time(NULL));
	MLV_create_window(NULL, NULL, TAILLE_IMAGE, TAILLE_IMAGE);
	
	/* Rectangles représentant les boutons du menu */
	Rect r1 = {176, 153, 160, 44};
	Rect r2 = {176, 207, 160, 44};
	Rect r3 = {176, 261, 160, 44};
	Rect r4 = {176, 315, 160, 44};
	Rect r5 = {176, 369, 160, 44};

	MLV_Input_box *input;
	input = MLV_create_input_box(
                176, 450,
                160, 44, 
                MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                MLV_COLOR_WHITE, "image : ");

	cheminImage = (char*) malloc(30);
	strcpy(cheminImage, "image.jpeg");
	
	
	while(1) {	
		MLV_clear_window(MLV_COLOR_BLACK);
		e.event = MLV_get_event( 
					NULL, NULL, NULL,
					&cheminImage, &input,
					&e.sx, &e.sy, NULL,
					&e.state );
		
		if (!jeuEnCours) {
			if (puzzle.image != NULL) {
				MLV_draw_image(puzzle.image, 0, 0);
			}

			else if (bouton(r1, "CHARGER IMAGE", &e)) {
				puzzle.image = MLV_load_image (cheminImage);				
				MLV_resize_image(puzzle.image, TAILLE_IMAGE, TAILLE_IMAGE);
				image_en_nuance_de_gris(puzzle.image);

				// création du quad tree a partir de l'image
				
				image_en_quadtree(puzzle.image, partie, &quad);
			
				FILE* f;
				char* nomFichier;
				nomFichier = strtok(cheminImage, "."); // enlève l'extension
				sprintf(nomFichier, "%s.quad", nomFichier);
				f = fopen(nomFichier, "w");
				quad_en_fichier(quad, f);
			}

			if (bouton(r2, "CHARGER QUAD TREE", &e)) {					
			}

			if (bouton(r3, "PUZZLE 16 PIECES", &e))
				jeuEnCours = creer_puzzle(&puzzle, 16);

			if (bouton(r4, "PUZZLE 64 PIECES", &e))
				jeuEnCours = creer_puzzle(&puzzle, 64);

			if (bouton(r5, "Quitter", &e))
				break;

			MLV_draw_input_box(input);
		}
		else {
			dessiner_image(puzzle.image, puzzle.tabGame, puzzle.nb_pieces);
			
			MLV_actualise_window();
			
			MLV_wait_mouse(&clique1.x, &clique1.y);
			MLV_wait_mouse(&clique2.x, &clique2.y);
			
			i = indice_piece_cliquee(clique1, puzzle.nb_pieces);
			j = indice_piece_cliquee(clique2,  puzzle.nb_pieces);

			echanger(&puzzle.tabGame[i], &puzzle.tabGame[j]);
			
			if (est_resolue(&puzzle)) {
				printf("puzzle résolue !");
				break;
			}
		}
		MLV_actualise_window();
	}
	
	if (puzzle.image != NULL)
		MLV_free_image(puzzle.image);
	
	MLV_free_input_box(input);
}


