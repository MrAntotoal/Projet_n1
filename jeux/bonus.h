#include "reap.h"


typedef struct {
  polygone p;
  int type;
}bonus;

typedef bonus* Bonus;

void bonus_conducteur(char3p c);
void bonus_tireur(char3p c);
void bonus_bouclier(char3p c);


liste faire_spawn_bonus(liste l_chars,liste l_bonus,liste liste_bonus_actif);


void afficher_liste_bonus(liste l_bonus);

int char_touche_bonus(char3p c,Bonus b);
liste char_touche_liste_bonus(char3p c,liste l_bonus);
liste all_char_liste_bonus(liste l_char , liste l_bonus);
