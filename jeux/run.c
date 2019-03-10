#include "traitement_fm.h"
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
  int id_fm;
  liste liste_action;
  id_fm=recuperer_id_fm();
  liste_action=list_vide();
  start = clock(); 

  while(run){
    end = clock(); 
    diff = (double)(end - start) / CLOCKS_PER_SEC; 
    if(somme2>fps_d){
      nbr_fps++;
      somme2=0.0;
      liste_action=lire_fm(id_fm,liste_action);
      liste_action=boucle_de_traitement_liste_requete(liste_action);
      //fprintf(stderr,"-   fps %d  somme %f\n",nbr_fps,somme);
      fprintf(stderr,"l %d\n",longueur_liste(liste_action));
      
      
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
