#include "serveur.h"

#define Clean_Buf memset(buffer,'\0',BUF_SIZE)

int GL_SOCK;
void app(void)
{
  SOCKET sock = init_connection();
  GL_SOCK = sock;
  char buffer[BUF_SIZE];
  char truc[BUF_SIZE];
  Clean_Buf;
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

    if(FD_ISSET(sock, &rdfs))
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

      if(est_dans_table(truc) == -1)
      {
        printf("PSEUDO_POK\n");
        strncpy(buffer, PSEUDO_POK, BUF_SIZE - 1);
        write_client(csock,buffer);
        Clean_Buf;
        closesocket(csock); // on déco le client
      }
      else
      {
        // PSEUDO_OK
        printf("PSEUDO_OK\n");

        strncpy(buffer,truc,BUF_SIZE - 1);
        Client c = { csock };

        c.pseudo = inserer_lexeme(truc);
        printf("client : %s connecté\n",buffer);
        Clean_Buf;
        clients[actual] = c;
        actual++;

        /*****************************/
        /*          on répond        */
        /*****************************/

        strncpy(buffer, MENU_JOUEUR"\n", BUF_SIZE - 1);
        write_client(csock,buffer);
        Clean_Buf;
      }
    }
    else
    {

      /* Reception depuis la file de message */
      // rcv
      while (prendre_reponse() != -1) {
        /* traiter les != cas */
      }

      int i = 0;
      for(i = 0; i < actual; i++)
      {
        /* a client is talking */
        if(FD_ISSET(clients[i].sock, &rdfs))
        {
          int c = read_client(clients[i].sock, buffer);
          /* client disconnected */
          if(c == 0)
          {
            closesocket(clients[i].sock);
            remove_client(clients, i, &actual); // on enlève le client

            // strncpy(buffer, client.name, BUF_SIZE - 1);
            // strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
            printf("connection perdu %s\n",get_lexeme(clients[i].pseudo));
            break; // on arrete pour relancer la boucle proprement
          }
          /* switch pour traitement des messages clients */
          char a_comparer[BUF_SIZE];
          strncpy(a_comparer,MODE_JEUX,BUF_SIZE - 1);
          if(fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
          {
            printf("%s\n",a_comparer);
          }
          else
          {
            strncpy(a_comparer,CREER_EQUIPE,BUF_SIZE - 1);
            if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
            {
              printf("%s\n",a_comparer);
              creer_equipe(&clients[i]);
              affiche_equipe(0);
            } else
            {
              strncpy(a_comparer,REJOINDRE_EQUIPE,BUF_SIZE - 1);
              if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
              {
                printf("%s\n",a_comparer);
                rejoindre_equipe(&clients[i],buffer[TAILLE_REJ + 2]); // ' ' puis num
              }
              else
              {
                strncpy(a_comparer,QUITTER_EQUIPE,BUF_SIZE - 1);
                if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
                {
                  printf("%s\n",a_comparer);
                  quitter_equipe(&clients[i]);
                }
                else
                {
                  //strncpy(a_comparer,DEPLACEMENT,BUF_SIZE - 1);
                  strncpy(a_comparer,DEPLACEMENT,BUF_SIZE - 1);
                  if (fast_compare(a_comparer,buffer,TAILLE_DEP) == 0)
                  {
                    // numéro char
                    envoyer_requete(buffer[TAILLE_DEP + 3],buffer[TAILLE_DEP + 2],buffer[TAILLE_DEP + 4]);
                    printf("** D char %d Type %d A repeter %d**\n",buffer[TAILLE_DEP + 3],buffer[TAILLE_DEP + 2],buffer[TAILLE_DEP + 4]);
                  }
                  else
                  {
                    strncpy(a_comparer, TIR,BUF_SIZE - 1);
                    if (fast_compare(a_comparer,buffer,TAILLE_TIR) == 0)
                    {
                      /* alors recuperer selon codage */
                      envoyer_requete(1,FTIR,0);
                      printf("TIR\n");
                    }
                    else
                    {
                      strncpy(a_comparer, RECHARGEMENT,BUF_SIZE - 1);
                      if(fast_compare(a_comparer,buffer,TAILLE_RECH) == 0)
                      {
                        envoyer_requete(buffer[TAILLE_DEP + 2],RECH,0);
                        printf("RECHARGEMENT TX\n");
                      }
                      else
                      {
                        printf("******* %s non reconnu *******\n", buffer);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        Clean_Buf;
      }
    }
  }
  clear_clients(clients, actual);
  end_connection(sock);
}



void clear_clients(Client *clients, int actual)
{
  int i = 0;
  for(i = 0; i < actual; i++)
  {
    closesocket(clients[i].sock);
  }
}

void remove_client(Client *clients, int to_remove, int *actual)
{
  /* we remove the client in the array */
  memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
  /* number client - 1 */
  (*actual)--;
}


int init_connection(void)
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
    fermer_fdm();
    exit(errno);
  }

  if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
  {
    perror("listen()");
    fermer_fdm();
    exit(errno);
  }

  return sock;
}

void end_connection(int sock)
{
  closesocket(sock);
}

int read_client(SOCKET sock, char *buffer)
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

void write_client(SOCKET sock, const char *buffer)
{
  // https://linux.die.net/man/2/send
  if(send(sock, buffer, strlen(buffer), 0) < 0)
  {
    perror("send()");
    exit(errno);
  }
}

void my_handler(int s){
  end_connection(GL_SOCK);
  fermer_fdm();
  exit(-1);
}


int main(int argc, char **argv)
{
  /**********************/
  /* test               */
  /**********************/
  /*char truc[50] = {'t','r','u','c','\0','m','a','c','h','i','n'};
  char bid[50];
  get_msg_next(truc,bid);
  printf("%s\n",bid);
  */

  /***********************************/
  /*         CAPTURE DE CTRL C       */
  /***********************************/
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler = my_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);
  // sigaction(SIGSEGV, &sigIntHandler, NULL);

  /***********************************/
  init_lexico(); // on initialise table hash pour pseudo
  init_equipe();

  if(creer_fdm() == 0)printf("File De Message Créer \n");

  app();
  return EXIT_SUCCESS;
}
