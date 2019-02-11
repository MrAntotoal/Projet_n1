#include "serveur.h"

Equipe GL_equipe[NB_EQUIPE_MAX];
int index_equipe;


void init_equipe(){
  index_equipe = 0;
}

void creer_equipe(Client * c){
  Equipe e;
  e.nb_joueur = 1;
  e.numj = 1;
  c->eq = e;
  GL_equipe[index_equipe] = e;
  c->numEquipe = index_equipe;
  index_equipe++;
}

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num){
  c->eq = GL_equipe[num];
  c->eq.nb_joueur++;
  c->eq.numj = c->eq.nb_joueur;
}


void quitter_equipe(Client *c){
  ;
}

void supprimer_equipe();
