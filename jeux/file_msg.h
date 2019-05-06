#include "type_fm.h"
#include "liste.h"

liste ajoute_requete(requete_t rt, liste l);
liste lire_fm(int id_fm,liste l);
void envoyer_au_serveur(int id_fm,reponse_t rep);
int recuperer_id_fm();
