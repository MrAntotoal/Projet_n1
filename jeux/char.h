#include "collisions.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct{
  Points centre;
  Points devant;
  Vecteurs directionc;
  //directiont et directionb
  polygone c;//c pour chassi
  // trouelle mais apres
  //bouclier mais apres
  double degre_c;
  //idem tourelle;
  //idem shield
  double vitesse_c;
  double vitesse_rotation_c;
  //idem pour tourelle et shield
}char_3_places;

typedef char_3_places * char3p;


char3p init_char(Points centre,double largeur,double longueur);

void char_avance(char3p c);
void char_recule(char3p c);
void char_droite(char3p c);
void char_gauche(char3p c);
void afficher_char(char3p c);
void afficher_liste_chars(liste chars);
int est_en_collisions_avec_un_autre(char3p c,liste l_char);
