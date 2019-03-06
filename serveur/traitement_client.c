#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strcmp_rapide.h"
#include "message_serveur.h"
#include "message.h"
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
  char a_comparer[50];
  char *RX; // a envoyer
  strcpy(a_comparer, DEPLACEMENT);
  printf("%s\n",a_comparer);
  if (strncmp(a_comparer,buffer,strlen(a_comparer)) == 0)
  {
    /* alors recuperer selon codage */
    RX = argv[2];
    printf("FDM %s\n",RX);
  }
  else
  {
    strcpy(a_comparer, TIR);
    if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
    {
      /* alors recuperer selon codage */
      printf("Tir %s\n",buffer);
    }
    else
    {
      strcpy(a_comparer, MORT);
      if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
      {
        /* alors recuperer selon codage */
        printf("M %s\n",buffer);
      }
      else
      {
        strcpy(a_comparer, TUER);
        if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
        {
          /* alors recuperer selon codage */
          printf("T %s\n",buffer);
        }
        else
        {
          printf("%s non reconnu\n", buffer);
          exit(-1);
        }
      }
    }
  }
  exit(0);
}
