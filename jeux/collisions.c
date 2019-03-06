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
  printf("deg %f\n",deg);
  return deg==360.0;
}
