#include <stdlib.h>
#include <stdio.h>

void *alloc_mem(int nombre,int size_of_type);
void *alloc_mem_0(int nombre,int size_of_type);
void *re_alloc_mem(void **p,int nombre,int size_of_type);
void libere_mem(void *p);
void libere(void *pt);
void libere_mem_2(void **p);
