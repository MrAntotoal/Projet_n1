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
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF		"\r\n"
#define PORT	 	1977
#define MAX_CLIENTS 	1000


#include "analyse_lexicographique.h"
#include "strcmp_rapide.h"

static void app(void);
static int init_connection(void);
static void end_connection(int sock);
static int read_client(SOCKET sock, char *buffer);
static void write_client(SOCKET sock, const char *buffer);
static void remove_client(Client *clients, int to_remove, int *actual);
static void clear_clients(Client *clients, int actual);

char * get_msg_next(char *buffer);

#endif /* guard */
