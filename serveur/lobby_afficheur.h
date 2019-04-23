#ifndef _LOBBY_AFF_H
#define _LOBBY_AFF_H

#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "analyse_lexicographique.h"
#include "strcmp_rapide.h"

Client list[NB_EQUIPE_MAX];
int nb;
void debut_html();
void refresh_html();
void ajouterChamps(Client c);
void init_html();
#endif
