#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strcmp_rapide.h"
#include "message_serveur.h"
#include "message.h"
#include "fdm.h"
/* usage */
/*  traitement_client buffer ... */
int main(int argc, char *argv[]) {
  /* code */

  char *buffer = argv[1];
  if(buffer == NULL)
  {
    printf("Buffer null\n");
    exit(-1);
  }

  /******************/
  /* recuperer fdm  */
  /******************/
  ouvrir_fdm();

  char a_comparer[50];
  char *RX; // a envoyer
  strcpy(a_comparer, DEPLACEMENT);
  if (strncmp(a_comparer,buffer,strlen(a_comparer)) == 0)
  {
      envoyer_requete(1,AVANCE,0);
      printf("** requete envoyé **\n");
  }
  else
  {
    strcpy(a_comparer, TIR);
    if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
    {
      /* alors recuperer selon codage */
      //printf("FDM %s\n",RX);
    }
    else
    {
      strcpy(a_comparer, RECHARGEMENT);
      if(fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
      {
        //printf("FDM %s\n",RX);
      }
      else
      {
        printf("%s non reconnu\n", buffer);
        exit(-1);
      }
    }
  }
  exit(0);
}
