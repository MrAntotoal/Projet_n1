#include "type_fm.h"
#include "collisions.h"

typedef liste action;

liste ajoute_requete(requete_t rt, liste l);
void stop_requete(char numero_char,char type_action,liste l);
liste boucle_de_traitement_liste_requete(liste l);
liste lire_fm(int id_fm,liste l);
void envoyer_au_serveur(int id_fm,reponse_t rep);
int recuperer_id_fm();
