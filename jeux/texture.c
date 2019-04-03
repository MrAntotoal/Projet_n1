#include "texture.h"

void activer_texturing(){
  glEnable(GL_TEXTURE_2D);
}

void desactiver_texturing(){
  glDisable(GL_TEXTURE_2D);
}

void bind_texture(Texture t){
  glBindTexture(GL_TEXTURE_2D,*t);
}

void vertex_texture(double xv,double yv,double xtex,double ytex){
  glTexCoord2d(xtex,ytex);
  glVertex2d(xv,yv);
}

Texture charger_texture(char * chemin,char * nom){
  Texture t;
  t=alloc_mem(1,sizeof(texture));
  t->loadTexture(chemin);
  strcpy(t->nom_texture,nom);
  return t;
}
