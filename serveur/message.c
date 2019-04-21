#include "message.h"

void changerBoutton(){
  srand(time(0));

  p3[0] = rand()%3 ;
  p3[1] = rand()%3 ;
  p3[2] = rand()%3 ;

  p2[0] = rand()%3 ;
  while(p2[0] == p3[0]) p2[0] = rand()%3 ;
  p2[1] = rand()%3 * 3 + 3;
  while(p2[1] == p3[1]) p2[1] = rand()%3 ;
  p2[2] = rand()%3 * 3 + 6;
  while(p2[2] == p3[2]) p2[2] = rand()%3 ;

  p1[0] = rand()%3 ;
  while(p1[0] == p3[0] || p1[0] == p2[0]) p1[0] = rand()%3 ;
  p1[1] = rand()%3;
  while(p1[1] == p3[1] || p1[1] == p2[1]) p1[1] = rand()%3;
  p1[2] = rand()%3;
  while(p1[2] == p3[2] || p1[2] == p2[2]) p1[2] = rand()%3;
}


void ecrireNouveauBouton(char *truc, int n){
  if(n == 0){
    switch (p1[0]) {
      case 0:
      sprintf(truc,"%s CG",truc);
      break;
      case 1:
      sprintf(truc,"%s PG",truc);
      break;
      case 2:
      sprintf(truc,"%s TG",truc);
      break;
    }
    switch (p1[1]) {
      case 0:
      sprintf(truc,"%s CD",truc);
      break;
      case 1:
      sprintf(truc,"%s PD",truc);
      break;
      case 2:
      sprintf(truc,"%s TD",truc);
      break;
    }
    switch (p1[2]) {
      case 0:
      sprintf(truc,"%s F",truc);
      break;
      case 1:
      sprintf(truc,"%s P",truc);
      break;
      case 2:
      sprintf(truc,"%s AR",truc);
      break;
    }
    sprintf(truc,"%s \n",truc);
  }
  else{
    if (n == 1) {
      switch (p2[0]) {
        case 0:
        sprintf(truc,"%s CG",truc);
        break;
        case 1:
        sprintf(truc,"%s PG",truc);
        break;
        case 2:
        sprintf(truc,"%s TG",truc);
        break;
      }
      switch (p2[1]) {
        case 0:
        sprintf(truc,"%s CD",truc);
        break;
        case 1:
        sprintf(truc,"%s PD",truc);
        break;
        case 2:
        sprintf(truc,"%s TD",truc);
        break;
      }
      switch (p2[2]) {
        case 0:
        sprintf(truc,"%s F",truc);
        break;
        case 1:
        sprintf(truc,"%s P",truc);
        break;
        case 2:
        sprintf(truc,"%s AR",truc);
        break;
      }
      sprintf(truc,"%s \n",truc);
    }
    else{

      switch (p3[0]) {
        case 0:
        sprintf(truc,"%s CG",truc);
        break;
        case 1:
        sprintf(truc,"%s PG",truc);
        break;
        case 2:
        sprintf(truc,"%s TG",truc);
        break;
      }
      switch (p3[1]) {
        case 0:
        sprintf(truc,"%s CD",truc);
        break;
        case 1:
        sprintf(truc,"%s PD",truc);
        break;
        case 2:
        sprintf(truc,"%s TD",truc);
        break;
      }
      switch (p3[2]) {
        case 0:
        sprintf(truc,"%s F",truc);
        break;
        case 1:
        sprintf(truc,"%s P",truc);
        break;
        case 2:
        sprintf(truc,"%s AR",truc);
        break;
      }
      sprintf(truc,"%s \n",truc);
    }
  }
}
