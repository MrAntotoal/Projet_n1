#include "affichage.h"


void cree_fen(int l,int h,char * nom){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(nom,NULL);
  SDL_SetVideoMode(l,h,32,SDL_OPENGL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,2048,0,1080);
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

void ecrire_text(TTF_Font *Font, int r,int g, int b,  double x,double y, char * Text) {
  /*Create some variables.*/
  SDL_Color Color = {255, 255, 255};
  SDL_Surface *Message = TTF_RenderText_Blended(Font, Text, Color);
  unsigned Texture = 0;
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  /*Generate an OpenGL 2D texture from the SDL_Surface*.*/
  glGenTextures(1, &Texture);
  glBindTexture(GL_TEXTURE_2D, Texture);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);

  /*Draw this texture on a quad with the given xyz coordinates.*/
 
  glBindTexture(GL_TEXTURE_2D, Texture); 
  glColor3ub(r,g,b);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex2d(x, y);
  glTexCoord2d(1, 1); glVertex2d(x+Message->w, y);
  glTexCoord2d(1, 0); glVertex2d(x+Message->w, y+Message->h);
  glTexCoord2d(0, 0); glVertex2d(x, y+Message->h);
  glEnd();

  /*Clean up.*/
  glDeleteTextures(1, &Texture);
  SDL_FreeSurface(Message);
}


void ecrire_texte_taille(TTF_Font *Font, int r,int g, int b,Points p1,Points p2,Points p3,Points p4, char * Text) {
  /*Create some variables.*/
  SDL_Color Color = {255, 255, 255};
  SDL_Surface *Message = TTF_RenderText_Blended(Font, Text, Color);
  unsigned Texture = 0;
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  /*Generate an OpenGL 2D texture from the SDL_Surface*.*/
  glGenTextures(1, &Texture);
  glBindTexture(GL_TEXTURE_2D, Texture);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);

  /*Draw this texture on a quad with the given xyz coordinates.*/
 
  glBindTexture(GL_TEXTURE_2D, Texture); 
  glColor3ub(r,g,b);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex2d(p1->x,p1->y);
  glTexCoord2d(1, 1); glVertex2d(p2->x,p2->y);
  glTexCoord2d(1, 0); glVertex2d(p3->x,p3->y);
  glTexCoord2d(0, 0); glVertex2d(p4->x,p4->y);
  glEnd();

  

  /*Clean up.*/
  glDeleteTextures(1, &Texture);
  SDL_FreeSurface(Message);
}
