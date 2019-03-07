#include "collisions.h"
#include "time.h"




int main(int argc, char * argv[]){
  int run=1;
  int fps=120;
  double fps_d=1.0/(double)fps;
  clock_t start, end; 
  double diff;
  int nbr_fps=0;
  double somme=0.0;;
  double somme2=0.0;
  start = clock(); 

  while(run){
    end = clock(); 
    diff = (double)(end - start) / CLOCKS_PER_SEC; 
    if(somme2>fps_d){
      nbr_fps++;
      somme2=0.0;
      //fprintf(stderr,"-   fps %d  somme %f\n",nbr_fps,somme);
    }
    start=end;
    somme+=diff;
    somme2+=diff;
    if(somme>1.0){
      fprintf(stderr,"fps %d  somme %f\n",nbr_fps,somme);
      somme=0.0;
      nbr_fps=0;
    }
  }



}
