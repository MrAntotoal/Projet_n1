<<<<<<< HEAD
#define FICHIER_CLE "../README.md"
=======
#define FICHIER_CLE "../README"
>>>>>>> origin/jeux
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

typedef struct{
  long mtype;
  char numero_char;
  char type_action;
  char a_repeter;
}requete_t;

typedef struct{
  long mtype;
  char numero_char;
  char type;
}reponse_t;

