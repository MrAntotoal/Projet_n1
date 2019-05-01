#include "fdm.h"

key_t cle;

int creer_fdm(){
  cle = ftok(FICHIER_CLE,LETTRE);
  id_fdm = msgget(cle, IPC_CREAT | IPC_EXCL | 0666);
  if(id_fdm == -1)
  {
    #ifdef AFFICHAGE
    printf("********** Création FDM Erreur **********\n");
    #endif
    return -1;
  }
  return 0;
}

int ouvrir_fdm(){
  cle = ftok(FICHIER_CLE,LETTRE);
  id_fdm = msgget(cle, 0);
  if(id_fdm == -1)
  {
    #ifdef AFFICHAGE
    printf("********** ID FDM Erreur **********\n");
    #endif
    return -1;
  }
  return 0;
}

void fermer_fdm(){
  msgctl(id_fdm,IPC_RMID,NULL);
}

int envoyer_requete(char nc, char action, char a_repeter){
  requete_t msg = {0};
  msg.m_type = A_JEUX;
  msg.numero_char = nc;
  msg.type_action = action;
  msg.a_repeter = a_repeter;

  if(msgsnd(id_fdm,&msg,sizeof(requete_t)- sizeof(long),0) == -1)
  {
    #ifdef AFFICHAGE
    printf("********** msg non envoyé **********\n");
    #endif
    return -1;
  }
  return 0;
}

int prendre_reponse(){
  if(msgrcv(id_fdm,&rcv,sizeof(reponse_t)- sizeof(long),1,IPC_NOWAIT)==-1){
    return -1;
  }
  return 0;
}
