#include "traitement_fm.h"


liste ajoute_requete(requete_t rt, liste l){
  requete_t *nv_rt;
  nv_rt=alloc_mem(1,sizeof(requete_t));

  nv_rt->numero_char=rt.numero_char;
  nv_rt->type_action=rt.type_action;
  nv_rt->a_repeter=rt.a_repeter;

  l=insere_elem_liste(l,nv_rt);
  return l;
}

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

liste boucle_de_traitement_liste_requete(liste l,liste l_char){
  int nbr;
  int i;
  requete_t* r;
  nbr=longueur_liste(l);
  fprintf(stderr,"long %d \n",nbr);
  for(i=0;i<nbr;i++){
    printf("traitment requete n %d\n",i);
    r=renvoie_sommet_liste(l);
    l=supprime_elem(l,r);
    fprintf(stderr,"requette %d %d %d \n",r->numero_char,r->type_action,r->a_repeter);
    if(r->a_repeter!=1){
      if(r->a_repeter==0){
      /*faire l'action*/
	if(r->type_action<0){// les arretes
	  stop_requete(r->numero_char,-r->type_action,l);
	}
	else{//actions unique

	}
	
      }
      libere(r);
    }
    else{
      /*faire l'action*/
      switch(r->type_action){
      case 1://avance char
	char_avance(get_index(r->numero_char-1,l_char));
	//verif si pas collisions

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  char_recule(get_index(r->numero_char-1,l_char));
	}
	
	break;
      case 2://recule char
	char_recule(get_index(r->numero_char-1,l_char));
	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  char_avance(get_index(r->numero_char-1,l_char));
	}
	break;
      case 3://go droite char
	char_droite(get_index(r->numero_char-1,l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  char_gauche(get_index(r->numero_char-1,l_char));
	}
	break;
      case 4://go gauche char
	char_gauche(get_index(r->numero_char-1,l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  char_droite(get_index(r->numero_char-1,l_char));
	}
	break;
      case 5://go droite tourelle
	tourelle_droite(get_index(r->numero_char-1,l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  tourelle_gauche(get_index(r->numero_char-1,l_char));
	}
	break;
      case 6://go gauche tourelle
	tourelle_gauche(get_index(r->numero_char-1,l_char));

	if(est_en_collisions_avec_un_autre(get_index(r->numero_char-1,l_char),l_char)){
	  tourelle_droite(get_index(r->numero_char-1,l_char));
	}
	break;
	
      }
      l=insere_elem_liste(l,r);
    } 
  }
  return l;
}

liste lire_fm(int id_fm,liste l){
  int test=0;
  requete_t requete;
  while(test!=-1){
    //fprintf(stderr,"traitement va lire fm\n");
    /* recuperation ou attente d'une action */
    test=msgrcv(id_fm,&requete,sizeof(requete_t),20001,IPC_NOWAIT);
    if(test==-1){
      if(errno == EINTR){
	fprintf(stderr,"erreur jeux stoper par un signal\n");
      }
      else if(errno == EAGAIN){
	fprintf(stderr,"erreur jeux  erreur file de message pleine !! attention\n\n");
      }
    }
    else{
    /*ajoute a la liste*/
      printf("ajoute \n");
      l=ajoute_requete(requete, l);
      fprintf(stderr,"aprers ajout\n");
    }
  }
  return l;
}

void envoyer_au_serveur(int id_fm,reponse_t rep){
  int test;
  test=msgsnd(id_fm,&rep,sizeof(reponse_t) - sizeof(long),2);
  if(test==-1){
    if(errno == EINTR){
      fprintf(stderr,"jeux erreur debloquer par la reception d'un signal non mortel \n");
    }
    else if(errno == EAGAIN){
      fprintf(stderr,"jeux erreur file de message pleine \n");
    }
  }
  fprintf(stderr,"jeux a envoyer un message\n");

}

int recuperer_id_fm(){
  FILE *fichier_pour_cle;
  int id_fm;
  int cle;
  fichier_pour_cle = fopen(FICHIER_CLE,"r");
  if (fichier_pour_cle==NULL){
    fprintf(stderr,"Lancement jeux impossible\n");
    exit(-1);
  }

  cle = ftok(FICHIER_CLE,'a');
  if (cle==-1){
    fprintf(stderr,"Pb creation cle\n");
    exit(-1);
  }

  id_fm=msgget(cle,0);
  if(id_fm==-1){
    fprintf(stderr,"jeux erreur recuperation fils de message\n");
    exit(-1);
  }
  return id_fm;
}
