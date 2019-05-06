#include "allocation_memoire.h"

void *alloc_mem(int nombre,int size_of_type){
  void *p;
  p=malloc(nombre*size_of_type);
  if(p==NULL){
    fprintf(stderr,"erreur allocation_mem");
  }
  return p;
}

void *alloc_mem_0(int nombre,int size_of_type){
  void *p;
  p=calloc(nombre,size_of_type);
  if(p==NULL){
    fprintf(stderr,"erreur allocation_mem");
  }
  return p;
}

void *re_alloc_mem(void **p,int nombre,int size_of_type){
  void *nouv;
  nouv=realloc(*p,nombre*size_of_type);
  if(p==NULL){
    fprintf(stderr,"erreur re-allocation_mem");
    return *p;
  }
  return nouv;
}

void libere_mem_2(void **p){
  if(*p!=NULL){
    free(*p);
  }
  *p=NULL;
}

void libere(void *pt){
    free(pt); 
}

void libere_mem(void *pt){
  void ** adr_pt=(void **) pt;
  if((*adr_pt)!=NULL){
    free(*adr_pt);
  }
    *adr_pt=NULL; 
}
