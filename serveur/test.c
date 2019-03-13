#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "equipe.h"

int main(int argc, char *argv[]) {
    printf("DEBUT\n");
    //fflush(stdout);
    Client c1 = {0};
    Client c2 = {0};
    Client r1 = {0};
    Client r2 = {0};
    init_lexico();
    c1.pseudo = inserer_lexeme("Chef1");
    c2.pseudo = inserer_lexeme("Chef2");
    r1.pseudo = inserer_lexeme("Rej1");
    r2.pseudo = inserer_lexeme("Rej2");
    init_equipe();

    creer_equipe(&c1);
    creer_equipe(&c2);

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


    printf("FIN\n");
    exit(0);
}
