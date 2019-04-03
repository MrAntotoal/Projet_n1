#include "char.h"
#define TAILLE_X_O 4
#define TAILLE_Y_O 2

typedef struct  {
  char3p tireur;
  double dmg;
  Vecteurs direction;
  double vitesse;
  Points centre;
  polygone p;
  float dega;
}obus;

typedef obus * Obus;

Obus cree_obus(char3p c);
void obus_avance(Obus o);
int obus_touche_cible(Obus o,liste liste_char,int id_fm);

liste traitement_tous_obus(liste l_obus,liste l_char,liste l_zone,int id_fm);
