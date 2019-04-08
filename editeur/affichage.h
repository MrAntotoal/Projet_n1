
#include "polygones.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


void cree_fen(int l,int h,char * nom);
void buffer_image_0();
void go_ecran();
void affiche_poly(polygone poly, int r,int g,int b);

void afficher_liste_point(liste l_p,int r,int g,int b);
void afficher_point_large(Points p,int r,int g,int b);
void afficher_poly_trait(polygone p,int r , int g , int b);
void afficher_liste_poly_trait(liste l_p,int r, int g ,int b);
void afficher_contour_select(Points p,int r,int g,int b);
