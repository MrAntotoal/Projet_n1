#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char const *argv[]) {
  FILE *fichier;
  char *nom_fichier = "./tmp.txt";
  int pid;
  fichier = fopen(nom_fichier, "r");
  fscanf(fichier,"%d\n",&pid);
  kill(pid,SIGUSR1);
  //remove("tmp.txt");
  system("./clients localhost _____________________________");
  return 0;
}
