#include "traitement_fm.h"




void stop_requete(char numero_char,char type_action,liste l){
  requete_t *rt;
  if(!est_list_vide(l)){
    rt=renvoie_sommet_liste(l);
    if(rt->numero_char==numero_char && rt->type_action== type_action){
      rt->a_repeter=-1;
    }
    else{
      stop_requete(numero_char,type_action,liste_sans_premier(l));
    }
  }
}


/*
void boucle_de_traitement_liste_requete(toutes_listes li){//liste l,liste l_char,liste l_obus
  int nbr;
  int i;
  requete_t* r;
  printf("liste r %p liste c %p liste o %p !!!\n ",li.l_requette,li.l_char,li.l_obus);
  nbr=longueur_liste(li.l_requette);
  for(i=0;i<nbr;i++){
    printf("traitment requete n %d  \n ",i);
    r=renvoie_sommet_liste(li.l_requette);
    li.l_requette=supprime_elem(li.l_requette,r);
    fprintf(stderr,"requette %d %d %d \n",r->numero_char,r->type_action,r->a_repeter);
    if(r->a_repeter!=1){
      if(r->a_repeter==0){
      //faire l'action
	if(r->type_action<0){// les arretes
	  stop_requete(r->numero_char,-r->type_action,li.l_requette);
	}
	else{//actions unique
	  switch (r->type_action){
	  case 10://tire
	    printf("tire!!\n");
	    li.l_obus=insere_elem_liste(li.l_obus,cree_obus(get_index(r->numero_char-1,li.l_char)));
	    break;
	  }
	  
	}
	
      }
      printf("liberation\n");
      libere(r);
    }
    else{
      //faire l'action
      switch(r->type_action){
      case 1://avance char
	char_avance(get_index(r->numero_char-1,li.l_char));
	//verif si pas collisions

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  char_recule(get_index(r->numero_char-1,li.l_char));
	}
	
	break;
      case 2://recule char
	char_recule(get_index(r->numero_char-1,li.l_char));
	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  char_avance(get_index(r->numero_char-1,li.l_char));
	}
	break;
      case 3://go droite char
	char_droite(get_index(r->numero_char-1,li.l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  char_gauche(get_index(r->numero_char-1,li.l_char));
	}
	break;
      case 4://go gauche char
	char_gauche(get_index(r->numero_char-1,li.l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  char_droite(get_index(r->numero_char-1,li.l_char));
	}
	break;
      case 5://go droite tourelle
	tourelle_droite(get_index(r->numero_char-1,li.l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  tourelle_gauche(get_index(r->numero_char-1,li.l_char));
	}
	break;
      case 6://go gauche tourelle
	tourelle_gauche(get_index(r->numero_char-1,li.l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,li.l_char),li.l_char)){
	  tourelle_droite(get_index(r->numero_char-1,li.l_char));
	}
	break;
	
      }
      li.l_requette=insere_elem_liste(li.l_requette,r);
    } 
  }
}*/


void boucle_de_traitement_liste_requete(t_liste tl,double time){
  int nbr;
  int i;
  requete_t* r;
  char3p c;
  //printf("liste r %p liste c %p liste o %p !!!\n ",tl->l_requette,tl->l_char,tl->l_obus);
  nbr=longueur_liste(tl->l_requette);
  //fprintf(stderr,"long %d \n",nbr);
  for(i=0;i<nbr;i++){
    //printf("traitment requete n %d\n",i);
    r=renvoie_sommet_liste(tl->l_requette);
    tl->l_requette=supprime_elem(tl->l_requette,r);

    
    //printf("liste r %p !!!!!!!!!\n ",tl->l_requette);
    //fprintf(stderr,"requette %d %d %d \n",r->numero_char,r->type_action,r->a_repeter);
    if(r->a_repeter!=1){
      if(r->a_repeter==0){
	//faire l'action
	if(r->type_action<0){// les arretes
	  stop_requete(r->numero_char,-r->type_action,tl->l_requette);
	}
	else{//actions unique
	  switch (r->type_action){
	  case 10://tire
	    c=get_index(r->numero_char-1,tl->l_char);
	    if(c->pv >0){
	      printf("tire!!\n");
	      tl->l_obus=insere_elem_liste(tl->l_obus,cree_obus(c));
	    }
	    break;
	  case 11://active bouclier
	    c=get_index(r->numero_char-1,tl->l_char);
	    activer_bouclier(c);
	    break;
	  
	  case 12://stop bouclier
	    stop_bouclier(get_index(r->numero_char-1,tl->l_char),time);
	    break;
	  case 20:
	    c=get_index(r->numero_char-1,tl->l_char);
	    activer_spe_c(c,time);
	    break;
	  case 21:
	    c=get_index(r->numero_char-1,tl->l_char);
	    activer_spe_t(c,time);
	  }
	  
	}
	
      }
      libere(r);
    }
    else{
      //faire l'action
      switch(r->type_action){
      case 1://avance char
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  char_avance(c);
	  //verif si pas collisions

	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    char_recule(c);
	  }
	}
	
	break;

	
      case 2://recule char

	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  char_recule(c);

	
	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    char_avance(c);
	  }
	}
	
	break;
	
      case 3://go droite char
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  char_droite(c);

	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    char_gauche(c);
	  }
	}
	
	break;
	
      case 4://go gauche char
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  char_gauche(c);

	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    char_droite(c);
	  }
	}
	break;
	
      case 5://go droite tourelle
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  tourelle_droite(c);

	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    tourelle_gauche(c);
	  }
	}
	break;
	
      case 6://go gauche tourelle
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  tourelle_gauche(c);

	  if(est_en_collisions_avec_un_autre(c,tl->l_char)||est_collision_avec_map(c,tl->l_map)){
	    tourelle_droite(c);
	  }
	}
	break;
	
      
      case 7://go droite bouclier
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  bouclier_droite(c);
	}
	break;

      case 8://go gauche bouclier
	c=get_index(r->numero_char-1,tl->l_char);
	if(c->pv >0){
	  bouclier_gauche(c);
	}
	break;
      }
      tl->l_requette=insere_elem_liste(tl->l_requette,r);
    } 
  }
  //return l;
}


