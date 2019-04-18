
#include "polygones.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_ttf.h>



void cree_fen(int l,int h,char * nom);
void buffer_image_0();
void go_ecran();
void affiche_poly(polygone poly, int r,int g,int b);
void ecrire_text(TTF_Font *Font, int r,int g, int b,  double x,double y, char * Text);

void ecrire_texte_taille(TTF_Font *Font, int r,int g, int b,Points p1,Points p2,Points p3,Points p4, char * Text);
