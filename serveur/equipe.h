#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "serveur.h"
#include "analyse_lexicographique.h"
#include "affich.h"
#include "lobby_afficheur.h"

Equipe GL_equipe[MAX_CLIENTS];
int index_equipe;

void init_equipe();

void creer_equipe(Client * c);

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num);

void quitter_equipe(Client *c);

void supprimer_equipe(int place);

int position_equipe(Client c);

void affiche_equipe(int n);

void affiche_tt_e();
