CC = gcc
Option = -Wall


all : serveur clients

serveur : serveur.c serveur.h
	$(CC) $(Option) serveur.c -o serveur

clients : client/client.c client/client.h
	$(CC) $(Option) client/client.c -o clients

clean:
	rm -f clients
	rm -f serveur
