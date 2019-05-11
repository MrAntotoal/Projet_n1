#include "resultats.h"


void enregister_char(FILE *html,char3p c){
  fprintf(html,"<td>%d</td> <td>%d</td> <td>%d</td> <td>%d</td>",
	  c->numero_char,c->kill,c->mort,c->points);
}

char3p char_qui_a_win_ffa_1(liste l_c){
  char3p c;
  while(!est_list_vide(l_c)){
    c=renvoie_sommet_liste(l_c);
    if(c->mort==0){
      return c;
    }
    l_c=liste_sans_premier(l_c);
  }
  return NULL;
}

liste liste_trier(liste l_c,int equipe){
  char3p c;
  liste l=NULL;
  while(!est_list_vide(l_c)){
    c=renvoie_sommet_liste(l_c);
    if(c->num_equipe==equipe || equipe==-1){
      l=insere_dans_liste_p(l,c);
    }
    l_c=liste_sans_premier(l_c);
  }
  return l;
}

liste insere_dans_liste_p(liste l ,char3p c){
  liste l_a;
  char3p c1;
  if(est_list_vide(l)){
    return empiler(l,c);
  }
  else{
    c1=renvoie_sommet_liste(l);
    if(c1->points>c->points){//si c'est plus petit
      l->suivant=insere_dans_liste_p(l->suivant,c);
      return l;
    }
    else{//plus grand
      l_a=(liste)alloc_mem(1,sizeof(struct_cellule));
      l_a->objet=c;
      l_a->suivant=l;
      return l_a;
    }
  }
}

void afficher_liste(liste l){
  char3p c;
  while(!est_list_vide(l)){
    c=renvoie_sommet_liste(l);
    printf("%d\n",c->points);
    l=liste_sans_premier(l);
  }
}

void enregistrer_tdm(liste l_char,FILE *html,int equipe_win){
  liste l1,l2;
  char3p c;
  l1=liste_trier(l_char,1);
  l2=liste_trier(l_char,2);

  fprintf(html, "<link rel=\"stylesheet\" type=\"text/css\" href=\"fin_game.css\">");
  fprintf(html, "<meta charset=\"UTF-8\">");
  fprintf(html, "<div class=\"container\">");

  if(equipe_win==1){
    fprintf(html,"<h1> L'équipe rouge a gagné !</h1>");
  }
  else if(equipe_win==2){
    fprintf(html,"<h1> L'équipe bleu a gagné !</h1>");
  }
  else{
    fprintf(html,"<h1> Egalité !</h1>");
  }
  fprintf(html,"<table>\n");
  fprintf(html,"<thead>\n");

  fprintf(html,"<tr>\n");

  fprintf(html,"<th colspan='4'>Equipe rouge</th>");
  fprintf(html,"<th colspan='4'>Equipe bleu</th>");

  fprintf(html,"</tr>\n");

  fprintf(html,"<tr>\n");

  fprintf(html,"<th >Numéro d'équipe</th>");
  fprintf(html,"<th >Nombre de tués</th>");
  fprintf(html,"<th >Nombre de morts</th>");
  fprintf(html,"<th >Nombre de points</th>");

  fprintf(html,"<th >Numéro d'équipe</th>");
  fprintf(html,"<th >Nombre de tués</th>");
  fprintf(html,"<th >Nombre de morts</th>");
  fprintf(html,"<th >Nombre de points</th>");

  fprintf(html,"</tr>\n");

  fprintf(html,"</thead>\n");
  fprintf(html,"<tbody>\n");

  while(!est_list_vide(l1)){
    fprintf(html,"<tr>\n");
    c=renvoie_sommet_liste(l1);
    enregister_char(html,c);
    if(!est_list_vide(l2)){
      c=renvoie_sommet_liste(l2);
      enregister_char(html,c);
      l2=liste_sans_premier(l2);
    }
    l1=liste_sans_premier(l1);
    fprintf(html,"</tr>\n");
  }

  fprintf(html,"</tbody>\n");
  fprintf(html,"</table>\n");
  fprintf(html, "</div>\n");
}

void enregistrer_ffa_1(liste l_char,FILE *html){
  liste l1;
  char3p c;
  l1=liste_trier(l_char,-1);
  c=char_qui_a_win_ffa_1(l_char);

  fprintf(html, "<link rel=\"stylesheet\" type=\"text/css\" href=\"fin_game.css\">");
  fprintf(html, "<meta charset=\"UTF-8\">");
  fprintf(html, "<div class=\"container\">");
  fprintf(html,"<h1> L'équipe gagnante est la %d !</h1>",c->numero_char);


  fprintf(html,"<table>\n");
  fprintf(html,"<thead>\n");

  fprintf(html,"<tr>\n");

  fprintf(html,"<th >Numéro d'équipe</th>");
  fprintf(html,"<th >Nombre de tués</th>");
  fprintf(html,"<th >Nombre de morts</th>");
  fprintf(html,"<th >Nombre de points</th>");

  fprintf(html,"</tr>\n");

  fprintf(html,"</thead>\n");
  fprintf(html,"<tbody>\n");

  while(!est_list_vide(l1)){
    fprintf(html,"<tr>\n");
    c=renvoie_sommet_liste(l1);
    enregister_char(html,c);
    l1=liste_sans_premier(l1);
    fprintf(html,"</tr>\n");
  }

  fprintf(html,"</tbody>\n");
  fprintf(html,"</table>\n");
  fprintf(html, "</div>");
}

void enregistrer_ffa(liste l_char,FILE *html){
  liste l1;
  char3p c;
  l1=liste_trier(l_char,-1);
  c=renvoie_sommet_liste(l1);
  fprintf(html, "<link rel=\"stylesheet\" type=\"text/css\" href=\"fin_game.css\">");
  fprintf(html, "<meta charset=\"UTF-8\">");
  fprintf(html, "<div class=\"container\">");
  fprintf(html,"<h1> L'equipe gagnante est la %d !</h1>",c->numero_char);

  fprintf(html,"<table>\n");
  fprintf(html,"<thead>\n");

  fprintf(html,"<tr>\n");

  fprintf(html,"<th >Numéro d'équipe</th>");
  fprintf(html,"<th >Nombre de tués</th>");
  fprintf(html,"<th >Nombre de morts</th>");
  fprintf(html,"<th >Nombre de points</th>");

  fprintf(html,"</tr>\n");

  fprintf(html,"</thead>\n");
  fprintf(html,"<tbody>\n");

  while(!est_list_vide(l1)){
    fprintf(html,"<tr>\n");
    c=renvoie_sommet_liste(l1);
    enregister_char(html,c);
    l1=liste_sans_premier(l1);
    fprintf(html,"</tr>\n");
  }

  fprintf(html,"</tbody>\n");
  fprintf(html,"</table>\n");
  fprintf(html, "</div>");
}
