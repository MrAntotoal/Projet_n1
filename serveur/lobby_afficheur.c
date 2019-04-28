#include "lobby_afficheur.h"


int mycmp(const void *a, const void *b){
  Client *a2 = (Client*) a;
  Client *b2 = (Client*) b;
  /*if(fast_compare(get_lexeme(b2->pseudo),get_lexeme(a2->pseudo),TAILLE_IDF) > 0){
    return -1;
  }
  else{
    return 1;
  }*/
  return a2->numEquipe > b2->numEquipe;

}

void debut_html(){
  FILE *fichier;
  char *nom_fichier = "lobby.html";

  fichier = fopen(nom_fichier, "w");

  if (fichier == (FILE *)NULL)
  {
    printf("Erreur ouverture fichier lobby.html\n");
    exit(-1);
  }

  fprintf(fichier, "<link rel=\"stylesheet\" type=\"text/css\" href=\"lobby.css\">");
  fprintf(fichier, "<META HTTP-EQUIV=\"refresh\" CONTENT=\"1\">" );
  fprintf(fichier, "<meta charset=\"UTF-8\">"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "	<div id=\"page-wrap\">");
  fprintf(fichier, "<h2>Bienvenue sur notre jeu, quelques règles et conseils : </h2><br>"
  "<h3>Les équipes sont composées de 3 personnes,<br> il est <strong>fortement</strong> recommandé d'avoir des équipes complètes"
  " et que les 3 joueurs soient assis à côté.</h3><br>" );
  // fin
  fclose(fichier);
}

void refresh_html(){
  FILE *fichier;
  char *nom_fichier = "lobby.html";
  debut_html();
  fichier = fopen(nom_fichier, "a");

  if (fichier == (FILE *)NULL)
  {
    printf("Erreur ouverture fichier lobby.html\n");
    exit(-1);
  }
  qsort(list,nb,sizeof(Client),mycmp);

  for (int i = 0; i < nb; i++) {
    if(i%22 == 0){
      fprintf(fichier, "  </table><table class=\"table\"><thead><tr>"
      "<th>Nom d'utilisateur</th><th>Numéro de l'équipe</th></tr>"
      "</thead><tbody>");
    }
    fprintf(fichier,"<tr><td>%s</td> <td>%d</td></tr>",get_lexeme(list[i].pseudo),list[i].numEquipe + 1);
  }
  // fin
  fclose(fichier);
}

void ajouterChamps(Client c){
  FILE *fichier;
  char *nom_fichier = "lobby.html";
  debut_html();
  list[nb] = c;
  nb++;
  fichier = fopen(nom_fichier, "a");

  if (fichier == (FILE *)NULL)
  {
    printf("Erreur ouverture fichier lobby.html\n");
    exit(-1);
  }
  qsort(list,nb,sizeof(Client),mycmp);

  for (int i = 0; i < nb; i++) {
    if(i%22 == 0){
      fprintf(fichier, "  </div></table><table class=\"table\"><thead><tr>"
      "<th>Nom d'utilisateur</th><th>Numéro d'équipe</th></tr>"
      "</thead><tbody>");
    }
    fprintf(fichier,"<tr><td>%s</td> <td>%d</td></tr>",get_lexeme(list[i].pseudo),list[i].numEquipe + 1);
  }
  // fin
  fclose(fichier);
}

void init_html(){
  nb = 0;
}
