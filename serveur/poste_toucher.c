#include "fdm.h"

int main(int argc, char const *argv[]) {
  if(argc != 2){
    printf("usage poste_toucher <num_equipe>\n");
    exit(-1);
  }

  ouvrir_fdm();

  reponse_t msg = {0};
  msg.m_type = 1;
  msg.numero_char = atoi(argv[1]);
  msg.type = 100;

  if(msgsnd(id_fdm,&msg,sizeof(reponse_t)- sizeof(long),0) == -1)
  {
    #ifdef AFFICHAGE
    printf("********** msg non envoyé **********\n");
    #endif
    return -1;
  }
  printf("message poster\n");
  return 0;
}
