#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "affich.h"

#define FICHIER_CLE "../README.md"
#define LETTRE 'a'
#define NUM_EXP 1
#define A_JEUX 20001

#define AVANCE 1
#define RECULE 2
#define DROITE 3
#define GAUCHE 4
#define FTIR 5
#define RECH 6

typedef struct{
  long m_type;
  signed char numero_char;
  signed char type_action;
  signed char a_repeter;
}requete_t;

typedef struct{
  long m_type;
  signed char numero_char;
  signed char type;
}reponse_t;

reponse_t rcv;
int id_fdm;


int creer_fdm();

int ouvrir_fdm();

void fermer_fdm();

/* -1 si erreur 0 sinon */
int envoyer_requete(char nc, char action, char a_repeter);

/* -1 si erreur 0 sinon */
/* consulter ensuite rcv (variable global) */
int prendre_reponse();
