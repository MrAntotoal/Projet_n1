#include "traitement_fm.h"
#include "time.h"


int main(int argc, char * argv[]){
  int run=1;
  int fps=120;
  double fps_d=1.0/(double)fps;
  clock_t start, end; 
  double diff;
  int nbr_fps=0;
  int nbr_fps_lf=0;
  char fps_aff[10];
  double somme=0.0;;
  double somme2=0.0;
  int id_fm;
  liste liste_action;
  liste liste_chars;
  liste liste_obus;
  liste map;
  t_liste t_listes;
  SDL_Event event;
  GLuint texture_char;
  GLuint texture_fond;


  TTF_Font *font;
  
  id_fm=recuperer_id_fm();
  liste_action=list_vide();
  liste_chars=list_vide();
  liste_obus=list_vide();

  t_listes=alloc_mem(1,sizeof(toutes_listes));


  //tmp
  char3p c;
  c=init_char(cree_point(1000.0,500.0),30.0,45.0,1,1);
  liste_chars=insere_elem_liste(liste_chars,c);
  c=init_char(cree_point(1080.0,500.0),30.0,45.0,20,20);
  liste_chars=insere_elem_liste(liste_chars,c);
  //

  cree_fen(1706,900,"run");
  TTF_Init();
  map=charger_map("assets/test.map");
  texture_fond=charger_texture("assets/test.png");
  texture_char=charger_texture("assets/sprite.png");
  font=TTF_OpenFont("assets/font.ttf",64);
  
  t_listes->l_requette=liste_action;
  t_listes->l_char=liste_chars;
  t_listes->l_obus=liste_obus;
  t_listes->l_map=map;
  
  
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

      afficher_fond(texture_fond);
      
      //printf("lire fm\n");
      t_listes->l_requette=lire_fm(id_fm,t_listes->l_requette);
      //printf("fin lire fm et boucle t\n");
      boucle_de_traitement_liste_requete(t_listes);
      //printf("fin boucle t debut obus\n");
      t_listes->l_obus=traitement_tous_obus(t_listes->l_obus,t_listes->l_char,map,id_fm,texture_char);
      //printf("fin obus\n");


      
      afficher_liste_chars(t_listes->l_char,texture_char,font);

      //printf("aff \n");

      afficher_map(map);

      sprintf(fps_aff,"%d",nbr_fps_lf);
      ecrire_text(font,255,255,255,1960,1000,fps_aff);

      //printf("%d \n",est_collision_avec_map(c,map));
      go_ecran();
      
    }
    start=end;
    somme+=diff;
    somme2+=diff;
    if(somme>1.0){
      //fprintf(stderr,"fps %d  somme %f\n",nbr_fps,somme);
      nbr_fps_lf=nbr_fps;
      somme=0.0;
      nbr_fps=0;
      
    }
  }



}
