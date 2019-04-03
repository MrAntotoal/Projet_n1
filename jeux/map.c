#include "map.h"

Obstacle cree_obstacle(int type,polygone p){
  Obstacle o;
  o=alloc_mem(1,sizeof(obstacle));
  o->p=p;
  o->type=type;
  return o;
}

Zone cree_zone(polygone zone,liste l_obstacle){
  Zone z;
  z=alloc_mem(1,sizeof(zone));
  z->p_zone=zone;
  z->l_obstacle=l_obstacle;
  return z;
}


void afficher_obstacle(Obstacle o){
  polygone poly=o->p;
  Points p;
  glBegin(GL_QUADS);
  glColor3ub(255,0,0);
  while(!est_list_vide(poly)){
    p=renvoie_sommet_liste(poly);
    glVertex2d(p->x,p->y);
    poly=liste_sans_premier(poly);
  }
  glEnd();
}

void afficher_zone(liste l_obs){
  liste l=l_obs;
  while(!est_list_vide(l)){
    afficher_obstacle(renvoie_sommet_liste(l));
    l=liste_sans_premier(l);
  }
}


void afficher_map(liste all_zone){
  liste l;
  Zone z;
  l=all_zone;
  while(!est_list_vide(l)){
    z=renvoie_sommet_liste(l);
    afficher_zone(z->l_obstacle);
    l=liste_sans_premier(l);
  }
}
