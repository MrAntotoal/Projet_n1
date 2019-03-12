#include "char.h"

char3p init_char(Points centre,double largeur,double longueur){
  char3p c3p;
  
  c3p=alloc_mem(1,sizeof(char_3_places));

  //test ?

  c3p->centre=centre;
  c3p->devant=cree_point(centre->x,centre->y+longueur);
  c3p->directionc=cree_vecteur_2p(c3p->centre,c3p->devant);

  c3p->c=cree_polygone_d(4,
			 centre->x-largeur,centre->y-longueur,
			 centre->x+largeur,centre->y-longueur,
			 centre->x+largeur,centre->y+longueur,
			 centre->x-largeur,centre->y+longueur);

  c3p->degre_c=0.0;
  c3p->vitesse_c=1.0;
  c3p->vitesse_rotation_c=1.0;
  
  
  return c3p;
}

void char_avance(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,c->vitesse_c);

  translation_poly_vecteur(c->c,c->directionc,c->vitesse_c);
  
}

void char_recule(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,c->vitesse_c);

  translation_poly_vecteur(c->c,c->directionc,-c->vitesse_c);
  
}


void char_droite(char3p c){
  rotation_points(c->devant,c->centre,-c->vitesse_rotation_c);

  c->degre_c-=c->vitesse_rotation_c;

  rotation_poly(c->c,c->centre,-c->vitesse_rotation_c);
}

void char_gauche(char3p c){
  rotation_points(c->devant,c->centre,c->vitesse_rotation_c);

  c->degre_c+=c->vitesse_rotation_c;

  rotation_poly(c->c,c->centre,+c->vitesse_rotation_c);
}



