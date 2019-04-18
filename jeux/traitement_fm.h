#include "obus.h"

typedef liste action;

typedef struct{
  liste l_requette;
  liste l_char;
  liste l_obus;
  liste l_map;
  //surment d'autres
}toutes_listes;

typedef toutes_listes * t_liste;

void stop_requete(char numero_char,char type_action,liste l);
void boucle_de_traitement_liste_requete(t_liste tl);
