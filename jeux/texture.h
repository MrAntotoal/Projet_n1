#include <SDL/SDL_image.h>
#include "musique.h"


//void vertex_texture(double xv,double yv,double xtex,double ytex);
void bind_texture(GLuint t);
void desactiver_texturing();
void activer_texturing();
GLuint charger_texture( char * filename);
