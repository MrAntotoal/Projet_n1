#include "mode_de_jeux.h"

Mode_ffa debut_ffa(double temps,int ticket){
  Mode_ffa m;
  m=alloc_mem(sizeof(mode_ffa),1);
  m->ticket_total=ticket;
  m->temps_debut=temps;
  m->temps_max=60.0*10.0;//en sec 10 min
  return m;
}


Mode_tdm debut_tdm(double temps,int ticket){
  Mode_tdm m;
  m=alloc_mem(sizeof(mode_tdm),1);
  m->ticket_t1=ticket;
  m->ticket_t2=ticket;
  m->temps_debut=temps;
  m->temps_max=60.0*10.0;//en sec 10 min
  printf("debut %d\n",m->ticket_t1);
  return m;
}

Mode_ffa_1_vie debut_ffa_1_vie(double temps){
  Mode_ffa_1_vie m;
  m=alloc_mem(sizeof(mode_ffa_1_vie),1);
  m->temps_debut=temps;
  m->temps_max=60.0*10.0;//en sec 10 min
  return m;
}

int nombre_chars(liste l_chars){
  return longueur_liste(l_chars);
}

int nombre_en_vie(liste l_chars){
  char3p c;
  int n=0;
  
  while(!est_list_vide(l_chars)){
    c=renvoie_sommet_liste(l_chars);
    if(c->pv>0){
      n++;
    }
    l_chars=liste_sans_premier(l_chars);
  }
  return n;
}

int fin_ffa(Mode_ffa m,double temps_actu){
  if(temps_actu>m->temps_debut+m->temps_max){
    return 1;
  }
  if(m->ticket_total<=0){
    return 1;
  }
  
  return 0;
}



int fin_tdm(Mode_tdm m,double temps_actu){
  if(temps_actu>m->temps_debut+m->temps_max){
    return 4;//time out
  }
  if(m->ticket_t1<=0 || m->ticket_t2<=0){//c la fin
    if(m->ticket_t1< m->ticket_t2){
      return 2;//team 2 win
    }
    if(m->ticket_t1> m->ticket_t2){
      printf("fin %d\n",m->ticket_t1);
      return 1;//team 1 win
    }
    if(m->ticket_t1==m->ticket_t2){
      return 3;//egalité
    }
    
  }
  return 0;
}

int fin_ffa_1(Mode_ffa_1_vie m,liste l_chars,double temps_actu){
  if(temps_actu>m->temps_debut+m->temps_max){
    return 1;
  }
  if(nombre_en_vie(l_chars)==1){
    return 1;
  }
  if(nombre_en_vie(l_chars)==0){
    return 3;//personne;
  }
  return 0; 
}


int peux_respawn_chars(double temps_debut,double temps_att, double temps_actu){
  return temps_debut+temps_att<=temps_actu;
}

void faire_res_all_chars(liste l_char,liste l_reap,double temps, int mode ,void * struct_mode){
  char3p c;
  Mode_ffa m1;
  Mode_tdm m2;
  liste l =l_char;
  if(mode==1){
    m1=struct_mode;
  }
  if(mode==2){
    m2=struct_mode;
  }
  
  while(!est_list_vide(l_char)){
    c=renvoie_sommet_liste(l_char);
    if(c->pv<=0){
      respawn_char(l_reap,l,c,temps);
      if(mode ==1){//ffa
	m1->ticket_total-=1;
      }
      if(mode ==2 ){//tdm
	if(c->num_equipe==1){
	  m2->ticket_t1-=1;
	}
	else{
	  m2->ticket_t2-=1;
	}
      }
    }
    l_char=liste_sans_premier(l_char);
  }
  
}

void afficher_ffa(Mode_ffa m,int x,int y,TTF_Font * font,double temps_actu){
  char t[100];
  sprintf(t,"tickets restants : %d",m->ticket_total);
  ecrire_text(font,255,255,255,x-270,y,t);


  sprintf(t,"temps restants : %f",m->temps_debut+m->temps_max-temps_actu);
  ecrire_text(font,255,255,255,x+270,y,t);
}

void afficher_tdm(Mode_tdm m,int x,int y,TTF_Font * font,double temps_actu){
  char t[100];
  ecrire_text(font,255,255,255,x-400,y,"tickets :");
  
  sprintf(t,"rouge : %d",m->ticket_t1);
  ecrire_text(font,255,0,0,x-200,y,t);

  sprintf(t,"bleu : %d",m->ticket_t2);
  ecrire_text(font,0,0,255,x+100,y,t);

  
  sprintf(t,"temps restants : %f",m->temps_debut+m->temps_max-temps_actu);
  ecrire_text(font,255,255,255,x+400,y,t);
}
void afficher_ffa_1(Mode_ffa_1_vie m,int x,int y,TTF_Font * font,double temps_actu,liste l_chars){
  char t[100];
  sprintf(t,"temps restants : %f       joueurs restant : %d",m->temps_debut+m->temps_max-temps_actu,nombre_chars(l_chars));
  ecrire_text(font,255,255,255,x,y,t);
  
}




void ecrire_resultats_partie_ffa(FILE *f){
  fprintf(f,"ffa \n");
}

void ecrire_resultats_partie_ffa_1(FILE *f){
  fprintf(f,"ffa 1\n");
}

void ecrire_resultats_partie_tdm(FILE *f){
  fprintf(f,"tdm\n");
}

