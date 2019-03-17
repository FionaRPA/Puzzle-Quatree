#ifndef __QUADTREE__H
#define __QUADTREE__H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "quad.h"
#include "puzzle.h"


typedef struct {
	int x;
	int y;
    int l;
    int h;
} Rect;


typedef struct event {
	MLV_Event event;
	MLV_Button_state  state;
	int sx;
	int sy;
} Event;


int rect_contient_point(Rect r, int px, int py);


int bouton(Rect r, char* texte, Event* e);


void jeu();



#endif