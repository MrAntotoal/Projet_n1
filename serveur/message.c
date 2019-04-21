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
