#include "collisions.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct{
  Points centre;
  Points devant;
  Points devant_t;
  Vecteurs directionc;
  Vecteurs directiont;
  //directiont et directionb
  polygone c;//c pour chassi
  polygone t;//t pour tourelle
  //bouclier mais apres
  double degre_c;
  double degre_t;
  //idem tourelle;
  //idem shield
  double vitesse_c;
  double vitesse_rotation_c;
  double vitesse_rotation_t;
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
void tourelle_droite(char3p c);
void tourelle_gauche(char3p c);
