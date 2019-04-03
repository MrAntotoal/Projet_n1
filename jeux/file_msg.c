#include "file_msg.h"

liste ajoute_requete(requete_t rt, liste l){
  requete_t *nv_rt;
  nv_rt=alloc_mem(1,sizeof(requete_t));

  nv_rt->numero_char=rt.numero_char;
  nv_rt->type_action=rt.type_action;
  nv_rt->a_repeter=rt.a_repeter;

  l=insere_elem_liste(l,nv_rt);
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
  fichier_pour_cle = fopen(FICHIER_CLE,"a");
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
