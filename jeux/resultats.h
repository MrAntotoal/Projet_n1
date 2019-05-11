#include "char.h"

void enregister_char(FILE *html,char3p c);
liste insere_dans_liste_p(liste l ,char3p c);
void afficher_liste(liste l);
liste liste_trier(liste l_c,int equipe);
void enregistrer_tdm(liste l_char,FILE *html,int equipe_win);
char3p char_qui_a_win_ffa_1(liste l_c);
void enregistrer_ffa_1(liste l_char,FILE *html);
void enregistrer_ffa(liste l_char,FILE *html);
