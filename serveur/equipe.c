#include "equipe.h"



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
  ajouterChamps(*c);
}

/*  avec num le numéro de l'équipe dans le tableau global */
void rejoindre_equipe(Client * c, int num){
  GL_equipe[num].nb_joueur++;
  GL_equipe[num].membre[GL_equipe[num].numj] = *c;
  GL_equipe[num].numj++;
  c->numEquipe = num;
  ajouterChamps(*c);
}


void quitter_equipe(Client *c){

  int place = 0;
  for (int i = 0; i < GL_equipe[c->numEquipe].nb_joueur; i++) {
    if(GL_equipe[c->numEquipe].membre[i].pseudo == c->pseudo) break;
    place++;
  }
  for (int i = place; i < GL_equipe[c->numEquipe].nb_joueur - 1; i++) {
    GL_equipe[c->numEquipe].membre[i] = GL_equipe[c->numEquipe].membre[i + 1];
  }

  place = c->numEquipe;

  GL_equipe[c->numEquipe].nb_joueur--;
  GL_equipe[c->numEquipe].numj--;
  c->numEquipe = -1;

  if(GL_equipe[c->numEquipe].nb_joueur == 0)
  {
    supprimer_equipe(place);
  }
  index_equipe--;
  int tmp = 0;
  while (list[tmp].pseudo != c->pseudo) {
    tmp++;
  }
  for (int i = tmp; i <= nb; i++) {
    list[i] = list[i+1];
  }
  nb--;
}

void supprimer_equipe(int place){
  for (int i = place; i <= index_equipe; i++) {
    GL_equipe[i] = GL_equipe[i+1];
  }
  refresh_html();
}

int position_equipe(Client c){
  for (int i = 0; i < GL_equipe[c.numEquipe].nb_joueur; i++) {
    if(c.pseudo == GL_equipe[c.numEquipe].membre[i].pseudo)
    return i;
  }
  return -1;
}


void affiche_equipe(int n){
  #ifdef AFFICHAGE
  char *t = get_lexeme(GL_equipe[n].membre[0].pseudo);
  fprintf(stderr,"Chef d'équipe : %s\n",t);
  for (int i = 0; i < GL_equipe[n].nb_joueur; i++) {
    printf("%d : %s\n",i,get_lexeme(GL_equipe[n].membre[i].pseudo));
  }
  #endif
}

void affiche_tt_e(){
  for (int i = 0; i < index_equipe; i++) {
    affiche_equipe(i);
  }
}
