#include "equipe.h"

Equipe GL_equipe[MAX_CLIENTS];
int index_equipe;


void init_equipe(){
  index_equipe = 0;
}

void creer_equipe(Client * c){
  Equipe e;
  e.nb_joueur = 1;
  e.numj = 1;
  GL_equipe[index_equipe] = e;
  c->numEquipe = index_equipe;
  index_equipe++;
}

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num){
  /*c->eq = GL_equipe[num];
  c->eq.nb_joueur++;
  c->eq.numj = c->eq.nb_joueur;*/
}


void quitter_equipe(Client *c){
  ;
}

void supprimer_equipe();


void affiche_equipe(int n){
  printf("Chef d'équipe : %s\n",get_lexeme(GL_equipe[0].membre->pseudo));
  for (int i = 1; i < GL_equipe[0].nb_joueur; i++) {
    printf("autre%s\n",get_lexeme(GL_equipe[i].membre->pseudo));
  }
}
