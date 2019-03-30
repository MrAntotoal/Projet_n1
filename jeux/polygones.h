#include "point_vecteur.h"
#include "file_msg.h"
#include <stdarg.h>


typedef liste polygone;


polygone cree_polygone_p(int nbr_points,Points p1,Points p2, Points p3,...);
polygone cree_polygone_d(int nbr_points,double x1,double y1,double x2,double y2,double x3,double y3,...);
void translation_poly_vecteur(polygone p,Vecteurs v,double coef);
void translation_poly_d(polygone p, double x, double y,double coef);
void rotation_poly(polygone p,Points O,double deg);
polygone union_polygones(polygone p1,polygone p2);
void afficher_polygone(polygone p);
