#include "affichage.h"


void cree_fen(int l,int h,char * nom){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(nom,NULL);
  SDL_SetVideoMode(l,h,32,SDL_OPENGL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100,2148,-100,1180);
}


void buffer_image_0(){
  glClear(GL_COLOR_BUFFER_BIT);
}

void go_ecran(){
  glFlush();
  SDL_GL_SwapBuffers();
}


void affiche_poly(polygone poly, int r,int g,int b){
  Points p;
  glBegin(GL_QUADS);
  glColor3ub(r,g,b);
  while(!est_list_vide(poly)){
    p=renvoie_sommet_liste(poly);
    glVertex2d(p->x,p->y);
    poly=liste_sans_premier(poly);
  }
  glEnd();
}

void afficher_liste_point(polygone l_p,int r,int g,int b){
  Points p;
  if(!est_list_vide(l_p)){
    p=renvoie_sommet_liste(l_p);
    afficher_point_large(p,r,g,b);
    afficher_liste_point(liste_sans_premier(l_p),r,g,b);
  }
}

void afficher_point_large(Points p,int r,int g,int b){
  glBegin(GL_QUADS);
  glColor3ub(r,g,b);
  glVertex2d(p->x-10,p->y-10);
  glVertex2d(p->x-10,p->y+10);
  glVertex2d(p->x+10,p->y+10);
  glVertex2d(p->x+10,p->y-10);
  glEnd();
}

void afficher_contour_select(Points p,int r,int g,int b){
  glBegin(GL_LINE_LOOP);
  glColor3ub(r,g,b);
  glVertex2d(p->x-10,p->y-10);
  glVertex2d(p->x-10,p->y+10);
  glVertex2d(p->x+10,p->y+10);
  glVertex2d(p->x+10,p->y-10);
  glEnd();
}

void afficher_poly_trait(polygone p,int r , int g , int b){
  Points po;
  polygone p2=p;
  afficher_liste_point(p,r,g,b);
  glBegin(GL_LINE_LOOP);
  while(!est_list_vide(p2)){
    po=renvoie_sommet_liste(p2);
    glVertex2d(po->x,po->y);
    p2=liste_sans_premier(p2);
  }
  glEnd();
}

void afficher_liste_poly_trait(liste l_p,int r, int g ,int b){
  polygone p;
  if(!est_list_vide(l_p)){
    p=renvoie_sommet_liste(l_p);
    afficher_poly_trait(p,r,g,b);
    afficher_liste_point(p,r,g,b);
    afficher_liste_poly_trait(liste_sans_premier(l_p),r,g,b);
  }
}

