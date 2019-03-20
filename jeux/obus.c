#include "obus.h"

Obus cree_obus(char3p c){
  Obus o;
  o=alloc_mem(1,sizeof(obus));

  o->tireur=c;
  o->dmg=1;
  o->direction=cree_vecteur_2p(c->centre,c->devant_t);
  o->vitesse=10;
  o->centre=cree_point(c->centre->x,c->centre->y);
  o->p=cree_polygone_d(4,
		       o->centre->x+TAILLE_X_O,o->centre->y-TAILLE_Y_O,
		       o->centre->x+TAILLE_X_O,o->centre->y+TAILLE_Y_O,
		       o->centre->x-TAILLE_X_O,o->centre->y+TAILLE_Y_O,
		       o->centre->x-TAILLE_X_O,o->centre->y-TAILLE_Y_O);

  return o;
}


void obus_avance(Obus o){
  appliquer_vecteur_a_point(o->centre,o->direction,o->vitesse);

  translation_poly_vecteur(o->p,o->direction,o->vitesse);
}

int obus_touche_cible(Obus o,liste l_char){
   char3p c2;
   polygone p_future;
  if(!est_list_vide(l_char)){
    c2=renvoie_sommet_liste(l_char);
    if(c2!=o->tireur){
      if(polygone_dans_polygone(o->p,c2->c)||polygone_dans_polygone(o->p,c2->t)){// ici il faudrais faire les tests sur un autre poly (pour eviter les bug tmtc)

	
	//inflige des dmg

	 //test pour les auters
	 obus_touche_cible(o,liste_sans_premier(l_char));
	 return 1;
       }
    }
    return obus_touche_cible(o,liste_sans_premier(l_char));
  }
  return 0;
}

void libere_obus(Obus o){
  libere(o->direction);
  libere(o->centre);
  libere(o);
}

liste traitement_tous_obus(liste l_obus,liste l_char){
  Obus o;
  if(!est_list_vide(l_obus)){
    o=renvoie_sommet_liste(l_obus);
    l_obus=supprime_elem(l_obus,o);
    l_obus=traitement_tous_obus(l_obus,l_char);
    if(!obus_touche_cible(o,l_char)){
      obus_avance(o);
      affiche_poly(o->p,255,0,0);
      return insere_elem_liste(l_obus,o);
    }
    else{
      libere_obus(o);
      return l_obus;
    }
  }
  return list_vide();
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

