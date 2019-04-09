CC = gcc
Option = -Wall
All = serveur clients fork_html

all : $(All)

serveur : serveur.c serveur.h analyse_lexicographique.o lobby_afficheur.o fdm.o strcmp_rapide.o equipe.o message.o
	$(CC) $(Option) strcmp_rapide.o analyse_lexicographique.o lobby_afficheur.o fdm.o serveur.c equipe.o message.o -o serveur

clients : client/client.c client/client.h
	$(CC) $(Option) client/client.c -o clients

analyse_lexicographique.o : analyse_lexicographique.c analyse_lexicographique.h
	$(CC) $(Option) -c analyse_lexicographique.c

strcmp_rapide.o : strcmp_rapide.c
	$(CC) $(Option) -c strcmp_rapide.c

equipe.o : equipe.c equipe.h
	$(CC) $(Option) -c equipe.c

message.o : message.c message.h
	$(CC) $(Option) -c message.c

fdm.o : fdm.c fdm.h
	$(CC) $(Option) -c fdm.c

lobby_afficheur.o : lobby_afficheur.c lobby_afficheur.h
	$(CC) $(Option) -c lobby_afficheur.c

fork_html : fork_html.c
	$(CC) $(Option) fork_html.c -o fork_html

clean:
	rm -f $(All)
	rm -f *.o
	rm -f gg
	rm -f test0


test : test.c equipe.o analyse_lexicographique.o message.o
	$(CC) $(Option) equipe.o analyse_lexicographique.o message.o test.c -o gg
