CC = gcc
Option = -Wall


all : serveur clients traitement_client

serveur : serveur.c serveur.h analyse_lexicographique.o strcmp_rapide.o equipe.o message.o
	$(CC) $(Option) strcmp_rapide.o analyse_lexicographique.o serveur.c equipe.o message.o -o serveur

clients : client/client.c client/client.h
	$(CC) $(Option) client/client.c -o clients

traitement_client : traitement_client.c strcmp_rapide.o
	$(CC) $(Option) strcmp_rapide.o traitement_client.c -o traitement_client

analyse_lexicographique.o : analyse_lexicographique.c analyse_lexicographique.h
	$(CC) $(Option) -c analyse_lexicographique.c

strcmp_rapide.o : strcmp_rapide.c
	$(CC) $(Option) -c strcmp_rapide.c

equipe.o : equipe.c equipe.h
	$(CC) $(Option) -c equipe.c

message.o : message.c message.h
	$(CC) $(Option) -c message.c
	
clean:
	rm -f clients
	rm -f serveur
	rm -f *.o


test : test.c test0.c
	$(CC) $(Option) test.c -o test
	$(CC) $(Option) test0.c -o test0
