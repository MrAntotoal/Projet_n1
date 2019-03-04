CC = gcc
Option = -Wall


all : serveur clients

serveur : serveur.c serveur.h analyse_lexicographique.o
	$(CC) $(Option) analyse_lexicographique.o serveur.c -o serveur

clients : client/client.c client/client.h
	$(CC) $(Option) client/client.c -o clients

analyse_lexicographique.o : analyse_lexicographique.c analyse_lexicographique.h
	$(CC) $(Option) -c analyse_lexicographique.c

clean:
	rm -f clients
	rm -f serveur
	rm -f *.o
