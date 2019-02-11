#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "serveur.h"

#define NB_J_EQUIPE_MAX 3
#define NB_EQUIPE_MAX 50
#define CREER_EQUIPE "CREER_EQUIPE"
#define REJOINDRE_EQUIPE "REJOINDRE_EQUIPE"
#define QUITTER_EQUIPE "QUITTER_EQUIPE"

typedef int SOCKET;
#define BUF_SIZE	1024

typedef struct
{
  int nb_joueur;
  int numj;
  SOCKET membre[NB_J_EQUIPE_MAX]; // chef d'équipe = 0
}Equipe;

typedef struct
{
   SOCKET sock;
   char name[BUF_SIZE];
   int numEquipe;
   Equipe eq;
}Client;



#endif /* guard */
