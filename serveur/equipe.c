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
  GL_equipe[index_equipe].membre[0] = *c;
  index_equipe++;
  printf("Création OK\n");
}

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num){
  GL_equipe[num].nb_joueur++;
  GL_equipe[num].membre[GL_equipe[num].numj] = *c;
  GL_equipe[num].numj++;
  c->numEquipe = num;
  printf("equipe rejointe %d\n",num);
}


void quitter_equipe(Client *c){
  GL_equipe[c->numEquipe].nb_joueur--;
  GL_equipe[c->numEquipe].numj--;
  c->numEquipe = -1;
}

void supprimer_equipe();


void affiche_equipe(int n){
  char *t = get_lexeme(GL_equipe[n].membre[0].pseudo);
  fprintf(stderr,"Chef d'équipe : %s\n",t);
  for (int i = 0; i < GL_equipe[n].nb_joueur; i++) {
    printf("%d : %s\n",i,get_lexeme(GL_equipe[n].membre[i].pseudo));
  }
}
