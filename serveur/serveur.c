#include "serveur.h"

#define Clean_Buf memset(buffer,'\0',BUF_SIZE)

int GL_SOCK;
int flag_lobby;
volatile int flag_start;
char **myenvp;
char **args;

/* an array for all clients */
Client clients[MAX_CLIENTS];
/* the index for the array */
int actual = 0;

void lancer_jeux(){
  args = malloc(sizeof(char *) * 101);
  for (int i = 0; i < 100; i++) {
    args[i] = malloc(sizeof(char) * 15);
  }
  args[0] = "../jeux/run";
  args[1] = "0"; // mode de jeux
  sprintf(args[2],"%d",index_equipe);
  for (int p = 0; p < index_equipe; p++) {
    sprintf(args[p+3],"%d",p);
  }
  args[3+index_equipe] = "test";
  args[3+index_equipe+1] = "png";
  args[5 + index_equipe] = NULL;
}


void app(void)
{
  SOCKET sock = init_connection();
  GL_SOCK = sock;
  char buffer[BUF_SIZE];
  char truc[BUF_SIZE];
  Clean_Buf;
  int max = sock;
  fd_set rdfs;

  struct sigaction sig;
  sigemptyset(&sig.sa_mask);
  sigaddset(&sig.sa_mask, SIGUSR1);
  while(1)
  {
    int i = 0;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);

    /* add the connection socket */
    FD_SET(sock, &rdfs);

    /* add socket of each client */
    for(i = 0; i < actual; i++)
    {
      FD_SET(clients[i].sock, &rdfs);
    }

    if(pselect(max + 1, &rdfs, NULL, NULL, NULL,&sig.sa_mask) == -1)
    {
      if(errno != EINTR){
        perror("select()");
        exit(errno);
      }
    }

    /***************************************/
    /* Reception depuis la file de message */
    /***************************************/
    int numero_char;
    while (prendre_reponse() != -1)
    {
      switch (rcv.type)
      {
        /*
        case 30: // conducteur
        case 31: // tireur
        case 32: // bouclier
        printf("Spécial prête\n");
        break;
        */
        case 100:    // toucher
        numero_char = rcv.numero_char;
        #ifdef AFFICHAGE
        printf("Char %d changement de boutton\n",numero_char);
        #endif
        changerBoutton();
        for (int l = 0; l < GL_equipe[numero_char].nb_joueur; l++) {
          Clean_Buf;
          sprintf(truc,NEW_BUTT);
          ecrireNouveauBouton(truc,l);
          #ifdef AFFICHAGE
          printf("NOUVEAU_BOUTTON %s\n",truc);
          #endif
          write_client(GL_equipe[numero_char].membre[l]->sock,truc);
        }

        break;

        case -100:
        //mort
        numero_char = rcv.numero_char;
        #ifdef AFFICHAGE
        printf("Char %d Mort\n",numero_char);
        #endif
        for (int k = 0; k < GL_equipe[numero_char].nb_joueur; k++) {
          write_client(GL_equipe[numero_char].membre[k]->sock,MORT);
        }
        break;
      }
      Clean_Buf;
    }


    if(flag_start == 2){
      flag_start = 0;
      #ifdef AFFICHAGE
      printf("envoie start\n");
      #endif
      for (int o = 0; o < actual; o++) {
        write_client(clients[o].sock,"START \n");
      }
      int pid;
      /*************/
      /* fork jeu  */
      /*************/
      lancer_jeux();
      pid = fork();
      if(pid == -1){
        printf("******** FORK JEU ECHOUE\n");
      }
      if(pid == 0){
        execve("../jeux/run",args,myenvp);
        fprintf(stderr,"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ EXECVE JEU\n");
        kill(getpid(),SIGINT);
      }
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
        #ifdef AFFICHAGE
        printf("déconnection\n");
        #endif
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
        #ifdef AFFICHAGE
        printf("PSEUDO_POK\n");
        #endif
        strncpy(buffer, PSEUDO_POK, BUF_SIZE - 1);
        write_client(csock,buffer);
        Clean_Buf;
        closesocket(csock);
      }
      else
      {
        #ifdef AFFICHAGE
        printf("PSEUDO_OK\n");
        #endif
        strncpy(buffer,truc,BUF_SIZE - 1);
        Client c = { csock };

        c.pseudo = inserer_lexeme(truc);
        #ifdef AFFICHAGE
        printf("client : %s connecté\n",buffer);
        #endif
        Clean_Buf;
        clients[actual] = c;
        actual++;
        strncpy(buffer, MENU_JOUEUR"\n", BUF_SIZE - 1);
        write_client(csock,buffer);
        Clean_Buf;
      }
    }
    else
    {
      if(flag_start == 2){
        flag_start = 0;
        #ifdef AFFICHAGE
        printf("envoie start\n");
        #endif
        for (int o = 0; o < actual; o++) {
          write_client(clients[o].sock,"START \n");
        }
        system("./kill_firefox.sh");
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
            #ifdef AFFICHAGE
            printf("connection perdu %s\n",get_lexeme(clients[i].pseudo));
            #endif
            remove_client(i); // on enlève le client
            break; // on arrete pour relancer la boucle proprement
          }

          /***********************************************/
          /* switch pour traitement des messages clients */
          /***********************************************/

          char a_comparer[BUF_SIZE];
          strncpy(a_comparer,KICK_EQUIPE,BUF_SIZE - 1);
          if(fast_compare(a_comparer,buffer,TAILLE_KICK) == 0){
            char ps[20];
            int role=1;
            sscanf(buffer,"%s %s\n",truc,ps);
            printf("%s\n",ps);
            while(fast_compare(get_lexeme(GL_equipe[clients[i].numEquipe].membre[role]->pseudo),ps,strlen(ps)) != 0){
              printf("strlen %ld\n",strlen(ps));
              role++;
            }
            printf("le role trouver %d le pseudo %s d'id %d\n",role,get_lexeme(GL_equipe[clients[i].numEquipe].membre[role]->pseudo),GL_equipe[clients[i].numEquipe].membre[role]->pseudo);
            affiche_tt_e();
            write_client(GL_equipe[clients[i].numEquipe].membre[role]->sock,KICK_EQUIPE"\n");
            quitter_equipe(GL_equipe[clients[i].numEquipe].membre[role]);
            affiche_tt_e();
            Clean_Buf;
            // ne pas envoyer OK
          }
          else{
            strncpy(a_comparer,ROLE,BUF_SIZE - 1);
            if(fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
            {
              Clean_Buf;
              sprintf(buffer,ROLE" %d\n",position_equipe(clients[i]));
              #ifdef AFFICHAGE
              printf("role : %s\n",buffer);
              #endif
              write_client(clients[i].sock,buffer);
              Clean_Buf;
            }
            else
            {
              strncpy(a_comparer,CREER_EQUIPE,BUF_SIZE - 1);
              if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
              {
                #ifdef AFFICHAGE
                printf("%s\n",a_comparer);
                #endif
                creer_equipe(&clients[i]);

                sprintf(buffer, "%d\n",index_equipe);
                write_client(clients[i].sock,buffer);

                /*******************/
                /* fork pour lobby */
                /*******************/
                if(flag_lobby == 0){ // on ouvre le lobby une fois !
                  #ifdef AFFICHAGE
                  printf("LOBBY DEMANDEE !\n");
                  #endif
                  flag_lobby = 1;
                  system("firefox lobby.html &");
                }
                Clean_Buf;
              } else
              {
                strncpy(a_comparer,REJOINDRE_EQUIPE,BUF_SIZE - 1);
                if (fast_compare(a_comparer,buffer,TAILLE_REJ) == 0)
                {
                  #ifdef AFFICHAGE
                  printf("%s\n",a_comparer);
                  #endif
                  int rej = 0;
                  sscanf(buffer,"%s %d\n",truc,&rej);
                  if(rej > index_equipe || rej <= 0){
                    write_client(clients[i].sock,ERREUR_REJOINDRE"\n");
                    Clean_Buf;
                  }
                  else{
                    if(GL_equipe[i].nb_joueur == 3){
                      write_client(clients[i].sock,ERREUR_REJOINDRE"\n");
                      Clean_Buf;
                    }
                    else{
                      sprintf(buffer,"%s\n",get_lexeme(clients[i].pseudo));
                      rejoindre_equipe(&clients[i],rej - 1);
                      write_client(GL_equipe[clients[i].numEquipe].membre[0]->sock,buffer);
                      Clean_Buf;
                      write_client(clients[i].sock,"OK\n");
                    }
                  }
                }
                else
                {
                  strncpy(a_comparer,QUITTER_EQUIPE,BUF_SIZE - 1);
                  if (fast_compare(a_comparer,buffer,strlen(buffer)) == 0)
                  {
                    #ifdef AFFICHAGE
                    printf("%s\n",a_comparer);
                    #endif
                    quitter_equipe(&clients[i]);
                    Clean_Buf;
                    write_client(clients[i].sock,"OK\n");

                  }
                  else
                  {
                    strncpy(a_comparer,DEPLACEMENT,BUF_SIZE - 1);
                    if (fast_compare(a_comparer,buffer,TAILLE_DEP) == 0)
                    {
                      int numero_char = 0;
                      int type = 0;
                      int repeter = 0;

                      sscanf(buffer,"%s %d %d %d\n",truc,&numero_char,&type,&repeter);
                      #ifdef AFFICHAGE
                      printf("** D char %d Type %d A repeter %d**\n",numero_char,type,repeter);
                      #endif

                      envoyer_requete(numero_char,type,repeter);
                      Clean_Buf;
                      write_client(clients[i].sock,"OK\n");
                    }
                    else
                    {
                      strncpy(a_comparer, TIR,BUF_SIZE - 1);
                      if (fast_compare(a_comparer,buffer,TAILLE_TIR) == 0)
                      {
                        /* alors recuperer selon codage */
                        int numero_char = 0;
                        sscanf(buffer,"%s %d",truc,&numero_char);
                        envoyer_requete(numero_char,TIRER,0);
                        #ifdef AFFICHAGE
                        printf("TIR\n");
                        #endif
                        Clean_Buf;
                        write_client(clients[i].sock,"OK\n");
                      }
                      else
                      {
                        #ifdef AFFICHAGE
                        printf("******* %s non reconnu *******\n", buffer);
                        #endif
                        Clean_Buf;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  clear_clients();
  end_connection(sock);
}



void clear_clients()
{
  int i = 0;
  for(i = 0; i < actual; i++)
  {
    closesocket(clients[i].sock);
  }
}

void remove_client(int to_remove)
{
  /* we remove the client in the array */
  memmove(clients + to_remove, clients + to_remove + 1,
    (actual - to_remove - 1) * sizeof(Client));
    /* number client - 1 */
    actual--;
  }


  int init_connection(void)
  {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };

    if(sock == INVALID_SOCKET)
    {
      #ifdef AFFICHAGE
      perror("socket()");
      #endif
      exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    int true = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int));
    if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
      #ifdef AFFICHAGE
      perror("bind()");
      #endif
      fermer_fdm();
      exit(errno);
    }

    if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
    {
      #ifdef AFFICHAGE
      perror("listen()");
      #endif
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
      #ifdef AFFICHAGE
      perror("recv()");
      #endif
      /* if recv error we disonnect the client */
      n = 0;
    }
    #ifdef AFFICHAGE
    printf("Reçue ~> %s\n",buffer);
    #endif
    buffer[n] = 0;

    return n;
  }

  void write_client(SOCKET sock, const char *buffer)
  {
    // https://linux.die.net/man/2/send
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
      #ifdef AFFICHAGE
      perror("send()");
      #endif
      exit(errno);
    }
  }

  void my_handler(int s){
    for(int i = 0; i < actual; i++)
    {
      write_client(clients[i].sock,"ARRETE");
    }
    end_connection(GL_SOCK);
    fermer_fdm();
    exit(-1);
  }
  void handler_usr1(int s){
    flag_start = 2;
  }
  void handler_usr2(int s){
    printf("usr2\n");
  }

  int main(int argc, char **argv,char **envp)
  {
    /***********************************/
    /*         CAPTURE DE CTRL C       */
    /***********************************/
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    struct sigaction sigUSR1Handler;

    sigUSR1Handler.sa_handler = handler_usr1;
    sigemptyset(&sigUSR1Handler.sa_mask);
    sigUSR1Handler.sa_flags = 0;


    struct sigaction sigUSR2Handler;

    sigUSR2Handler.sa_handler = handler_usr1;
    sigemptyset(&sigUSR2Handler.sa_mask);
    sigUSR2Handler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    sigaction(SIGUSR1, &sigUSR1Handler, NULL);
    sigaction(SIGUSR2, &sigUSR2Handler, NULL);
    /***********************************/
    /*          Initialisation         */
    /***********************************/
    init_lexico(); // on initialise table hash pour pseudo
    init_equipe();
    init_html();
    flag_lobby = 0;
    flag_start = 0;
    myenvp = envp;

    FILE *fichier;
    char *nom_fichier = "./tmp.txt";

    fichier = fopen(nom_fichier, "w");

    if (fichier == (FILE *)NULL)
    {
      printf("Erreur ouverture fichier\n");
      exit(1);
    }

    // Ecriture du fichier
    fprintf(fichier,"%d ", getpid());
    fclose(fichier);
    // fin


    /***********************************/
    /*         File de message         */
    /***********************************/
    if(creer_fdm() == 0)
    {
      #ifdef AFFICHAGE
      printf("File De Message Créer \n");
      #endif
      ;
    }
    app();
    return EXIT_SUCCESS;
  }
