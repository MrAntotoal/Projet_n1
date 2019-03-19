#include "collisions.h"


int point_dans_poly_bis(Points p,polygone poly,Points premier_list,Points p0,double deg){
  Points p1;
  if(est_list_vide(poly)){
    return deg +=degre_de_2_points(p,p0,premier_list);
  }
  else{
    p1=renvoie_sommet_liste(poly);
    return point_dans_poly_bis(p,liste_sans_premier(poly),premier_list,p1,deg+degre_de_2_points(p,p0,p1));
  }
}


int point_dans_polygone(Points p,polygone poly){
  /*360 deg somme angles*/

  double deg=0;

  deg=point_dans_poly_bis(p,liste_sans_premier(poly),renvoie_sommet_liste(poly),renvoie_sommet_liste(poly),0);
  //printf("deg %f\n",deg);
  return deg==360.0;
}

int polygone_dans_polygone_bis(polygone poly0,polygone poly1){
  if(est_list_vide(poly0)){
    return 0;
  }
  else{
    //afficher_point(renvoie_sommet_liste(poly0));
    if(point_dans_polygone(renvoie_sommet_liste(poly0),poly1)){
      return 1;
    }
    return polygone_dans_polygone_bis(liste_sans_premier(poly0),poly1);
  }
}

int polygone_dans_polygone(polygone poly0,polygone poly1){
  if(polygone_dans_polygone_bis( poly0, poly1)){
    return 1;
  }
  return polygone_dans_polygone_bis( poly1, poly0);
}




