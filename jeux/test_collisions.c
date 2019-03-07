#include "collisions.h"


int main(){
  Points p0,p1;
  polygone poly,poly2;
  p0=cree_point(1.5486,0.543245);
  p1=cree_point(6.0,1.5);
  poly=cree_polygone_d(4,0.0,0.0,20.0,0.0,20.0,20.0,0.0,20.0);
  printf("%d\n",point_dans_polygone(p0,poly));
  poly2=cree_polygone_d(5,4.0,1.0,6.0,0.0,8.0,1.0,5.0,2.0);
  printf("%d\n",polygone_dans_polygone(poly,poly2));
  printf("%d\n",point_dans_polygone(p1,poly2));
  exit(0);
}
