#include "reap.h"

int char_peux_reap_ici(char3p c1 ,Points p,liste l_char){
  Vecteurs v1;
  char3p c;
  v1=cree_vecteur_2p(c1->centre,p);


  liste l=l_char;
  while(!est_list_vide(l)){
    c=renvoie_sommet_liste(l);
    if(distance_2_points(p,c->centre)<=150){
      return 0;
    }
    l=liste_sans_premier(l);
  }

  translation_char_vec(c1,v1,1.0);
   
  libere_points(v1);
  return 1;
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
      rotation_char_deg(c,rand()%360);
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



void respawn_char(liste l_reap,liste l_char,char3p c,double temps){
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
      remise_a_zero_char(c,temps);
      rotation_char_deg(c,rand()%360);
      return;
    }
    i++;
    
  }
  
}
