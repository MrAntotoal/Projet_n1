#include "sauvegarde.h"


void enregistrer_point(FILE *f,Points p){
  if(p!=NULL){
    fprintf(f," debut_point %f %f fin_point ",p->x,p->y);
  }
}


void enregistrer_poly(FILE * f,polygone p){
  if(!est_list_vide(p)){
    fprintf(f," debut_poly \n");
    while(!est_list_vide(p)){
      enregistrer_point(f,renvoie_sommet_liste(p));
      p=liste_sans_premier(p);
    }
    fprintf(f," fin_poly \n");
  }
}

void enregistrer_reap(FILE *f,liste p){
  if(!est_list_vide(p)){
    fprintf(f," debut_reap \n");
    while(!est_list_vide(p)){
      enregistrer_point(f,renvoie_sommet_liste(p));
      p=liste_sans_premier(p);
    }
    fprintf(f," fin_reap \n");
  }
}


int enregistrer_all(char * fichier_sortie,liste l_poly, liste l_zones,liste l_reap){
  FILE * f;
  liste l_inter_p,l_inter_z;
  polygone zone, obs;
  f=fopen(fichier_sortie,"w");
  if(f==NULL){
    fprintf(stderr,"impossible d'ouvrir le fichier %s\n",fichier_sortie);
    exit(-1);
  }
  l_inter_p=l_poly;
  l_inter_z=l_zones;
  while(!est_list_vide(l_inter_z)){
    zone=renvoie_sommet_liste(l_inter_z);
    fprintf(f," debut_z\n ");
    enregistrer_poly(f,zone);

    while(!est_list_vide(l_inter_p)){
      obs=renvoie_sommet_liste(l_inter_p);
      if(obs!=zone &&
	 !est_dans_liste(l_inter_z,obs) &&
	 polygone_dans_polygone(zone,obs)){
	enregistrer_poly(f,obs);
      }
      l_inter_p=liste_sans_premier(l_inter_p);
    }
    l_inter_p=l_poly;
    fprintf(f," fin_z \n\n");
    l_inter_z=liste_sans_premier(l_inter_z);
  }
  enregistrer_reap(f,l_reap);
  fclose(f);
  return 1;
}
