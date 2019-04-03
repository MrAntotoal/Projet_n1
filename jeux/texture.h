#include "sdlglutils.h"
#include "polygone.h"

typedef struct{
  GLuint text;
  char nom_texture[500];
}texture;

typedef texture * Texture;

Texture charger_texture(char * chemin,char * nom);
void vertex_texture(double xv,double yv,double xtex,double ytex);
void bind_texture(Texture t);
void desactiver_texturing();
void activer_texturing();
