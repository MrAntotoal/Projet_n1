#include "sauvegarde.h"

int main(int argc,char * argv[]){
  //char *nom_fichier_image;
  //liste liste_des_obsacles;
  //liste liste_de_zone;
  int resolution_max_x;
  int resolution_max_y;
  int resolution_actu_x;
  int resolution_actu_y;
  //liste l_points=list_vide();
  liste liste_poly=list_vide();
  liste liste_poly_zone=list_vide();
  liste liste_points_reap=list_vide();
  liste liste_points_bonus=list_vide();
  //liste l_inter_z;
  int numero_poly_actu=-1;
  int poly_actu=-1;
  int nouveau=1;
  int i;
  int ajoute=0;
  
  
  int run =1;

  int need_affichage=1;

  SDL_Event event;
  Points sourie =cree_point(500,500);
  Vecteurs diff_sourie=cree_vecteur_2d(0,0);
  int a_clicker=0;
  float rap_x,rap_y;
  int modification_mode=0;
  int reap_mode=0;
  int bonus_mode=0;
  Points p_select=NULL;
  Points p_derniere_pos=NULL;
  liste l_inter;
  GLuint fond;
  //int zone=0;
  int num;
  if(argc!=4){
    fprintf(stderr,"editeur <nom_de_l'image> <resolution x> <resolution y>\n ->sortie map map.map \n");
    exit(-1);
  }
  resolution_max_x=2048;
  resolution_max_y=1080;

  resolution_actu_x=atoi(argv[2]);
  resolution_actu_y=atoi(argv[3]);

  rap_x=(float)resolution_max_x/resolution_actu_x;
  rap_y=(float)resolution_max_y/resolution_actu_y;

  cree_fen((resolution_actu_x*(resolution_max_x+200))/resolution_max_x,
	   (resolution_actu_y*(resolution_max_y+200))/resolution_max_y,
	   "editeur");


  fond=charger_texture(argv[1]);
  
  
  
  while(run){

    //event l'appli va pas fonctiopnner avec fps comme le jeux mais sur les evnets
    SDL_WaitEvent(&event);
    switch(event.type)
      {
      case SDL_QUIT:
	run = 0;
	break;
      case SDL_MOUSEBUTTONDOWN:
	if(!a_clicker){
	  //printf("%d %d\n",event.button.x,event.button.y);
	  
	  modifier_points(sourie,-100+event.button.x*rap_x,100+(resolution_actu_y
						       -event.button.y)*rap_y);

	  //printf("%f %f \n",sourie->x,sourie->y);
	  a_clicker=1;
	  need_affichage=1;
	  if(!modification_mode){
	    p_derniere_pos=cree_point(-100+event.button.x*rap_x,
				      100+(resolution_actu_y
				       -event.button.y)
				      *rap_y);
	    if(reap_mode){
	      liste_points_reap=insere_elem_liste(liste_points_reap,p_derniere_pos);
	    }
	    else if(bonus_mode){
	      liste_points_bonus=insere_elem_liste(liste_points_bonus,p_derniere_pos);
	    }
	    else if(nouveau==1){
	      numero_poly_actu++;
	      poly_actu=numero_poly_actu;
	      liste_poly=insere_elem_liste(liste_poly,
					   insere_elem_liste(list_vide(),p_derniere_pos));
	      nouveau=0;
	    }
	    else{
	      if(!ajoute){
		insere_point_poly(get_index(poly_actu,liste_poly),
					p_derniere_pos);
	      }
	      else{
		if(p_select!=NULL){
		  insere_elem_apres_un_autre(p_select,get_index(poly_actu,liste_poly),p_derniere_pos);
		  p_select=p_derniere_pos;
		}
	      }
	    }
	  }
	  else{
	    p_select=sur_un_point(sourie,liste_poly);
	    if(p_select==NULL){
	      p_select=sur_un_point_poly(sourie,liste_points_reap);
	    }
	    if(p_select==NULL){
	      p_select=sur_un_point_poly(sourie,liste_points_bonus);
	    }
	  }
	}
	
	  /*if(liste_poly==list_vide()){	    poly_actu=cree_polygone_p(1,cree_point(event.button.x*rap_x,(resolution_actu_y-event.button.y)*rap_y));
	    insere_elem_liste(liste_poly,poly_actu);
	  }
	  else{
	    insere_point_poly(liste_poly,cree_point(event.button.x*rap_x,(resolution_actu_y-event.button.y)*rap_y));
	    }
	  
	    }*/
	break;
      case SDL_MOUSEBUTTONUP:
	//printf("un presse\n");
	a_clicker=0;
	need_affichage=1;
	break;
	
      case SDL_MOUSEMOTION:
	if(a_clicker){
	  if(modification_mode && p_select!=NULL){
	    need_affichage=1;
	    modifier_points(diff_sourie,
			    -100+event.motion.x*rap_x-sourie->x,
			    100+(resolution_actu_y-event.motion.y)*rap_y-sourie->y);

	    

	    //modifier_points(sourie,event.button.x*rap_x,(resolution_actu_y
	    //-event.button.y)*rap_y);

	    modifier_points(sourie,-100+event.button.x*rap_x,100+(resolution_actu_y
						       -event.button.y)*rap_y);

	    modifier_points(p_select,p_select->x+diff_sourie->x,p_select->y+diff_sourie->y);
	  }
	}
	break;

	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym){
	  case SDLK_n:
	    if(!nouveau){
	      nouveau=1;
	      ajoute=0;
	      reap_mode=0;
	      modification_mode=0;
	      need_affichage=1;
	    }
	    break;
	  case SDLK_s:
	    enregistrer_all("map.map",liste_poly,liste_poly_zone,liste_points_reap,liste_points_bonus);
	    break;
	  case SDLK_z:
	    l_inter=liste_poly;
	    i=0;
	    if(modification_mode && p_select!=NULL){
	      while(!est_list_vide(l_inter)){
		if(est_dans_liste(l_inter->objet,p_select)){
		  poly_actu=i;
		  break;
		}
		l_inter=l_inter->suivant;
		i++;
	      }
	      num=poly_actu;
	      polygone p;
	      p=get_index(num,liste_poly);
	      if(est_dans_liste(liste_poly_zone,p)){
		liste_poly_zone=supprime_elem_sans_libere(liste_poly_zone,p);
	      }
	      else{
		liste_poly_zone=insere_elem_liste(liste_poly_zone,p);
	      }
	      need_affichage=1;
	    }
	    break;
	  case SDLK_m:
	    if(!modification_mode){
	      modification_mode=1;
	      ajoute=0;
	      reap_mode=0;
	      need_affichage=1;
	    }
	    else{
	      modification_mode=0;
	      need_affichage=1;
	    }
	    break;
	  case SDLK_r:
	    if(!reap_mode){
	      reap_mode=1;
	      ajoute=0;
	      modification_mode=0;
	      need_affichage=1;
	    }
	    else{
	      reap_mode=0;
	      modification_mode=0;
	      need_affichage=1;
	    }
	    break;
	  case SDLK_b:
	    if(!bonus_mode){
	      bonus_mode=1;
	      ajoute=0;
	      modification_mode=0;
	      need_affichage=1;
	    }
	    else{
	      bonus_mode=0;
	      modification_mode=0;
	      need_affichage=1;
	    }
	    
	    break;
	  case SDLK_a:
	    if(!ajoute){
	      if(modification_mode && p_select!=NULL){
		l_inter=liste_poly;
		i=0;
		while(!est_list_vide(l_inter)){
		  if(est_dans_liste(l_inter->objet,p_select)){
		    poly_actu=i;
		    ajoute=1;
		    break;
		  }
		  l_inter=l_inter->suivant;
		  i++;
		}
		modification_mode=0;
		need_affichage=1;
	      }
	    }
	    else{
	      ajoute=0;
	      need_affichage=1;
	    }
	    break;


	    
	  case SDLK_DELETE:
	    if(modification_mode && p_select!=NULL){
	      l_inter=liste_poly;
	      liste_points_reap=supprime_elem(liste_points_reap,p_select);
	      liste_poly->objet=supprime_elem(liste_poly->objet,p_select);
	      liste_points_bonus=supprime_elem(liste_points_bonus,p_select);
	      while(!est_list_vide(l_inter)){
		l_inter->objet=supprime_elem(l_inter->objet,p_select);
		l_inter=l_inter->suivant;
	      }
	      //liste_poly=l_inter;

	      
	      if(p_select==p_derniere_pos){
		p_derniere_pos=NULL;
	      }
	      p_select=NULL;
	      need_affichage=1;
	    }
	    break;
	    
	     
	  default :
	    break;
	  }
	  
      }

    //si besoin affichage re afficher ce qu'on a 
    if(need_affichage){
      need_affichage=0;

      buffer_image_0();
      //section affichage

      //afficher la zones des options 
      if(modification_mode){
	glColor3ub(255,0,0);
      }
      else if(ajoute){
	glColor3ub(0,255,0);
      }
      else if(reap_mode){
	glColor3ub(255,255,255);
      }
      else if(bonus_mode){
	glColor3ub(255,147,0);
      }
      else{
	glColor3ub(0,0,255);
      }
      glBegin(GL_QUADS);
      glVertex2d(-100,-100);
      glVertex2d(-100,1180);
      glVertex2d(0,1180);
      glVertex2d(0,-100);
      glEnd();
      glBegin(GL_QUADS);
      glVertex2d(0,-100);
      glVertex2d(0,0);
      glVertex2d(2048,0);
      glVertex2d(2048,-100);
      glEnd();
      glBegin(GL_QUADS);
      glVertex2d(0,1080);
      glVertex2d(0,1180);
      glVertex2d(2048,1180);
      glVertex2d(2048,1080);
      glEnd();
      glBegin(GL_QUADS);
      glVertex2d(2148,-100);
      glVertex2d(2148,1180);
      glVertex2d(2048,1180);
      glVertex2d(2048,-100);
      glEnd();

      glColor3ub(255,255,255);
      activer_texturing();
      bind_texture(fond);
      glBegin(GL_QUADS);
      glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
      glTexCoord2d(0.0,1.0); glVertex2d(0.0,1080.0);
      glTexCoord2d(1.0,1.0); glVertex2d(2048,1080);
      glTexCoord2d(1.0,0.0); glVertex2d(2048,0.0);
      glEnd();
      desactiver_texturing();

      //afficher_les_poly
      afficher_liste_poly_trait(liste_poly,255 , 255 , 255);
      afficher_liste_poly_trait(liste_poly_zone,255 , 0 , 0);
      if(p_derniere_pos!=NULL){
	afficher_contour_select(p_derniere_pos,0,0,255);
      }
      if(modification_mode || ajoute){
	if(p_select!=NULL){
	  afficher_contour_select(p_select,255,0,0);
	}
      }

      afficher_liste_point(liste_points_reap,255,255,0);
      afficher_liste_point(liste_points_bonus,255,140,0);
      go_ecran();
      
    }
  }
  
}
