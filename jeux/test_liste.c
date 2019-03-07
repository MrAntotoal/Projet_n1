#include "liste.h"
#include "point_vecteur.h"


int main(){
  Points p1,p2,p3;
  liste l;
  p1=cree_point(1.0,1.0);
  p2=cree_point(2.0,2.0);
  p3=cree_point(3.0,3.0);

  l=list_vide();
  l=insere_elem_liste(l,p1);

  p2=renvoie_sommet_liste(l);

  afficher_point(p1);
  afficher_point(p2);
  afficher_point(p3);

  exit(0);
}
