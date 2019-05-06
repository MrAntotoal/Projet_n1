/**********************************************************/
/*                ANALYSE_LEXICOGRAPHIQUE.C               */
/**********************************************************/

#include "analyse_lexicographique.h"

/* table stockage hash code */

void ajoute_type_base(){
  inserer_lexeme("integer");
  inserer_lexeme("real");
  inserer_lexeme("bool");
  inserer_lexeme("char");
}

/* renvoie l'index de la position dans le tableau lexico_table_lex,
si il n'appartient pas deja on l'ajoute et on renvoie sa position
sinon on renvoie l'index de sa position */
int inserer_lexeme(char *lexeme){
  int hc=calcul_hash_code(lexeme);
  int annule=1;
  if(lexico_hash_code_table[hc]==-1) //pas de precedent dans la table hash
  {
    #ifdef DEBUG_MODE
    printf("Pas dans data\n");
    #endif
    lexico_hash_code_table[hc]=lexico_compteur_table_lex; //index du data tab lex
    strcpy(lexico_table_lex[lexico_compteur_table_lex].idf,lexeme);
    //printf("%s\n%s\n",lexeme,lexico_table_lex[lexico_compteur_table_lex].idf);
    lexico_table_lex[lexico_compteur_table_lex].taille=strlen(lexeme);
    int tmp=lexico_compteur_table_lex;
    lexico_compteur_table_lex++;
    return tmp;
  }

  int actu=lexico_hash_code_table[hc],sauv_actu;
  int taille_lexeme=strlen(lexeme);
  //printf("%d ",taille_lexeme);
  while(actu!=-1)//table hash a un index du data tab lex
  {
    //regarde si dedans taille
    if(taille_lexeme==lexico_table_lex[actu].taille)
    {
      if(strcmp(lexeme,lexico_table_lex[actu].idf)==0)//par string
      {//identique
        annule=0;
        #ifdef DEBUG_MODE
        printf("deja dedans\n");
        #endif
        break;
      }
      sauv_actu=actu;
      actu=lexico_table_lex[actu].suivant;//on continue
      #ifdef DEBUG_MODE
      printf("On continue\n");
      #endif
    }
    else
    {
      sauv_actu=actu;
      actu=lexico_table_lex[actu].suivant;//on continue
      #ifdef DEBUG_MODE
      printf("On continue 2\n");
      #endif
    }
  }
  if(annule==1)//pas deja dedans
  {
    #ifdef DEBUG_MODE
    printf("Pas deja dedans\n");
    #endif
    strcpy(lexico_table_lex[lexico_compteur_table_lex].idf,lexeme);//ajoute
    lexico_table_lex[lexico_compteur_table_lex].taille=strlen(lexeme);
    //printf("taille %d",lexico_table_lex[lexico_compteur_table_lex].taille);
    lexico_table_lex[sauv_actu].suivant=lexico_compteur_table_lex;
    //printf("index %d   suivant %d",sauv_actu,lexico_table_lex[sauv_actu].suivant);
    int tmp=lexico_compteur_table_lex;
    lexico_compteur_table_lex++;
    return tmp;
  }
  else
  {
    return actu;//sinon renvoie son index
  }

}

// -1 est dans 0 pas dedans
int est_dans_table(char * lexeme){
  int hc=calcul_hash_code(lexeme);
  int annule=1;
  if(lexico_hash_code_table[hc]==-1) //pas de precedent dans la table hash
  {
    #ifdef DEBUG_MODE
    printf("Pas dans data\n");
    #endif
    return 0;
  }

  int actu=lexico_hash_code_table[hc];
  int taille_lexeme=strlen(lexeme);
  //printf("%d ",taille_lexeme);
  while(actu!=-1)//table hash a un index du data tab lex
  {
    //regarde si dedans taille
    if(taille_lexeme==lexico_table_lex[actu].taille)
    {
      if(strcmp(lexeme,lexico_table_lex[actu].idf)==0)//par string
      {//identique
        annule=0;
        #ifdef DEBUG_MODE
        printf("deja dedans\n");
        #endif
        return -1;
      }
      actu=lexico_table_lex[actu].suivant;//on continue
      #ifdef DEBUG_MODE
      printf("On continue\n");
      #endif
    }
    else
    {
      actu=lexico_table_lex[actu].suivant;//on continue
      #ifdef DEBUG_MODE
      printf("On continue 2\n");
      #endif
    }
  }
  if(annule==1)//pas deja dedans
  {
    #ifdef DEBUG_MODE
    printf("Pas deja dedans\n");
    #endif
    return 0;
  }
  else
  {
    return -1;
  }
}


