
#include "liste.h"

/*Créer une liste vide*/
liste list_vide(){
  return NULL;
}

/*Fonction qui teste si la liste est vide ou pas*/
int est_list_vide(liste l){
  return (l==NULL);
}

/*
Fonction qui prends en argument un type "elem" et un type "liste".
Elle insère l'élément à la liste.
*/
liste insere_elem_liste(liste l,elem elem){
  liste l_a=(liste)alloc_mem(1,sizeof(struct_cellule));
  liste lt=l;
  l_a->objet=elem;
  l_a->suivant=NULL;
  if(l==NULL){
    return l_a;
  }
  while(lt->suivant!=NULL){
    lt=lt->suivant;
  }
  lt->suivant=l_a;
  return l;
}

liste empiler(liste l, elem e){
  liste l_a=(liste)alloc_mem(1,sizeof(struct_cellule));
  l_a->objet=e;
  l_a->suivant=NULL;
  if(l==NULL){
    return l_a;
  }
  l_a->suivant=l;
  return l_a;
}

/*
Fonction qui prend un type "liste" et qui retourne un type "elem".
Elle renvoie l'elem qui est en sommet de liste.
*/
elem renvoie_sommet_liste(liste l){
  return l->objet;
}


/*
Fonction qui prends un type "liste" en argument et qui retourne un type "liste".
Modifie la liste en supprimant le premier élément de celle-ci et qui renvoie cette liste modifié.
*/
elem depiler(liste l){
  liste suivant;
  elem e;
  suivant=l;
  e=suivant->objet;
  l=l->suivant;
  libere_mem(&suivant);
  return e;
}

/*Fonction qui retourne la longueur de la liste passée en argument*/
int longueur_liste(liste l){
  if(est_list_vide(l)){
    return 0;
  }
  return 1 + longueur_liste(l->suivant);
}

/*Fonction qui supprime la liste passée en argument*/
void supprime_liste(liste l){
  if(!est_list_vide(l)){
    supprime_liste(l->suivant);
    libere(l);
  }
}
/*
liste supprime_elem(liste l,elem e){
  liste prochaine;
  if(e==l->objet){
    prochaine=l->suivant;
    libere(l);
    return prochaine;
  }
  else{
    return l->suivant=supprime_elem(l->suivant,e);
  }
  }*/

liste supprime_elem(liste l,elem e){
  liste l_i=l;
  liste ef;
  if(l_i==NULL){
    return NULL;
  }
  if(l_i->objet==e){
    ef=l_i->suivant;
    libere(l_i->objet);
    libere(l_i);
    return ef;
  }
  while(l_i->suivant!=NULL){
    ef=l_i->suivant;
    if(ef->objet==e){
      printf("trouver \n");
      l_i->suivant=ef->suivant;
      libere(ef->objet);
      libere(ef);
      return l;
    }
    l_i=l_i->suivant;
  }
  printf("pas trouver \n");
  return l;
}


liste supprime_elem_sans_libere(liste l,elem e){
  liste l_i=l;
  liste ef;
  if(l_i==NULL){
    return NULL;
  }
  if(l_i->objet==e){
    ef=l_i->suivant;
    return ef;
  }
  while(l_i->suivant!=NULL){
    ef=l_i->suivant;
    if(ef->objet==e){
      printf("trouver \n");
      l_i->suivant=ef->suivant;
      return l;
    }
    l_i=l_i->suivant;
  }
  printf("pas trouver \n");
  return l;
}

/*Fonction qui retourne un type "liste" sans le premier de celle passée en argument*/
liste liste_sans_premier(liste l){
  return l->suivant;
}

/*
Fonction qui retourne un type "liste".
Elle concatène 2 listes passées en arguments
*/
liste concat_liste(liste l1,liste l2){
  liste lt;
  if(l1==NULL){
    return l2;
  }
  if(l2==NULL){
    return l1;
  }
  lt=l1;
  while(lt->suivant!=NULL){
    lt=lt->suivant;
  }
  lt->suivant=l2;
  return l1;
}

/*Fonction qui retoune 1 si l'élèment est dans la liste et 0 sinon*/
int est_dans_liste(liste l ,elem e){
  if (l==NULL){
    return 0;
  }
  if(l->objet == e){
    return 1;
  }
  return est_dans_liste(l->suivant,e);
}

/*affichage d'une liste*/
void affiche_liste(liste l)
{
  liste p=l;

  while(!est_list_vide(p))
    {
      printf("%p -> ",p->objet);
      p=p->suivant;
    }
  printf("\n");
}

elem get_last_elem(liste l){
  int taille = longueur_liste(l);
  liste tmp = l;
  for(int i =0; i < taille-1; i++)
    tmp = tmp->suivant;
  return tmp->objet;

}


elem get_index(int index,liste l){
  if(index==0){
    return renvoie_sommet_liste(l);
  }
  return get_index(index-1,liste_sans_premier(l));
}


liste insere_elem_apres_un_autre(elem e,liste l,elem e_a_insere){
  liste l_a;
  liste l_inter=l;
  while (l!=NULL){
    if(l->objet==e){
      l_a=(liste)alloc_mem(1,sizeof(struct_cellule));
      l_a->objet=e_a_insere;
      l_a->suivant=l->suivant;
      l->suivant=l_a;
      break;
    }
    else{
      l=l->suivant;
    }
  }
  return l_inter;
}
