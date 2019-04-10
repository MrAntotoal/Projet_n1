#include "texture.h"

void activer_texturing(){
  glEnable(GL_TEXTURE_2D);
}

void desactiver_texturing(){
  glDisable(GL_TEXTURE_2D);
}

void bind_texture(GLuint t){
  glBindTexture(GL_TEXTURE_2D,t);
}

void vertex_texture(double xv,double yv,double xtex,double ytex){
  glTexCoord2d(xtex,ytex);
  glVertex2d(xv,yv);
}


GLuint charger_texture( char * filename){
  GLuint text_inter;
  SDL_Surface *texture;
  
  
  texture=IMG_Load(filename);
  if(texture==NULL){
    fprintf(stderr,"erreur chargement texture %s \n",filename);
  }
  
  glGenTextures(1,&text_inter);
  glBindTexture(GL_TEXTURE_2D,text_inter);

  
  int mode=GL_RGB;

  if(texture->format->BytesPerPixel==4){
    mode=GL_RGBA;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glTexImage2D(GL_TEXTURE_2D,0,mode,texture->w,texture->h,0,mode,GL_UNSIGNED_BYTE,texture->pixels);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

  SDL_FreeSurface(texture);
  return text_inter;
}

