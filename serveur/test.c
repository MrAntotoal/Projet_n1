#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "equipe.h"

int main(int argc, char *argv[]) {
    printf("DEBUT\n");
    //fflush(stdout);

    Client tab[10];


    Client c1 = {0};
    Client c2 = {0};
    Client r1 = {0};
    Client r2 = {0};
    Client oui = {0};
    init_lexico();
    c1.pseudo = inserer_lexeme("Chef1");
    c2.pseudo = inserer_lexeme("Chef2");
    r1.pseudo = inserer_lexeme("Rej1");
    r2.pseudo = inserer_lexeme("Rej2");
    oui.pseudo = inserer_lexeme("oui");
    tab[0] = c1;
    tab[1] = c2;
    tab[2] = r1;
    tab[3] = r2;
    tab[4] = oui;
    init_equipe();

    creer_equipe(&tab[0]);
    creer_equipe(&tab[1]);
    creer_equipe(&tab[4]);
    creer_equipe(&tab[2]);

    for (int i = 0; i < 4; i++) {
      affiche_equipe(i);
    }
    quitter_equipe(&tab[0]);

    printf("quitter_equipe\n");
    for (int i = 0; i < 3; i++) {
      affiche_equipe(i);
    }
    creer_equipe(&tab[2]);
    for (int i = 0; i < 4; i++) {
      affiche_equipe(i);
    }
/*
    printf("\n********Equipe 0\n");
    affiche_equipe(0);

    printf("\n********Equipe 1\n");
    affiche_equipe(1);

    rejoindre_equipe(&r1,0);
    printf("\n*********Equipe 0\n");
    affiche_equipe(0);

    rejoindre_equipe(&r2,0);
    printf("\n*********Equipe 0\n");
    affiche_equipe(0);

    quitter_equipe(&r1);
    printf("\n*********Equipe 0\n");
    affiche_equipe(0);

    rejoindre_equipe(&r1,0);
    printf("\n*********Equipe 0\n");
    affiche_equipe(0);

    printf("supprimé équipe\n");
    quitter_equipe(&r1);

    printf("\n*********Equipe 0\n");
    affiche_equipe(0);

    creer_equipe(&oui);
    creer_equipe(&r2);
    printf("\n*********Equipe 1\n");
    affiche_equipe(1);
    printf("\n*********Equipe 2\n");
    affiche_equipe(2);
*/
    printf("FIN\n");
    exit(0);
}
