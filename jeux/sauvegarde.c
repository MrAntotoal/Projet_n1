#include "sauvegarde.h"


polygone charger_polygone(FILE *f){
  polygone p=NULL;
  Points po=NULL;
  float x,y;
  char res[500];
  fscanf(f," %s ",res);
  while(strcmp(res,"fin_poly")!=0){
    fscanf(f," %s ",res);
    x=atof(res);
    fscanf(f," %s ",res);
    y=atof(res);
    po=cree_point(x,y);
    p=insere_elem_liste(p,po);
    fscanf(f," %s ",res);
    fscanf(f," %s ",res);
  }
  return p;
}

polygone charger_liste(FILE *f){
  polygone p=NULL;
  Points po=NULL;
  float x,y;
  char res[500];
  fscanf(f," %s ",res);
  while(strcmp(res,"fin_reap")!=0){
    fscanf(f," %s ",res);
    x=atof(res);
    fscanf(f," %s ",res);
    y=atof(res);
    po=cree_point(x,y);
    p=insere_elem_liste(p,po);
    fscanf(f," %s ",res);
    fscanf(f," %s ",res);
  }
  return p;
}

polygone charger_liste_bonus(FILE *f){
  polygone p=NULL;
  Points po=NULL;
  float x,y;
  char res[500];
  fscanf(f," %s ",res);
  while(strcmp(res,"fin_bonus")!=0){
    fscanf(f," %s ",res);
    x=atof(res);
    fscanf(f," %s ",res);
    y=atof(res);
    po=cree_point(x,y);
    p=insere_elem_liste(p,po);
    fscanf(f," %s ",res);
    fscanf(f," %s ",res);
  }
  return p;
}

Zone charger_zone(FILE * f){
  Zone z;
  polygone p_z,p;
  Obstacle o;
  liste l_p=NULL;
  char res[500];
  fscanf(f," %s ",res);
  p_z=charger_polygone(f);
  fscanf(f," %s ",res);
  while(strcmp(res,"fin_z")!=0){
    p=charger_polygone(f);
    o=cree_obstacle(1,p);
    l_p=insere_elem_liste(l_p,o);
    fscanf(f," %s ",res);
  }
  z=cree_zone(p_z,l_p);
  return z;
}


liste charger_map(char *nom_map){
  liste all=NULL;
  liste all_zones=NULL;
  liste liste_reap=NULL;
  liste liste_bonus=NULL;
  char res[500];
  Zone z;
  FILE *f;
  f=fopen(nom_map,"r");
  if(f==NULL){
    fprintf(stderr,"impossible d'ouvrir le fichier %s\n",nom_map);
    return NULL;
  }


  while(fscanf(f," %s ",res)==1){
    if(strcmp(res,"debut_z")==0){
      z=charger_zone(f);
      all_zones=insere_elem_liste(all_zones,z);
    }
    if(strcmp(res,"debut_reap")==0){
      liste_reap=charger_liste(f);
    }
    if(strcmp(res,"debut_bonus")==0){
      liste_bonus=charger_liste_bonus(f);
    }
  }

  all=insere_elem_liste(all,all_zones);
  all=insere_elem_liste(all,liste_reap);
  all=insere_elem_liste(all,liste_bonus);
  return all;
}



