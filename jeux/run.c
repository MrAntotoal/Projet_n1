#include "mode_de_jeux.h"
#include <time.h>
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
  //clock_t start, end; 
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
  GLuint texture_fin_partie;
  GLuint texture_bonus;
  int nbr_chars;
  int mode_de_jeux;
  int i;
  char3p c;
  char nom_map[500];
  char nom_fond[500];
  long zero_bonus;
  double temps_spawn_bonus=15.0;

  long zero_respawn;
  double temps_a_respawn=30.0;

  long zero_fin_partie;
  double temps_fin_de_partie=10.0;
  void * struct_mode=NULL;
  int team=0;
  reponse_t rep;

  FILE * f;
  TTF_Font *font;

  int en_jeux=1;

  //musique
  Mix_Music *musique_fond;
  
  Mix_Chunk *son_laser;
  Mix_Chunk *son_conducteur;
  Mix_Chunk *son_bouclier;



  ///////test time
  struct timespec temps_start,temps_end;

  ////
  clock_gettime(CLOCK_REALTIME,&temps_start);

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
    c=init_char(cree_point(-100.0,-100),24.0,36.0,i,atoi(argv[2+i]),temps_start.tv_sec);
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
  ouvrir_mixer();
  Mix_AllocateChannels(nbr_chars*3);
  
  
  musique_fond=Mix_LoadMUS("assets/musique/Battlefield - 1.mp3");
  son_laser=Mix_LoadWAV("assets/effets_sonore/Ima - Firen.wav");
  son_conducteur=Mix_LoadWAV("assets/effets_sonore/Ima - Firen.wav");
  son_bouclier=Mix_LoadWAV("assets/effets_sonore/Ima - Firen.wav");
  
  sauv=charger_map(nom_map);
  map=renvoie_sommet_liste(sauv);
  reap=renvoie_sommet_liste(liste_sans_premier(sauv));
  bonus=renvoie_sommet_liste(liste_sans_premier(liste_sans_premier(sauv)));
  texture_fond=charger_texture(nom_fond);
  texture_char=charger_texture("assets/sprite.png");
  texture_fin_partie=charger_texture("assets/fin.jpg");
  texture_bonus=charger_texture("assets/bonus.png");
  font=TTF_OpenFont("assets/font.ttf",60);
  
  t_listes->l_requette=liste_action;
  t_listes->l_char=liste_chars;
  t_listes->l_obus=liste_obus;
  t_listes->l_map=map;
  

  spawn_all_tank(reap,liste_chars);

  f=fopen("resultats.html","w");
  if(f==NULL){
    fprintf(stderr,"impossible d'ouvrir le fichier resultats.game \n");
    exit(-1);
  }

  clock_gettime(CLOCK_REALTIME,&temps_start);
  //start = clock(); 
  /*zero_bonus=start/CLOCKS_PER_SEC;
    zero_respawn=start/CLOCKS_PER_SEC;*/

  zero_bonus=temps_start.tv_sec;
  zero_respawn=temps_start.tv_sec;

  Mix_PlayMusic(musique_fond,-1);


  /* reglé le volume
  Mix_Volume(1,MIX_MAX_VOLUME);
  */
  //Mix_PlayChannel(-1,son_laser,1);

  
  if(mode_de_jeux==0){
    //ffa 1 vie
    struct_mode=debut_ffa_1_vie(temps_start.tv_sec);
  }
  if(mode_de_jeux==1){
    //ffa 
    struct_mode=debut_ffa(temps_start.tv_sec,20);
  }
  if(mode_de_jeux==2){
    //tdm
    struct_mode=debut_tdm(temps_start.tv_sec,20);
  }
  while(run){
    
    //end = clock();
    clock_gettime(CLOCK_REALTIME,&temps_end);
    //diff = (double)(end - start) / CLOCKS_PER_SEC;
    if(temps_end.tv_sec==temps_start.tv_sec){
      diff=(temps_end.tv_nsec-temps_start.tv_nsec)/1000000000.0;
    }
    else{
      diff=1000000000-temps_start.tv_nsec+temps_end.tv_nsec;
    }
    
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
      if(en_jeux){
	afficher_fond(texture_fond);
      
	//printf("lire fm\n");
	t_listes->l_requette=lire_fm(id_fm,t_listes->l_requette);
	//printf("fin lire fm et boucle t\n");
	boucle_de_traitement_liste_requete(t_listes,temps_end.tv_sec,son_conducteur,son_laser,son_bouclier);
	//printf("fin boucle t debut obus\n");
	t_listes->l_obus=traitement_tous_obus(t_listes->l_obus,t_listes->l_char,map,id_fm,texture_char);

	//les bonus
	l_bonus=all_char_liste_bonus(t_listes->l_char,l_bonus);
	//laser
	all_laser_touche(t_listes->l_char,id_fm);
	//printf("fin obus\n");
	afficher_liste_chars(t_listes->l_char,texture_char,font,mode_de_jeux);
	//printf("aff \n")
	afficher_map(map);
	//les modes aff
	switch(mode_de_jeux){
	case 0:
	  afficher_ffa_1(struct_mode,550,1000,font,temps_end.tv_sec,t_listes->l_char);
	  break;
	case 1:
	  afficher_ffa(struct_mode,750,1000,font,temps_end.tv_sec);
	  break;
	case 2:
	  afficher_tdm(struct_mode,750,1000,font,temps_end.tv_sec);
	  break;
	}

	sprintf(fps_aff,"%d",nbr_fps_lf);
	ecrire_text(font,255,255,255,1960,1000,fps_aff);
	afficher_liste_bonus(l_bonus,texture_bonus);

	//printf("%d \n",est_collision_avec_map(c,map));
	go_ecran();
      
      }
      else {
	afficher_fin_game(texture_fin_partie);
	go_ecran();
      }
    }
      

      
    if(en_jeux){
      test_stop_special_all_char(t_listes->l_char,temps_end.tv_sec);
      regene_bouclier_all_char(t_listes->l_char,temps_end.tv_sec);
      special_recharge_all_char(t_listes->l_char,temps_end.tv_sec,id_fm);

      if(zero_bonus+temps_spawn_bonus<temps_end.tv_sec){
	l_bonus=faire_spawn_bonus(t_listes->l_char,bonus,l_bonus);
	zero_bonus=temps_end.tv_sec;
      }

      if(zero_respawn+ temps_a_respawn<temps_end.tv_sec){
	switch(mode_de_jeux){
	case 1:
	  faire_res_all_chars(t_listes->l_char,reap,temps_end.tv_sec,mode_de_jeux,(Mode_ffa)struct_mode);
	  break;
	case 2:
	  faire_res_all_chars(t_listes->l_char,reap,temps_end.tv_sec,mode_de_jeux,(Mode_tdm)struct_mode);
	  break;
	}
      
	zero_respawn=temps_end.tv_sec;
      }

      //mode de jeux
      switch(mode_de_jeux){
      case 0://ffa 1
	if(fin_ffa_1((Mode_ffa_1_vie)struct_mode,t_listes->l_char,temps_end.tv_sec)){
	  printf("fin de la game\n");
	  en_jeux=0;
	  zero_fin_partie=temps_end.tv_sec;
	  enregistrer_ffa_1(t_listes->l_char,f);
	  rep.mtype=1;
	  rep.numero_char=-1;
	  rep.type=0;
	  envoyer_au_serveur(id_fm,rep);
	  fclose(f);
	}
	break;
      case 1://ffa
	if(fin_ffa((Mode_ffa)struct_mode,temps_end.tv_sec)){
	  printf("fin de la game\n");
	  en_jeux=0;
	  zero_fin_partie=temps_end.tv_sec;
	  enregistrer_ffa(t_listes->l_char,f);
	  rep.mtype=1;
	  rep.numero_char=-1;
	  rep.type=0;
	  envoyer_au_serveur(id_fm,rep);
	  fclose(f);
	}
	break;
      case 2://tdm
	team= fin_tdm((Mode_tdm)struct_mode,temps_end.tv_sec);
	if(team!=0){
	  printf("fin de la game %d win \n",team);
	  en_jeux=0;
	  zero_fin_partie=temps_end.tv_sec;
	  enregistrer_tdm(t_listes->l_char,f,team);
	  rep.mtype=1;
	  rep.numero_char=-1;
	  rep.type=0;
	  envoyer_au_serveur(id_fm,rep);
	  fclose(f);
	  
	}
	break;
      
      }
    }
    else{
      if(temps_end.tv_sec>=zero_fin_partie+temps_fin_de_partie){
	//redaction des resultats
	//ecrire_tous_chars(f,t_listes->l_char);
	
	run=0;
      }
    }
    
    //start=end;

    temps_start=temps_end;
    somme+=diff;
    somme2+=diff;
    if(somme>1.0){
      //fprintf(stderr,"fps %d  somme %f\n",nbr_fps,somme);
      nbr_fps_lf=nbr_fps;
      somme=0.0;
      nbr_fps=0;
      
    }

    ///test temps
    //clock_gettime(CLOCK_REALTIME,&tt);
    // printf("sec %ld  nano %ld\n",tt.tv_sec,tt.tv_nsec);
    //test fin 
  }
 
  Mix_FreeChunk(son_laser);
  Mix_FreeChunk(son_conducteur);
  Mix_FreeChunk(son_bouclier);

  Mix_FreeMusic(musique_fond);
  
  fermeture_mixer();
  exit(0);

}