/* renvoie un lexeme, prends l'index du lexeme dans le tableau
lexico_table_lex */
char* get_lexeme(int index_t_lex){
  return lexico_table_lex[index_t_lex].idf;
}

/* met a -1 les cases du tableau lexico_hash_code_table */
void init_hash_array(){
  memset(lexico_hash_code_table,-1,TAILLE_HASH_TABLE*sizeof(int));
}

/* met a -1 le champ suivant et table du tableau lexico_table_lex*/
void init_data_array(){
  memset(lexico_table_lex,-1,TAILLE_TABLE_LEX*sizeof(lex_data_table));
  lexico_compteur_table_lex=0;
}

/* renvoie le hash code (entier) correspondant au lexeme entree*/
int calcul_hash_code(char *lexeme){
  int lenght=0;
  int res=0;
  lenght=strlen(lexeme);
  //printf("%d\n",lenght);
  for(int i=0;i<lenght;i++)
  {
    res+=lexeme[i];
  }
  return res%32;
}

/* affiche le tableau lexico_table_lex jusqu'a lexico_compteur_table_lex (dernier element) */
void afficher_data_array(){
  for(int i=0;i<TAILLE_TABLE_LEX;i++)
  if(lexico_table_lex[i].taille==0 || lexico_table_lex[i].taille==-1){
    ;
  }
  else{
    printf("index %d  | idf : %s  | taille %d |  index suiv %d\n",i,lexico_table_lex[i].idf,lexico_table_lex[i].taille,lexico_table_lex[i].suivant);
  }
}

/* affiche le tableau lexico_hash_code_table */
void afficher_hash_array(){
  for(int i=0;i<TAILLE_HASH_TABLE;i++)
  {
    if(lexico_hash_code_table[i]!=-1)
    printf("index hash %d  |  index data %d\n",i,lexico_hash_code_table[i]);
  }
}

void init_lexico(){
  init_hash_array();
  init_data_array();
}

void enregistrement_hashcode(){
  FILE *fichier;
  char *nom_fichier = "./Enregistrement_tables/hash.txt";

  fichier = fopen(nom_fichier, "w");

  if (fichier == (FILE *)NULL)
  {
    printf("Erreur ouverture fichier\n");
    exit(1);
  }

  // Ecriture du fichier
  for(int i=0;i<TAILLE_HASH_TABLE;i++){
    fprintf(fichier,"%d ", lexico_hash_code_table[i]);
  }
  // fin
  fclose(fichier);
}

void chargement_hashcode(){
  FILE *fichier;
  char *nom_fichier = "./Enregistrement_tables/hash.txt";

  fichier = fopen(nom_fichier, "r");

  if (fichier == (FILE *)NULL)
  {
    exit(1);
    printf("Erreur ouverture fichier");
  }
  int i=0;
  // Ecriture du fichier
  while(fscanf(fichier,"%d ", &lexico_hash_code_table[i])!=EOF){
    i++;
  }
  // fin
  fclose(fichier);
}


void enregistrement_lexicographique(){
  FILE *fichier;
  char *nom_fichier = "./Enregistrement_tables/lexico.txt";

  fichier = fopen(nom_fichier, "w");

  if (fichier == (FILE *)NULL)
  {
    exit(1);
    printf("Erreur ouverture fichier");
  }

  // Ecriture du fichier
  for(int i=0;i<TAILLE_TABLE_LEX;i++){
    fprintf(fichier,"%s %d %d\n", lexico_table_lex[i].idf, lexico_table_lex[i].taille, lexico_table_lex[i].suivant);
  }
  // fin
  fclose(fichier);
}

void chargement_lexicographique(){
  FILE *fichier;
  char *nom_fichier = "./Enregistrement_tables/lexico.txt";

  fichier = fopen(nom_fichier, "r");

  if (fichier == (FILE *)NULL)
  {
    exit(1);
    printf("Erreur ouverture fichier");
  }
  int i=0;
  // Ecriture du fichier
  while(fscanf(fichier,"%s %d %d\n", lexico_table_lex[i].idf, &lexico_table_lex[i].taille, &lexico_table_lex[i].suivant)!=EOF){
    i++;
  }
  // fin
  fclose(fichier);
}
