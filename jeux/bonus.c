#include "bonus.h"

///le last pd

void libere_bonus(Bonus b){
  libere_liste_point(b->p);
  libere(b);
}

liste all_char_liste_bonus(liste l_char , liste l_bonus){
  liste l=l_char;
  char3p c;
  while(!est_list_vide(l)){
    c=renvoie_sommet_liste(l);
    l_bonus=char_touche_liste_bonus(c,l_bonus);
    l=liste_sans_premier(l);
  }
  return l_bonus;
}

liste char_touche_liste_bonus(char3p c,liste l_bonus){
  liste l=l_bonus;
  Bonus b;
  while(!est_list_vide(l)){
    b=renvoie_sommet_liste(l);
    if(char_touche_bonus(c,b)){
      switch(b->type){
      case 1:
	bonus_conducteur(c);
	break;
      case 2:
	bonus_tireur(c);
	break;
      case 3:
	bonus_bouclier(c);
	break;
      }
      //suppr
      l=liste_sans_premier(l);
      l_bonus=supprime_elem(l_bonus,b);
      libere_bonus(b);
    }
    else{
      l=liste_sans_premier(l);
    }
    //actu
  }
  return l_bonus;
}

int char_touche_bonus(char3p c,Bonus b){
  return( polygone_dans_polygone(c->c,b->p) ||polygone_dans_polygone(c->t,b->p));
}

void bonus_conducteur(char3p c){
  c->vitesse_c*=1.25;
  c->vitesse_rotation_c*=1.25;
}

void bonus_tireur(char3p c){
  c->temps_de_tire/=0.75;
}

void bonus_bouclier(char3p c){
  c->largeur_b*=1.25;
  c->regene_bouclier*=1.25;
}

void afficher_bonus(Bonus b,GLuint t_b){
  Points p;
  switch(b->type){
  case 1:
    glColor3ub(255,140,0);
    break;
  case 2:
    glColor3ub(255,0,0);
    break;
  case 3:
    glColor3ub(0,0,255);
    break;
  }
  activer_texturing();
  bind_texture(t_b);
  glBegin(GL_QUADS);
  p=get_index(0,b->p);
  glTexCoord2d(0,0);glVertex2d(p->x,p->y);

  
  p=get_index(1,b->p);
  glTexCoord2d(0,1);glVertex2d(p->x,p->y);

  
  p=get_index(2,b->p);
  glTexCoord2d(1,1);glVertex2d(p->x,p->y);

  
  p=get_index(3,b->p);
  glTexCoord2d(1,0);glVertex2d(p->x,p->y);
  glEnd();
  desactiver_texturing();
}

void afficher_liste_bonus(liste l_bonus,GLuint t_b){
  Bonus b;
   while(!est_list_vide(l_bonus)){
    b=renvoie_sommet_liste(l_bonus);
    afficher_bonus(b,t_b);
    l_bonus=liste_sans_premier(l_bonus);
  }
 
}

Bonus cree_bonus(int type,Points p){
  Bonus b;
  b=alloc_mem(sizeof(bonus),1);
  b->type=type;
  b->p=cree_polygone_d(4,
		       p->x-10,p->y-10,
		       p->x-10,p->y+10,
		       p->x+10,p->y+10,
		       p->x+10,p->y-10);
  return b;
}


int bonus_peux_ici(Points p,liste l_char){
  //ici il faut que je fasse le reste 
  char3p c;
  double rayon =200.0;
  liste l=l_char;
   while(!est_list_vide(l)){
    c=renvoie_sommet_liste(l);
    if(distance_2_points(p,c->centre)>=rayon){
      return 1;
    }
    l=liste_sans_premier(l);
  }
  
  return 0;
}


liste faire_spawn_bonus(liste l_chars,liste l_bonus,liste liste_bonus_actif){
  int len;
  len=longueur_liste(l_bonus);
  int deb,i,ok;
  deb=rand()%len;
  ok=0;
  i=0;
  while(!ok){
    if(i>=len){
      ok=1;
    }
    if(bonus_peux_ici(get_index((i+deb)%len,l_bonus),l_chars)){
      liste_bonus_actif=empiler(liste_bonus_actif,cree_bonus(1+(rand()%3),get_index((i+deb)%len,l_bonus)));
      return liste_bonus_actif;
    }
    i++;
  }
  return liste_bonus_actif;
}





