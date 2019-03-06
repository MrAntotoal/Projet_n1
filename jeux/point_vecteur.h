#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
}points;

typedef points * Vecteurs;
typedef points * Points;

Points cree_point(double x, double y);
Vecteurs cree_vecteur_2d(double x,double y);
Vecteurs cree_vecteur_4d(double x1,double y1,double x2,double y2);
Vecteurs cree_vecteur_2p(Points p1,Points p2);
Points libere_points(Points p);
void appliquer_vecteur_a_point(Points p, Vecteurs v,double coef);
void translation_x(Points p, double val);
void translation_y(Points p,double val);
void translation(Points p,double val_x,double val_y);
void modifier_points(Points p,double x, double y);
void rotation_points(Points p, Points p_base,double d);
void afficher_point(Points p);
double norme_vecteur(Vecteurs v1);
double distance_2_points(Points p1,Points p2);
double produit_scalaire(Vecteurs v1,Vecteurs v2);
double degre_de_2_points(Points O ,Points A,Points B);
