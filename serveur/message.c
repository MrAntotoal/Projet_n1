#include "message.h"

void changerBoutton(int nb_joueur){
  srand(time(0));
  for (int i = 0; i < nb_joueur; i++) {
    p1[0] = rand()%3 * 3;
    p1[1] = rand()%3 * 3;
    p1[2] = rand()%3 * 3;
  }


}
