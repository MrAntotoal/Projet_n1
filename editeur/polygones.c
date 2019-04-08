#include "polygones.h"




polygone cree_polygone_p(int nbr_points,Points p1,Points p2, Points p3,...){
  polygone poly;
  va_list params;
  Points p;
  int i;
  poly=list_vide();
  poly=insere_elem_liste(poly,p1);
  poly=insere_elem_liste(poly,p2);
  poly=insere_elem_liste(poly,p3);

  va_start(params,p3);
  for(i=3;i<nbr_points;i++){
    p=va_arg(params,Points);
    poly=insere_elem_liste(poly,p);
  }
  va_end(params);
  
  return poly;
}

polygone cree_polygone_d(int nbr_points,double x1,double y1,double x2,double y2,double x3,double y3,...){
  polygone poly;
  va_list params;
  int i;
  double x,y;
  poly=list_vide();
  poly=insere_elem_liste(poly,cree_point(x1,y1));
  poly=insere_elem_liste(poly,cree_point(x2,y2));
  poly=insere_elem_liste(poly,cree_point(x3,y3));

  va_start(params,y3);
  for(i=3;i<nbr_points;i++){
    x=va_arg(params,double);
    y=va_arg(params,double);
    poly=insere_elem_liste(poly,cree_point(x,y));
  }
  va_end(params);
  
  return poly;
  
}

void translation_poly_vecteur(polygone p,Vecteurs v,double coef){
  if(!est_list_vide(p)){
    appliquer_vecteur_a_point(renvoie_sommet_liste(p),v,coef);
    translation_poly_vecteur(liste_sans_premier(p),v,coef);
  }
}

void translation_poly_d(polygone p, double x, double y,double coef){
  if(!est_list_vide(p)){
    translation(renvoie_sommet_liste(p),x*coef,y*coef);
    translation_poly_d(liste_sans_premier(p),x,y,coef);
  }
}


void rotation_poly(polygone p,Points O,double deg){
  if(!est_list_vide(p)){
    rotation_points(renvoie_sommet_liste(p),O,deg);
    rotation_poly(liste_sans_premier(p),O,deg);
  }

}


polygone union_polygones(polygone p1,polygone p2){
  return concat_liste(p1,p2);
}

void afficher_polygone(polygone p){
  if(!est_list_vide(p)){
    afficher_point(renvoie_sommet_liste(p));
    afficher_polygone(liste_sans_premier(p));
  }
}


polygone insere_point_poly(polygone p1,Points p){
  return insere_elem_liste(p1,p);
}

