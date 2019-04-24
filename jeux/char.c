#include "char.h"

char3p init_char(Points centre,double largeur,double longueur,char numero,char num_equipe){
  char3p c3p;
  
  c3p=alloc_mem(1,sizeof(char_3_places));

  //test ?

  c3p->numero_char=numero;
  c3p->num_equipe=num_equipe;

  c3p->centre=centre;
  
  c3p->devant=cree_point(centre->x,centre->y+1);
  c3p->devant_t=cree_point(centre->x,centre->y+1);
  
  c3p->directionc=cree_vecteur_2p(c3p->centre,c3p->devant);
  c3p->directiont=cree_vecteur_2p(c3p->centre,c3p->devant_t);

  c3p->c=cree_polygone_d(4,
			 centre->x-largeur,centre->y-longueur,
			 centre->x+largeur,centre->y-longueur,
			 centre->x+largeur,centre->y+longueur,
			 centre->x-largeur,centre->y+longueur);

  c3p->t=cree_polygone_d(4,
			 centre->x+(0.5/3)*largeur,centre->y+(1/4.5)*longueur,
			 centre->x+(0.5/3)*largeur,centre->y+1.8*longueur,
 			 centre->x-(0.5/3)*largeur,centre->y+1.8*longueur,
			 centre->x-(0.5/3)*largeur,centre->y+(1/4.5)*longueur);

  c3p->t_pour_afficher=cree_polygone_d(4,
				       centre->x-(2.5/3)*largeur,centre->y-((1.8/4.0)*longueur),
				       centre->x+(2.5/3)*largeur,centre->y-((1.8/4.0)*longueur),
				       centre->x+(2.5/3)*largeur,centre->y+1.8*longueur,
				       centre->x-(2.5/3)*largeur,centre->y+1.8*longueur);

  c3p->degre_c=0.0;
  c3p->degre_t=0.0;
  c3p->degre_b=90.0;
  c3p->vitesse_c=0.2;
  c3p->vitesse_rotation_c=0.2;
  c3p->vitesse_rotation_t=0.2;
  c3p->vitesse_rotation_b=0.2;
  c3p->pv=1000.0;
  c3p->pv_bouclier=300.0;
  c3p->bouclier_active=0;
  c3p->regene_bouclier=100.0;
  c3p->temps_regene=1.0;
  c3p->temps_stop_active=0.0;
  c3p->largeur_b=20;
  c3p->rayon_min_b=90.0;
  c3p->rayon_max_b=100.0;

  c3p->devant_b=cree_point(centre->x+c3p->rayon_max_b*cos(c3p->degre_b*(M_PI/180.0)),
			   centre->y+c3p->rayon_max_b*sin(c3p->degre_b*(M_PI/180.0)));

  return c3p;
}

void char_avance(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_t,c->directionc,c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_b,c->directionc,c->vitesse_c);

  translation_poly_vecteur(c->c,c->directionc,c->vitesse_c);
  translation_poly_vecteur(c->t,c->directionc,c->vitesse_c);
  translation_poly_vecteur(c->t_pour_afficher,c->directionc,c->vitesse_c);
  
}

void char_recule(char3p c){
  appliquer_vecteur_a_point(c->centre,c->directionc,-c->vitesse_c);

  appliquer_vecteur_a_point(c->devant,c->directionc,-c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_t,c->directionc,-c->vitesse_c);
  appliquer_vecteur_a_point(c->devant_b,c->directionc,-c->vitesse_c);
  
  translation_poly_vecteur(c->c,c->directionc,-c->vitesse_c);
  translation_poly_vecteur(c->t,c->directionc,-c->vitesse_c);
  translation_poly_vecteur(c->t_pour_afficher,c->directionc,-c->vitesse_c);
}


