#include "char.h"

char3p init_char(Points centre,double largeur,double longueur){
  char3p c3p;
  
  c3p=alloc_mem(1,sizeof(char_3_places));

  //test ?

  c3p->centre=centre;
  
  c3p->devant=cree_point(centre->x,centre->y+1);
  c3p->devant_t=cree_point(centre->x,centre->y+1);
  
  c3p->directionc=cree_vecteur_2p(c3p->centre,c3p->devant);
  c3p->directiont=cree_vecteur_2p(c3p->centre,c3p->devant_t);

  c3p->c=cree_polygone_d(4,
			 centre->x-largeur,centre->y-longueur,
			 centre->x+largeur,centre->y-longueur,
			 centre->x+largeur,centre->y+longueur,
			 centre->x-largeur,centre->y+longueur);

  c3p->t=cree_polygone_d(4,
			 centre->x+(0.5/3)*largeur,centre->y+(1/4.5)*longueur,
			 centre->x+(0.5/3)*largeur,centre->y+1.5*longueur,
			 centre->x-(0.5/3)*largeur,centre->y+1.5*longueur,
			 centre->x-(0.5/3)*largeur,centre->y+(1/4.5)*longueur);

  c3p->degre_c=0.0;
  c3p->degre_t=0.0;
  c3p->vitesse_c=0.2;
  c3p->vitesse_rotation_c=0.2;
  c3p->vitesse_rotation_t=0.2;
  
  
  return c3p;
}

void char_avance(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_t,c->directionc,c->vitesse_c);

  translation_poly_vecteur(c->c,c->directionc,c->vitesse_c);
  translation_poly_vecteur(c->t,c->directionc,c->vitesse_c);
  
}

void char_recule(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,-c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,-c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_t,c->directionc,-c->vitesse_c);
  
  translation_poly_vecteur(c->c,c->directionc,-c->vitesse_c);
  translation_poly_vecteur(c->t,c->directionc,-c->vitesse_c);
  
}


void char_droite(char3p c){
  rotation_points(c->devant,c->centre,-c->vitesse_rotation_c);
  rotation_points(c->devant_t,c->centre,-c->vitesse_rotation_c);

  re_calcule_un_vecteur(c->centre,c->devant,c->directionc);
  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_c-=c->vitesse_rotation_c;

  rotation_poly(c->c,c->centre,-c->vitesse_rotation_c);
  rotation_poly(c->t,c->centre,-c->vitesse_rotation_c);
}

void char_gauche(char3p c){
  rotation_points(c->devant,c->centre,c->vitesse_rotation_c);
  rotation_points(c->devant_t,c->centre,c->vitesse_rotation_c);
  
  re_calcule_un_vecteur(c->centre,c->devant,c->directionc);
  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);

  c->degre_c+=c->vitesse_rotation_c;

  rotation_poly(c->c,c->centre,+c->vitesse_rotation_c);
  rotation_poly(c->t,c->centre,+c->vitesse_rotation_c);
}


void tourelle_droite(char3p c){
  rotation_points(c->devant_t,c->centre,-c->vitesse_rotation_t);

  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_t-=c->vitesse_rotation_t;

  rotation_poly(c->t,c->centre,-c->vitesse_rotation_t);
}

void tourelle_gauche(char3p c){
  rotation_points(c->devant_t,c->centre,+c->vitesse_rotation_t);

  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_t+=c->vitesse_rotation_t;

  rotation_poly(c->t,c->centre,+c->vitesse_rotation_t);
}



void afficher_char(char3p c){
  polygone poly =c->c;
  Points p;
  glBegin(GL_QUADS);
  glColor3ub(255,255,255);
  while(!est_list_vide(poly)){
    p=renvoie_sommet_liste(poly);
    glVertex2d(p->x,p->y);
    poly=liste_sans_premier(poly);
  }
  glEnd();
}

void afficher_tourelle(char3p c){
  polygone poly =c->t;
  Points p;
  glBegin(GL_QUADS);
  glColor3ub(0,255,255);
  while(!est_list_vide(poly)){
    p=renvoie_sommet_liste(poly);
    glVertex2d(p->x,p->y);
    poly=liste_sans_premier(poly);
  }
  glEnd();
}

void afficher_liste_chars(liste chars){
  char3p c;
  if(!est_list_vide(chars)){
    c=renvoie_sommet_liste(chars);
    afficher_char(c);
    afficher_tourelle(c);
    afficher_liste_chars(liste_sans_premier(chars));
  }
}

int est_en_collisions_avec_un_autre(char3p c,liste l_char){
  char3p c2;
  if(!est_list_vide(l_char)){
    c2=renvoie_sommet_liste(l_char);
    if(c!=c2){
      printf("test_collision\n");
      if(polygone_dans_polygone(c->c,c2->c)||polygone_dans_polygone(c->t,c2->c)||polygone_dans_polygone(c->c,c2->t)||polygone_dans_polygone(c->t,c2->t)){
	return 1;
      }
    }
    return est_en_collisions_avec_un_autre(c,liste_sans_premier(l_char));
  }
  return 0;
}


