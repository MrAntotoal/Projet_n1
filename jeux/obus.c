#include "obus.h"

Obus cree_obus(char3p c){
  Obus o;
  o=alloc_mem(1,sizeof(obus));

  o->tireur=c;
  o->dmg=1;
  o->direction=cree_vecteur_2p(c->centre,c->devant_t);
  o->vitesse=7;
  o->centre=cree_point(c->centre->x,c->centre->y);
  o->p=cree_polygone_d(4,
		       o->centre->x+TAILLE_X_O,o->centre->y-TAILLE_Y_O,
		       o->centre->x+TAILLE_X_O,o->centre->y+TAILLE_Y_O,
		       o->centre->x-TAILLE_X_O,o->centre->y+TAILLE_Y_O,
		       o->centre->x-TAILLE_X_O,o->centre->y-TAILLE_Y_O);
  rotation_poly(o->p,c->centre,c->degre_t);
  o->dega=100.0;
  return o;
}


void obus_avance(Obus o){
  appliquer_vecteur_a_point(o->centre,o->direction,o->vitesse);

  translation_poly_vecteur(o->p,o->direction,o->vitesse);
}

int obus_touche_cible(Obus o,liste l_char,int id_fm){
  char3p c2;
  if(!est_list_vide(l_char)){
    c2=renvoie_sommet_liste(l_char);
    if(c2!=o->tireur){
      if(polygone_dans_polygone(o->p,c2->c)||polygone_dans_polygone(o->p,c2->t)){// ici il faudrais faire les tests sur un autre poly (pour eviter les bug tmtc)

	
	//inflige des dmg
	retirer_pv(c2,o->dega,id_fm);
	//envoie msg au serveur
	

	//test pour les auters
	obus_touche_cible(o,liste_sans_premier(l_char),id_fm);
	return 1;
      }
    }
    return obus_touche_cible(o,liste_sans_premier(l_char),id_fm);
  }
  return 0;
}

int en_collision_avec_obstacle(Obus o,Obstacle ob){
  return polygone_dans_polygone(ob->p,o->p);
}

int obus_touche_un_obstacle(liste l_obstacle,Obus o){
  Obstacle ob;
  if(!(est_list_vide(l_obstacle))){
    ob=renvoie_sommet_liste(l_obstacle);
    if(en_collision_avec_obstacle(o,ob)){
      printf("touche obsacle %d \n",ob->type);
      afficher_polygone(ob->p);
      return 1;
    }  
    return obus_touche_un_obstacle(liste_sans_premier(l_obstacle),o);
  } 
  return 0;
}

int obus_touche_map(liste l_zone,Obus o){
  Zone z;
  if(!(est_list_vide(l_zone))){
    z=renvoie_sommet_liste(l_zone);
    if(polygone_dans_polygone(z->p_zone,o->p)){
      if(obus_touche_un_obstacle(z->l_obstacle,o)){
	return 1;
      }
    }
    return obus_touche_map(liste_sans_premier(l_zone),o);
  } 
  return 0;
}
void libere_obus(Obus o){
  libere(o->direction);
  libere(o->centre);
  libere(o);
}

liste traitement_tous_obus(liste l_obus,liste l_char,liste l_zone,int id_fm,GLuint t_o){
  Obus o;
  if(!est_list_vide(l_obus)){
    o=renvoie_sommet_liste(l_obus);
    l_obus=supprime_elem(l_obus,o);
    l_obus=traitement_tous_obus(l_obus,l_char,l_zone,id_fm,t_o);
    if(!obus_touche_cible(o,l_char,id_fm)&&!obus_touche_map(l_zone,o)){
      obus_avance(o);
      afficher_obus(o,t_o);
      return insere_elem_liste(l_obus,o);
    }
    else{
      printf("toucher\n");
      libere_obus(o);
      return l_obus;
    }
  }
  return list_vide();
}


void afficher_obus(Obus o,GLuint t_o){
  polygone poly =o->p;
  Points p1,p2,p3,p4;
  activer_texturing();
  bind_texture(t_o);
  glBegin(GL_QUADS);
  glColor3ub(255,255,255);
  //glColor3ub(((1000.0-c->pv)/1000.0)*255,(c->pv/1000.0)*255,0);
  p1=get_index(0,poly);
  p2=get_index(1,poly);
  p3=get_index(2,poly);
  p4=get_index(3,poly);
  glTexCoord2d(0.1385,0.93); glVertex2d(p1->x,p1->y);
  glTexCoord2d(0.1385,0.874); glVertex2d(p2->x,p2->y);
  glTexCoord2d(0.1215,0.874); glVertex2d(p3->x,p3->y);
  glTexCoord2d(0.1215,0.93); glVertex2d(p4->x,p4->y); 
  glEnd();
  desactiver_texturing();
}


/*
void avance_tous_obus(liste l_obus){
  Obus o;
  if(!est_liste_vide(l_obus)){
    o=renvoie_sommet_liste(l_obus);
    obus_avance(o);
    avance_tous_obus(liste_sans_premier(l_obus));
  }
}

void affiche_tous_obus(liste l_obus){
  Obus o;
  if(!est_liste_vide(l_obus)){
    o=renvoie_sommet_liste(l_obus);
    affiche_poly(o->p,255,0,0);
    affiche_tous_obus(liste_sans_premier(l_obus));
  }
}



liste boucle_traitement_obus(liste l_obus,liste l_char){
  avance_tous_obus(l_obus);
  
}

*/