void char_droite(char3p c){
  rotation_points(c->devant,c->centre,-c->vitesse_rotation_c);
  rotation_points(c->devant_t,c->centre,-c->vitesse_rotation_c);
  //rotation_points(c->devant_b,c->centre,-c->vitesse_rotation_c);

  re_calcule_un_vecteur(c->centre,c->devant,c->directionc);
  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_c-=c->vitesse_rotation_c;
  c->degre_t-=c->vitesse_rotation_t;

  rotation_poly(c->c,c->centre,-c->vitesse_rotation_c);
  rotation_poly(c->t,c->centre,-c->vitesse_rotation_c);
  rotation_poly(c->t_pour_afficher,c->centre,-c->vitesse_rotation_c);
}

void char_gauche(char3p c){
  rotation_points(c->devant,c->centre,c->vitesse_rotation_c);
  rotation_points(c->devant_t,c->centre,c->vitesse_rotation_c);
  //rotation_points(c->devant_b,c->centre,c->vitesse_rotation_c);
  
  re_calcule_un_vecteur(c->centre,c->devant,c->directionc);
  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);

  c->degre_c+=c->vitesse_rotation_c;
  c->degre_t+=c->vitesse_rotation_t;

  rotation_poly(c->c,c->centre,+c->vitesse_rotation_c);
  rotation_poly(c->t,c->centre,+c->vitesse_rotation_c);
  rotation_poly(c->t_pour_afficher,c->centre,+c->vitesse_rotation_c);
}


void tourelle_droite(char3p c){
  rotation_points(c->devant_t,c->centre,-c->vitesse_rotation_t);

  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_t-=c->vitesse_rotation_t;

  rotation_poly(c->t,c->centre,-c->vitesse_rotation_t);
  rotation_poly(c->t_pour_afficher,c->centre,-c->vitesse_rotation_t);
}

void tourelle_gauche(char3p c){
  rotation_points(c->devant_t,c->centre,+c->vitesse_rotation_t);

  re_calcule_un_vecteur(c->centre,c->devant_t,c->directiont);
  
  c->degre_t+=c->vitesse_rotation_t;

  rotation_poly(c->t,c->centre,+c->vitesse_rotation_t);
  rotation_poly(c->t_pour_afficher,c->centre,+c->vitesse_rotation_t);
}


void bouclier_gauche(char3p c){
  rotation_points(c->devant_b,c->centre,+c->vitesse_rotation_b);
  c->degre_b+=c->vitesse_rotation_b;
}

void bouclier_droite(char3p c){
  rotation_points(c->devant_b,c->centre,-c->vitesse_rotation_b);
  c->degre_b-=c->vitesse_rotation_b;
}

void activer_bouclier(char3p c){
  c->bouclier_active=1;
}

void stop_bouclier(char3p c,double temps){
  c->bouclier_active=0;
  c->temps_stop_active=temps;
}





void afficher_char(char3p c,GLuint t_c){
  polygone poly =c->c;
  Points p1,p2,p3,p4;
  activer_texturing();
  bind_texture(t_c);
  glBegin(GL_QUADS);
  glColor3ub(255,255,255);
  //glColor3ub(((1000.0-c->pv)/1000.0)*255,(c->pv/1000.0)*255,0);
  p1=get_index(0,poly);
  p2=get_index(1,poly);
  p3=get_index(2,poly);
  p4=get_index(3,poly);
  glTexCoord2d(0.0,0.3645); glVertex2d(p1->x,p1->y);
  glTexCoord2d(0.2425,0.3645); glVertex2d(p2->x,p2->y);
  glTexCoord2d(0.2425,0.0); glVertex2d(p3->x,p3->y);
  glTexCoord2d(0.0,0.0); glVertex2d(p4->x,p4->y); 
  glEnd();
  desactiver_texturing();
}

