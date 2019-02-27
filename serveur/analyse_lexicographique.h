/**********************************************************/
/*                ANALYSE_LEXICOGRAPHIQUE.H               */
/**********************************************************/
#ifndef ANALYSE_LEXICOGRAPHIQUE_H
#define ANALYSE_LEXICOGRAPHIQUE_H

#define TAILLE_IDF 30
#define TAILLE_TABLE_LEX 500
#define TAILLE_HASH_TABLE 32

//#define DEBUG_MODE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* structure lexical */
typedef struct data{
  char idf[TAILLE_IDF];
  int taille;
  int suivant;
}lex_data_table;

/* compteur table lexico_table_lex */
int lexico_compteur_table_lex;

/* table lexical */
lex_data_table lexico_table_lex[TAILLE_TABLE_LEX];
int lexico_hash_code_table[TAILLE_HASH_TABLE];

/* renvoie l'index de la position dans le tableau lexico_table_lex,
si il n'appartient pas deja on l'ajoute et on renvoie sa position
sinon on renvoie l'index de sa position */
int inserer_lexeme(char *lexeme);

/* renvoie un lexeme, prends l'index du lexeme dans le tableau
lexico_table_lex */
char *get_lexeme(int index_t_lex);

/* met a -1 les cases du tableau lexico_hash_code_table */
void init_hash_array();

/* met a -1 le champ suivant du tableau lexico_table_lex*/
void init_data_array();

void init_lexico();

/* renvoie le hash code (entier) correspondant au lexeme entree*/
int calcul_hash_code(char *lexeme);

/* affiche le tableau lexico_table_lex jusqu'a lexico_compteur_table_lex (dernier element) */
void afficher_data_array();

/* affiche le tableau lexico_hash_code_table */
void afficher_hash_array();

void enregistrement_hashcode();

void chargement_hashcode();

void enregistrement_lexicographique();

void chargement_lexicographique();


#endif
