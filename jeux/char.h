#include "sauvegarde.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct{
  char numero_char;
  char num_equipe;
  Points centre;
  Points devant;
  Points devant_t;
  Vecteurs directionc;
  Vecteurs directiont;
  //directiont et directionb
  polygone c;//c pour chassi
  polygone t;//t pour tourelle
  polygone t_pour_afficher;
  //bouclier mais apres
  double degre_c;
  double degre_t;
  //idem tourelle;
  //idem shield
  double vitesse_c;
  double vitesse_rotation_c;
  double vitesse_rotation_t;

  //vie
  double pv;
  //idem pour tourelle et shield
}char_3_places;

typedef char_3_places * char3p;


char3p init_char(Points centre,double largeur,double longueur,char numero,char num_equipe);

void char_avance(char3p c);
void char_recule(char3p c);
void char_droite(char3p c);
void char_gauche(char3p c);
void afficher_char(char3p c,GLuint t_c);
void afficher_tourelle(char3p c,GLuint t_c);
void afficher_liste_chars(liste chars,GLuint t_c);
int est_en_collisions_avec_un_autre(char3p c,liste l_char);
void tourelle_droite(char3p c);
void tourelle_gauche(char3p c);

int est_collision_avec_map(char3p c,liste map);
void retirer_pv(char3p c,double pv,int id_fm);
