#include "polygones.h"


int main(){

  int i;
  polygone p;

  p=cree_polygone_d(5,
		  0.0,0.0,
		  2.0,2.0,
		  4.0,3.0,
		  3.0,4.0,
		  0.0,1.0);
  
  
  Vecteurs v =cree_vecteur_2d(1.0,1.0);
  
  for(i=0;i<3000000;i++){
    translation_poly_vecteur(p,v,1);
    translation_poly_d(p,1.0,1.0,1);
    rotation_poly(p,v,2);
  }
  
  scanf("%d",&i);
  exit(0);
}
