#include "bonus.h"

typedef struct{
  int ticket_total;
  double temps_debut;
  double temps_max;
}mode_ffa;


typedef struct {
  int ticket_t1;
  int ticket_t2;
  double temps_debut;
  double temps_max;
}mode_tdm;


typedef struct {
  double temps_debut;
  double temps_max;
}mode_ffa_1_vie;


typedef mode_ffa * Mode_ffa;
typedef mode_tdm * Mode_tdm;
typedef mode_ffa_1_vie * Mode_ffa_1_vie;


Mode_ffa debut_ffa(double temps,int ticket);
Mode_tdm debut_tdm(double temps,int ticket);
Mode_ffa_1_vie debut_ffa_1_vie(double temps);


int fin_ffa(Mode_ffa m,double temps_actu);
int fin_tdm(Mode_tdm m,double temps_actu);
int fin_ffa_1(Mode_ffa_1_vie m,liste l_chars,double temps_actu);
int peux_respawn_chars(double temps_debut,double temps_att, double temps_actu);
void faire_res_all_chars(liste l_char,liste l_reap,double temps, int mode ,void * struct_mode);


void afficher_ffa(Mode_ffa m,int x,int y,TTF_Font * font,double temps_actu);
void afficher_tdm(Mode_tdm m,int x,int y,TTF_Font * font,double temps_actu);
void afficher_ffa_1(Mode_ffa_1_vie m,int x,int y,TTF_Font * font,double temps_actu,liste l_chars);

void ecrire_resultats_partie_ffa(FILE *f);
void ecrire_resultats_partie_ffa_1(FILE *f);
void ecrire_resultats_partie_tdm(FILE *f);
