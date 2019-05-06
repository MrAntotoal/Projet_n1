#ifndef _LISTE_H
#define _LISTE_H

#include <stdio.h>
#include <stdlib.h>
#include "point_vecteur.h"

typedef void * elem;
typedef struct cellule{
  elem objet;
  struct cellule * suivant;
}struct_cellule;

typedef struct_cellule * liste;

/*Créer une liste vide*/
liste list_vide();

/*Fonction qui teste si la liste est vide ou pas*/
int est_list_vide(liste l);

/*
Fonction qui prends en argument un type "elem" et un type "liste".
Elle insère l'élément à la liste.
*/
liste insere_elem_liste(liste l,elem elem);

/*Insere l'elem au debut de la liste*/
liste empiler(liste l, elem e);

elem renvoie_sommet_liste(liste l);

/*
Fonction qui prend un type "liste" et qui retourne un type "elem".
Elle renvoie l'elem qui est en sommet de liste et le supprime
*/
elem depiler(liste l);

/*
Fonction qui prends un type "liste" en argument et qui retourne un type "liste".
Modifie la liste en supprimant le premier élément de celle-ci et qui renvoie cette liste modifié.
*/
liste supprimer_premier_liste(liste l);

/*Fonction qui retourne la longueur de la liste passée en argument*/
int longueur_liste(liste l);

/*Fonction qui supprime la liste passée en argument*/
void supprime_liste(liste l);

/*Fonction qui retourne un type "liste" sans le premier de celle passée en argument*/
liste liste_sans_premier(liste l);

/*
Fonction qui retourne un type "liste".
Elle concatène 2 listes passées en arguments
*/
liste concat_liste(liste l1,liste l2);

liste supprime_elem(liste l,elem e);

/*Fonction qui retoune 1 si l'élèment est dans la liste et 0 sinon*/
int est_dans_liste(liste l ,elem e);

/*
Fonction qui prend un type "liste" en argument et qui retourne un type "liste"
Elle parcourt la liste et supprime les doublons
*/
liste suppr_doublons_coord(liste l);

/*affichage d'une liste*/
void affiche_liste(liste l);

elem get_last_elem(liste l);

elem get_index(int index,liste l);


void libere_liste_point(liste l);

#endif
