#include "point_vecteur.h"

int erreur_malloc(){
  exit(-1);
}

Points cree_point(double x, double y){
  Points p =malloc(sizeof(points));
  if(p==NULL){
    fprintf(stderr,"erreur allocation point\n");
    erreur_malloc();
  }
  p->x=x;
  p->y=y;
  return p;
}


Vecteurs cree_vecteur_2d(double x,double y){
  Vecteurs p =malloc(sizeof(points));
  if(p==NULL){
    fprintf(stderr,"erreur allocation point\n");
    erreur_malloc();
  }
  p->x=x;
  p->y=y;
  return p;
}


Vecteurs cree_vecteur_4d(double x1,double y1,double x2,double y2){
  Vecteurs p =malloc(sizeof(points));
  if(p==NULL){
    fprintf(stderr,"erreur allocation point\n");
    erreur_malloc();
  }
  p->x=x2-x1;
  p->y=y2-y1;
  return p;
}

Vecteurs cree_vecteur_2p(Points p1,Points p2){
  Vecteurs p =malloc(sizeof(points));
  if(p==NULL){
    fprintf(stderr,"erreur allocation point\n");
    erreur_malloc();
  }
  p->x=p2->x-p1->x;
  p->y=p2->y-p1->y;
  return p;
}

Points libere_points(Points p){
  free(p);
  return NULL;
}

void appliquer_vecteur_a_point(Points p, Vecteurs v,double coef){
  p->x+=coef*v->x;
  p->y+=coef*v->y;
}

void translation_x(Points p, double val){
  p->x+=val;
}

void translation_y(Points p,double val){
  p->y+=val;
}


void translation(Points p,double val_x,double val_y){
  p->x+=val_x;
  p->y+=val_y;
}

void modifier_points(Points p,double x, double y){
  p->x=x;
  p->y=y;
}

void rotation_points(Points p, Points p_base,double d){
  Vecteurs OA;
  Points O;
  double teta;
  d=fmod(d,360.0);
  teta=d*(M_PI/180);
  O=cree_point(0.0,0.0);
  OA=cree_vecteur_2p(O,p_base);
  appliquer_vecteur_a_point(p,OA,-1);
  modifier_points(p,
		  p->x*cos(teta)-p->y*sin(teta),
		  p->x*sin(teta)+p->y*cos(teta)
		  );

  appliquer_vecteur_a_point(p,OA,1);
  libere_points(O);
  libere_points((Points)OA);
  
}

double norme_vecteur(Vecteurs v1){
  return sqrt(pow(v1->x,2)+pow(v1->y,2));
}

double distance_2_points(Points p1,Points p2){
  return sqrt(pow(p2->x-p1->x,2)+pow(p2->y-p1->y,2));
}

double produit_scalaire(Vecteurs v1,Vecteurs v2){
  return v1->x*v2->x+v1->y*v2->y;
}

double degre_de_2_points(Points O ,Points A,Points B){
  Vecteurs v1,v2;
  double res;
  v1=cree_vecteur_2p(O,A);
  v2=cree_vecteur_2p(O,B);
  fprintf(stderr,"%f %f %f\n",norme_vecteur(v1),norme_vecteur(v2),produit_scalaire(v1,v2));
  res=acos(produit_scalaire(v1,v2)/(norme_vecteur(v1)*norme_vecteur(v2)));
  libere_points(v1);
  libere_points(v2);
  fprintf(stderr,"%f\n",res);
  return res*180/M_PI;
}


void afficher_point(Points p){
  printf("points : \nx : %f\ny: %f\n",p->x,p->y);
}
