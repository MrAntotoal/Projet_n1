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


