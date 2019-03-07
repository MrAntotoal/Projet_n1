#include "point_vecteur.h"

int main(){
  /*Points p0,p1,p2,p3,p4;
  Vecteurs v1;
  p0=cree_point(2.0,2.5);
  p1=cree_point(1.0,1.0);
  p2=cree_point(3.0,1.0);
  p3=cree_point(3.0,4.0);
  p4=cree_point(1.0,4.0);
  v1=cree_vecteur_2d(0.0,1.0);
  rotation_points(p1,p0,90);
  rotation_points(p2,p0,90);
  rotation_points(p3,p0,90);
  rotation_points(p4,p0,90);
  rotation_points((Points)v1,p0,90);
  afficher_point(p1);
  afficher_point(p2);
  afficher_point(p3);
  afficher_point(p4);
  afficher_point(v1);
*/
  Points pa,pb,O;
  O=cree_point(0.0,0.0);
  pa=cree_point(2.0,0.0);
  pb=cree_point(1.0,1.0);
  printf("%f\n",degre_de_2_points(O,pa,pb));

  exit(0);
}
