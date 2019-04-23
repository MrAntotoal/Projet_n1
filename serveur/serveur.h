#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#include <signal.h>


#include "structure.h"
#include "message_serveur.h"
#include "affich.h"
#include "message.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define PORT	 	1977
#define MAX_CLIENTS 	1000



#include "analyse_lexicographique.h"
#include "strcmp_rapide.h"
#include "equipe.h"
#include "fdm.h"
#include "lobby_afficheur.h"
void app(void);
int init_connection(void);
void end_connection(int sock);
int read_client(SOCKET sock, char *buffer);
void write_client(SOCKET sock, const char *buffer);
void remove_client(int to_remove);
void clear_clients();

void get_msg_next(char *buffer, char *res);

#endif /* guard */
