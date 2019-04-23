#include "lobby_afficheur.h"

Client list[NB_EQUIPE_MAX];
int nb = 0;

int mycmp(const void *a, const void *b){
  Client *a2 = (Client*) a;
  Client *b2 = (Client*) b;
  if(fast_compare(get_lexeme(b2->pseudo),get_lexeme(a2->pseudo),TAILLE_IDF) > 0){
    return -1;
  }
  else{
    return 1;
  }
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
  fprintf(fichier, "<META HTTP-EQUIV=\"refresh\" CONTENT=\"2\">" );
  fprintf(fichier, "<meta charset=\"UTF-8\">");
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
      fprintf(fichier, "  </table><table class=\"table\"><thead><tr>"
      "<th>Nom d'utilisateur</th><th>Numéro d'équipe</th></tr>"
      "</thead><tbody>");
    }
    fprintf(fichier,"<tr><td>%s</td> <td>%d</td></tr>",get_lexeme(list[i].pseudo),list[i].numEquipe + 1);
  }
  // fin
  fclose(fichier);
}
