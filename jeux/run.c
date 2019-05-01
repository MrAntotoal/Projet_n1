#include "bonus.h"
#include "time.h"
#include <sys/types.h>
#include <unistd.h>

int usage(){
  fprintf(stderr,"./run <mode de jeux> <nbr chars> <numero equipe char 0> <numero equipe char 1> ... <dossier map> <extention image fond>\n");
  exit(-1);
}

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
  liste sauv;
  liste reap;
  liste bonus;
  liste l_bonus=NULL;
  t_liste t_listes;
  SDL_Event event;
  GLuint texture_char;
  GLuint texture_fond;
  int nbr_chars;
  int mode_de_jeux;
  int i;
  char3p c;
  char nom_map[500];
  char nom_fond[500];
  double zero_bonus;
  double temps_spawn_bonus=60.0;


  TTF_Font *font;

  liste_action=list_vide();
  liste_chars=list_vide();
  liste_obus=list_vide();

  if(argc<5){
    usage();
  }
  mode_de_jeux=atoi(argv[1]);
  nbr_chars=atoi(argv[2]);
  if(argc<2+nbr_chars+1){
    usage();
  }

  for(i=1;i<=nbr_chars;i++){
    c=init_char(cree_point(-100.0,-100),24.0,36.0,i,atoi(argv[2+i]));
    liste_chars=insere_elem_liste(liste_chars,c);
  }

  sprintf(nom_map,"assets/%s/%s.map",argv[2+i],argv[2+i]);
  sprintf(nom_fond,"assets/%s/%s.%s",argv[2+i],argv[2+i],argv[3+i]);

  srand( getpid());
  
  id_fm=recuperer_id_fm();

  t_listes=alloc_mem(1,sizeof(toutes_listes));

  


  /*//tmp
  c=init_char(cree_point(-100.0,-100),30.0,45.0,1,1);
  liste_chars=insere_elem_liste(liste_chars,c);
  c=init_char(cree_point(-100.0,-100.0),30.0,45.0,20,20);
  liste_chars=insere_elem_liste(liste_chars,c);
  //*/

  cree_fen(1706,900,"run");
  TTF_Init();
  sauv=charger_map(nom_map);
  map=renvoie_sommet_liste(sauv);
  reap=renvoie_sommet_liste(liste_sans_premier(sauv));
  bonus=renvoie_sommet_liste(liste_sans_premier(liste_sans_premier(sauv)));
  texture_fond=charger_texture(nom_fond);
  texture_char=charger_texture("assets/sprite.png");
  font=TTF_OpenFont("assets/font.ttf",64);
  
  t_listes->l_requette=liste_action;
  t_listes->l_char=liste_chars;
  t_listes->l_obus=liste_obus;
  t_listes->l_map=map;
  

  spawn_all_tank(reap,liste_chars);
  
  start = clock(); 
  zero_bonus=start/CLOCKS_PER_SEC;
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
      boucle_de_traitement_liste_requete(t_listes,end/CLOCKS_PER_SEC);
      //printf("fin boucle t debut obus\n");
      t_listes->l_obus=traitement_tous_obus(t_listes->l_obus,t_listes->l_char,map,id_fm,texture_char);

      //les bonus
      l_bonus=all_char_liste_bonus(t_listes->l_char,l_bonus);

      //laser

      all_laser_touche(t_listes->l_char,id_fm);
      //printf("fin obus\n");


      
      afficher_liste_chars(t_listes->l_char,texture_char,font);

      //printf("aff \n");

      afficher_map(map);

      sprintf(fps_aff,"%d",nbr_fps_lf);
      ecrire_text(font,255,255,255,1960,1000,fps_aff);
      afficher_liste_bonus(l_bonus);

      //printf("%d \n",est_collision_avec_map(c,map));
      go_ecran();
      
    }
    test_stop_special_all_char(t_listes->l_char,end/CLOCKS_PER_SEC);
    regene_bouclier_all_char(t_listes->l_char,end/CLOCKS_PER_SEC);
    special_recharge_all_char(t_listes->l_char,end/CLOCKS_PER_SEC,id_fm);


    if(zero_bonus+temps_spawn_bonus<start/CLOCKS_PER_SEC){
      l_bonus=faire_spawn_bonus(t_listes->l_char,bonus,l_bonus);
      zero_bonus=start/CLOCKS_PER_SEC;
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
