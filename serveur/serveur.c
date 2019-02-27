#include "serveur.h"


static void app(void)
{
  SOCKET sock = init_connection();
  char buffer[BUF_SIZE];
  char truc[BUF_SIZE];
  memset(buffer,'\0',BUF_SIZE);
  /* the index for the array */
  int actual = 0;
  int max = sock;
  /* an array for all clients */
  Client clients[MAX_CLIENTS];

  fd_set rdfs;

  while(1)
  {
    int i = 0;
    FD_ZERO(&rdfs);

    /* add STDIN_FILENO */
    FD_SET(STDIN_FILENO, &rdfs);

    /* add the connection socket */
    FD_SET(sock, &rdfs);

    /* add socket of each client */
    for(i = 0; i < actual; i++)
    {
      FD_SET(clients[i].sock, &rdfs);
    }

    if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
    {
      perror("select()");
      exit(errno);
    }

    /* something from standard input : i.e keyboard */
    if(FD_ISSET(STDIN_FILENO, &rdfs))
    {
      /* stop process when type on keyboard */
      break;
    }
    else if(FD_ISSET(sock, &rdfs))
    {
      /* new client */
      SOCKADDR_IN csin = { 0 };
      size_t sinsize = sizeof(csin);
      int csock = accept(sock, (SOCKADDR *)&csin, (socklen_t *)&sinsize);
      if(csock == SOCKET_ERROR)
      {
        perror("accept()");
        continue;
      }

      /* after connecting the client sends its name */
      if(read_client(csock, buffer) == -1)
      {
        /* disconnected */
        printf("déconnection\n");
        continue;
      }
      /* what is the new maximum fd ? */
      max = csock > max ? csock : max;

      FD_SET(csock, &rdfs);
      strncpy(truc,buffer,BUF_SIZE - 1);
      /*****************************/
      /*    on vérifie le pseudo   */
      /*****************************/
      int bool = 0;
      for (int k = 0; k < actual; k++) {
        printf("%s ! %s\n",clients[k].name,buffer);
        if(strcmp(clients[k].name,buffer) == 0)
        {
          printf("PSEUDO_POK\n");
          strncpy(buffer, PSEUDO_POK, BUF_SIZE - 1);
          write_client(csock,buffer);
          memset(buffer,'\0',sizeof(buffer)); // on efface le buffer
          bool = 1;
          break;
        }
      }
      if(bool == 0)
      {
        // PSEUDO_OK
        printf("PSEUDO_OK\n");

        strncpy(buffer,truc,BUF_SIZE - 1);
        Client c = { csock };
        strncpy(c.name, buffer, BUF_SIZE - 1);
        printf("|%s|%s\n",c.name,buffer);
        printf("client : %s connecté\n",buffer);
        memset(buffer,'\0',sizeof(buffer));
        clients[actual] = c;
        actual++;

        /*****************************/
        /*          on répond        */
        /*****************************/

        strncpy(buffer, MENU_JOUEUR, BUF_SIZE - 1);
        write_client(csock,buffer);
        memset(buffer,'\0',sizeof(buffer)); // on efface le buffer

      }
      else
      {
        // on le déco ?
        closesocket(csock);
        printf("client déco car mauvais pseudo\n");

      }
    }
    else
    {
      int i = 0;
      for(i = 0; i < actual; i++)
      {
        /* a client is talking */
        if(FD_ISSET(clients[i].sock, &rdfs))
        {
          Client client = clients[i];
          int c = read_client(clients[i].sock, buffer);
          /* client disconnected */
          if(c == 0)
          {
            closesocket(clients[i].sock);
            remove_client(clients, i, &actual); // on enlève le client

            // strncpy(buffer, client.name, BUF_SIZE - 1);
            // strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
            printf("connection perdu %s\n",client.name);
            break; // on arrete pour relancer la boucle proprement
          }
          /* switch pour traitement des messages clients */
        }
      }
    }
  }

  clear_clients(clients, actual);
  end_connection(sock);
}



static void clear_clients(Client *clients, int actual)
{
  int i = 0;
  for(i = 0; i < actual; i++)
  {
    closesocket(clients[i].sock);
  }
}

static void remove_client(Client *clients, int to_remove, int *actual)
{
  /* we remove the client in the array */
  memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
  /* number client - 1 */
  (*actual)--;
}


static int init_connection(void)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKADDR_IN sin = { 0 };

  if(sock == INVALID_SOCKET)
  {
    perror("socket()");
    exit(errno);
  }

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;

  if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
  {
    perror("bind()");
    exit(errno);
  }

  if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
  {
    perror("listen()");
    exit(errno);
  }

  return sock;
}

static void end_connection(int sock)
{
  closesocket(sock);
}

static int read_client(SOCKET sock, char *buffer)
{
  int n = 0;

  if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
  {
    perror("recv()");
    /* if recv error we disonnect the client */
    n = 0;
  }
  printf("Reçue ~> %s\n",buffer);
  buffer[n] = 0;

  return n;
}

static void write_client(SOCKET sock, const char *buffer)
{
  // https://linux.die.net/man/2/send
  if(send(sock, buffer, strlen(buffer), 0) < 0)
  {
    perror("send()");
    exit(errno);
  }
}

int main(int argc, char **argv)
{
  /**********************/
  /* test               */
  /**********************/
  char truc[50];
  strcpy(truc,"bidule\0machin\0");
  printf("%s\n",get_msg_next(truc));

  //app();
  return EXIT_SUCCESS;
}

char * get_msg_next(char *buffer){
  char *res = malloc(sizeof(char)*30); // free a la fin
  int cop = 0;
  int nb_zero = 0;
  int i = 0;
  printf("%s\n", buffer);
  while(nb_zero < 2) {
    if(buffer[i] == '\0')
    {
      nb_zero++;
    }
    else
    {
      if(nb_zero == 1)
      {
        res[cop] = buffer[i];
        fprintf(stderr,"|%c|\n", buffer[i]);
        cop++;
      }
    }
    i++;
  }
  return res;
}
