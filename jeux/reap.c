#include "reap.h"

int char_peux_reap_ici(char3p c ,Points p,liste l_char){
  Vecteurs v1;
  v1=cree_vecteur_2p(c->centre,p);

  translation_char_vec(c,v1,1.0);
  if(!est_en_collisions_avec_un_autre(c,l_char)){
    libere_points(v1);
    return 1;
  }
  translation_char_vec(c,v1,-1.0);
  libere_points(v1);
  return 0;
}

void spawn_char(liste l_reap,liste l_char,char3p c){
  int len;
  len=longueur_liste(l_reap);
  int deb,i,ok;
  deb=rand()%len;
  ok=0;
  i=0;
  while(!ok){
    if(i>=len){
      ok=1;
    }
    if(char_peux_reap_ici(c,
			  get_index((i+deb)%len,l_reap),
			  l_char)){
      return;
    }
    i++;
    
  }
  
  
}

void spawn_all_tank(liste l_reap,liste l_char){
  liste l_c=l_char;
  char3p c;
  while(!est_list_vide(l_c)){
    c=renvoie_sommet_liste(l_c);
    spawn_char(l_reap,l_char,c);
    l_c=liste_sans_premier(l_c);
  }
  
}
