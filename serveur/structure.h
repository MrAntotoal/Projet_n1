#ifndef STRUCTURE_H
#define STRUCTURE_H

//#include "serveur.h"

#define NB_J_EQUIPE_MAX 3
#define NB_EQUIPE_MAX 50


typedef int SOCKET;
#define BUF_SIZE	1024


typedef struct
{
   SOCKET sock;
   int pseudo;
   int numEquipe;
}Client;


typedef struct
{
  int nb_joueur;
  int numj;
  Client *membre[NB_J_EQUIPE_MAX]; // chef d'équipe = 0
}Equipe;



#endif /* guard */