void afficher_tourelle(char3p c,GLuint t_c,TTF_Font * font){
  polygone poly =c->t_pour_afficher;
  Points p1,p2,p3,p4;
  Points p5,p6,p7,p8;
  Vecteurs v,v2;
  
  int num;
  char s[10];
  activer_texturing();
  bind_texture(t_c);
  glBegin(GL_QUADS);
  glColor3ub(255,255,255);
  //glColor3ub(((1000.0-c->pv)/1000.0)*255,(c->pv/1000.0)*255,0);
  p1=get_index(0,poly);
  p2=get_index(1,poly);
  p3=get_index(2,poly);
  p4=get_index(3,poly);
  glTexCoord2d(0.263,0.4185); glVertex2d(p1->x,p1->y);
  glTexCoord2d(0.4635,0.4185); glVertex2d(p2->x,p2->y);
  glTexCoord2d(0.4635,0.0); glVertex2d(p3->x,p3->y);
  glTexCoord2d(0.263,0.0); glVertex2d(p4->x,p4->y); 
  glEnd();

  num=c->numero_char;
  sprintf(s,"%d",num);


  v2=cree_vecteur_2p(p1,p2);

  p7=cree_point(p1->x,p1->y);
  p8=cree_point(p2->x,p2->y);
  
  if(num<10){
    appliquer_vecteur_a_point(p8,v2,-0.3);
    appliquer_vecteur_a_point(p7,v2,0.3);
  }
  else{
    appliquer_vecteur_a_point(p8,v2,-0.2);
    appliquer_vecteur_a_point(p7,v2,0.2);
  }
  v=cree_vecteur_2p(p2,p3);

  p6=cree_point(p7->x,p7->y);
  p5=cree_point(p8->x,p8->y);

  appliquer_vecteur_a_point(p5,v,0.4);
  appliquer_vecteur_a_point(p6,v,0.4);
  
  ecrire_texte_taille(font,
		      ((1000.0-c->pv)/1000.0)*255,(c->pv/1000.0)*255,0,
		      p7,p8,p5,p6,s);
  
  desactiver_texturing();
  libere_points(p5);
  libere_points(p6);
  libere_points(v);
  libere_points(v2);
}

