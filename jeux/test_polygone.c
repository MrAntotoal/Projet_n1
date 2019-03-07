#include "polygones.h"

int main(){
  Points p1,p2,p3,p4;
  Vecteurs v1 ,v2;
  polygone p;
  p1=cree_point(0.0,0.0);
  p2=cree_point(2.0,0.0);
  p3=cree_point(2.0,2.0);
  p4=cree_point(0.0,2.0);
  v1=cree_vecteur_2d(2.0,2.0);
  v2=cree_vecteur_2d(-4.0,-4.0);

  p=cree_polygone_p(4,p1,p2,p3,p4);

  printf("%d\n",longueur_liste(p));
  translation_poly_vecteur(p,v1,1.0);
  afficher_point(p1);
  translation_poly_vecteur(p,v2,1.0);
  afficher_point(p1);
  exit(-1);
}
