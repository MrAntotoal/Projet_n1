#ifndef CLIENT_H
#define CLIENT_H

#include "serveur.h"

typedef struct
{
   SOCKET sock;
   char name[BUF_SIZE];
}Client;

#endif /* guard */
