#include "type_fm.h"
#include "obus.h"

typedef liste action;

typedef struct{
  liste l_requette;
  liste l_char;
  liste l_obus;
  //surment d'autres
}toutes_listes;

typedef toutes_listes * t_liste;

liste ajoute_requete(requete_t rt, liste l);
void stop_requete(char numero_char,char type_action,liste l);
void boucle_de_traitement_liste_requete(t_liste tl);
liste lire_fm(int id_fm,liste l);
void envoyer_au_serveur(int id_fm,reponse_t rep);
int recuperer_id_fm();
