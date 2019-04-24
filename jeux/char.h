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
  Points devant_b;
  Vecteurs directionc;
  Vecteurs directiont;
  Vecteurs directionb;
  //directiont et directionb
  polygone c;//c pour chassi
  polygone t;//t pour tourelle
  polygone t_pour_afficher;
  //bouclier mais apres
  double degre_c;
  double degre_t;
  double degre_b;
  //idem tourelle;
  //idem shield
  double vitesse_c;
  double vitesse_rotation_c;
  double vitesse_rotation_t;
  double vitesse_rotation_b;
  double rayon_min_b;
  double rayon_max_b;
  double largeur_b;
  //vie
  double pv;
  double pv_bouclier;
  int bouclier_active;
  double regene_bouclier;
  double temps_regene;
  double temps_stop_active;
  //les spe
  double temps_co_special_c;
  double temps_zero_special_c;
  double temps_exec_spe_c;
  double temps_max_exec_spe_c;
  int spe_peux_active_c;
  int spe_c;
  
  double temps_co_special_t;
  double temps_zero_special_t;
  int spe_peux_active_t;
  int spe_t;
  
  double temps_co_special_b;
  double temps_zero_special_b;
  int spe_peux_active_b;
  int spe_b;
  
  //idem pour tourelle et shield
}char_3_places;

typedef char_3_places * char3p;


char3p init_char(Points centre,double largeur,double longueur,char numero,char num_equipe);

void char_avance(char3p c);
void char_recule(char3p c);
void char_droite(char3p c);
void char_gauche(char3p c);
void afficher_char(char3p c,GLuint t_c);
void afficher_tourelle(char3p c,GLuint t_c,TTF_Font *font);
void afficher_liste_chars(liste chars,GLuint t_c,TTF_Font *font);
int est_en_collisions_avec_un_autre(char3p c,liste l_char);
void tourelle_droite(char3p c);
void tourelle_gauche(char3p c);

int est_collision_avec_map(char3p c,liste map);
void retirer_pv(char3p c,double pv,int id_fm);

void afficher_bouclier(char3p c);
int est_en_collision_avec_bouclier(char3p c,polygone p);

void bouclier_gauche(char3p c);
void bouclier_droite(char3p c);
void translation_char_vec(char3p c,Vecteurs v,double coef);
void regene_bouclier(char3p c,double temps_actu);
void regene_bouclier_all_char(liste chars,double temps);
void stop_bouclier(char3p c,double temps);
void activer_bouclier(char3p c);
void special_recharge(char3p c , double temps_actu,int id_fm);
void special_recharge_all_char(liste chars,double temps,int id_fm);

void test_stop_special_c(char3p c,double temps);
void test_stop_special_all_char(liste chars,double temps);

void desactive_spe_c(char3p c);
void activer_spe_c(char3p c,double temps);