void afficher_bouclier(char3p c){
  double i;
  double degre_actu=c->degre_b-c->largeur_b;
  double degre_step=c->largeur_b/20.0;
  if(c->bouclier_active){
    glColor3ub(((300.0-c->pv_bouclier)/300.0)*255,0.0,(c->pv_bouclier/300.0)*255);
  }
  else{
    glColor3ub(100.0,100.0,100.0);
  }
  glBegin(GL_LINE_LOOP);
  for(i=degre_actu;i<=c->degre_b+c->largeur_b;i+=degre_step){
    glVertex2d(c->centre->x+c->rayon_max_b*cos(i*(M_PI/180.0)),
	       c->centre->y+c->rayon_max_b*sin(i*(M_PI/180.0)));
  }
  for(i=i-degre_step;i>=c->degre_b-c->largeur_b;i-=degre_step){
    glVertex2d(c->centre->x+c->rayon_min_b*cos(i*(M_PI/180.0)),
	       c->centre->y+c->rayon_min_b*sin(i*(M_PI/180.0)));
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex2d(c->centre->x,c->centre->y);
  glVertex2d(c->devant_b->x,c->devant_b->y);
  glEnd();
  
}

void afficher_liste_chars(liste chars,GLuint t_c,TTF_Font *font){
  char3p c;
  if(!est_list_vide(chars)){
    c=renvoie_sommet_liste(chars);

    if(c->pv>0){
    
      afficher_char(c,t_c);
      afficher_tourelle(c,t_c,font);
      afficher_bouclier(c);
    }
    afficher_liste_chars(liste_sans_premier(chars),t_c,font);
    
  }
}

int est_en_collisions_avec_un_autre(char3p c,liste l_char){
  char3p c2;
  if(!est_list_vide(l_char)){
    c2=renvoie_sommet_liste(l_char);
    if(c!=c2 && c2->pv >0){
      if(polygone_dans_polygone(c->c,c2->c)||polygone_dans_polygone(c->t,c2->c)||polygone_dans_polygone(c->c,c2->t)||polygone_dans_polygone(c->t,c2->t)){
	return 1;
      }
    }
    return est_en_collisions_avec_un_autre(c,liste_sans_premier(l_char));
  }
  return 0;
}

int est_en_collision_avec_obstacle(char3p c, Obstacle o){
  
  return polygone_dans_polygone(o->p,c->c)||polygone_dans_polygone(o->p,c->t);
}

int est_en_collision_dans_zone(char3p c, liste l_zone){
  Obstacle o;
  if(!(est_list_vide(l_zone))){
    o=renvoie_sommet_liste(l_zone);
    if(est_en_collision_avec_obstacle(c,o)){
      return 1;
    }
    return est_en_collision_dans_zone(c,liste_sans_premier(l_zone));
  }
  return 0;
}

int est_collision_avec_map(char3p c,liste map){
  Zone z;
  if(!(est_list_vide(map))){
    z=renvoie_sommet_liste(map);
    if(polygone_dans_polygone(z->p_zone,c->c)||polygone_dans_polygone(z->p_zone,c->t)){
      if(est_en_collision_dans_zone(c,z->l_obstacle)){
	return 1;
      }
    }
    return est_collision_avec_map(c,liste_sans_premier(map));
  } 
  return 0;
}


void retirer_pv(char3p c,double pv,int id_fm){
  reponse_t rep;
  Points p;
  Vecteurs v;
  c->pv-=pv;
  rep.mtype=10;
  rep.numero_char=c->numero_char;
  if(c->pv<=0){
    //mort
    p=cree_point(-100.0,-100.0);
    v=cree_vecteur_2p(c->centre,p);
    translation_char_vec(c,v,1.0);
    rep.type=-100;
    libere_points(p);
    libere_points(v);
  }
  else{
    //toucher mais toujours debout rassure toi
    rep.type=100;
  }
  envoyer_au_serveur(id_fm,rep);
}

int est_en_collision_avec_bouclier_point(char3p c,Points p){
  double distance=distance_2_points(c->centre,p);
  double degre;
  if(distance < c->rayon_max_b && distance > c->rayon_min_b ){
    degre=degre_de_2_points(c->centre,c->devant_b,p);
    if(degre<0){
      degre=-degre;
    }
    if(degre<c->largeur_b){
    return 1;
    }
  }
  return 0;
}

int est_en_collision_avec_bouclier(char3p c,polygone p){
  Points po;
  if(c->bouclier_active){
    if(!est_list_vide(p)){
      po=renvoie_sommet_liste(p);
      if(est_en_collision_avec_bouclier_point(c,po)){
	return 1;
      }
      return est_en_collision_avec_bouclier(c,liste_sans_premier(p));
    }
  }
  return 0;
}


void translation_char_vec(char3p c,Vecteurs v,double coef){

  appliquer_vecteur_a_point(c->centre,v,coef);
  appliquer_vecteur_a_point(c->devant,v,coef);
  appliquer_vecteur_a_point(c->devant_t,v,coef);
  appliquer_vecteur_a_point(c->devant_b,v,coef);
  
  translation_poly_vecteur(c->c,v,coef);
  translation_poly_vecteur(c->t,v,coef);
  translation_poly_vecteur(c->t_pour_afficher,v,coef);
}


void regene_bouclier(char3p c,double temps_actu){
  if(c->temps_stop_active+c->temps_regene<= temps_actu && !c->bouclier_active &&c->pv_bouclier!=300.0){
    c->temps_stop_active=temps_actu;
    c->pv_bouclier+=c->regene_bouclier;
  }
}

void regene_bouclier_all_char(liste chars,double temps){
  if(!est_list_vide(chars)){
    regene_bouclier(renvoie_sommet_liste(chars),temps);
    regene_bouclier_all_char(liste_sans_premier(chars),temps);
  }
}
