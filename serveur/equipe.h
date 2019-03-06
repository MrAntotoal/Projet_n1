#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "serveur.h"
#include "analyse_lexicographique.h"
void init_equipe();

void creer_equipe(Client * c);

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num);

void quitter_equipe(Client *c);

void supprimer_equipe();

void affiche_equipe(int n);
