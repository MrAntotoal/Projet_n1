#include "traitement_fm.h"
#include "time.h"
#include "affichage.h"


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
  liste liste_chars;
  SDL_Event event;
  id_fm=recuperer_id_fm();
  liste_action=list_vide();
  liste_chars=list_vide();


  //tmp
  char3p c;
  c=init_char(cree_point(1000.0,500.0),30.0,40.0);
  liste_chars=insere_elem_liste(liste_chars,c);
  c=init_char(cree_point(1080.0,500.0),30.0,40.0);
  liste_chars=insere_elem_liste(liste_chars,c);
  //

  cree_fen(1600,900,"run");
  
  start = clock(); 

  while(run){
    end = clock(); 
    diff = (double)(end - start) / CLOCKS_PER_SEC; 
    if(somme2>fps_d){

      SDL_PollEvent(&event);
      switch(event.type)
       {
          case SDL_QUIT:
               run = 0;
       }
      
      buffer_image_0();
      nbr_fps++;
      somme2=0.0;
      liste_action=lire_fm(id_fm,liste_action);
      liste_action=boucle_de_traitement_liste_requete(liste_action,liste_chars);
      fprintf(stderr,"apres boucle traitment\n");
      //fprintf(stderr,"-   fps %d  somme %f\n",nbr_fps,somme);
      fprintf(stderr,"l %d\n",longueur_liste(liste_action));

      
      afficher_liste_chars(liste_chars);
      
      go_ecran();
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
