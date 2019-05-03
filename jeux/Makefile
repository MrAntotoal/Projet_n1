cc=gcc
option=-Wall
o_sdl=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf
o_opengl=-lGL -lGLU

run: run.c mode_de_jeux.o bonus.o reap.o obus.o texture.o affichage.o char.o sauvegarde.o map.o traitement_fm.o collisions.o file_msg.o liste.o point_vecteur.o allocation_memoire.o polygones.o
	$(cc) $(option) run.c mode_de_jeux.o bonus.o reap.o obus.o texture.o affichage.o char.o sauvegarde.o map.o traitement_fm.o collisions.o file_msg.o liste.o point_vecteur.o allocation_memoire.o polygones.o -o run -lm $(o_sdl) $(o_opengl)

mode_de_jeux.o: mode_de_jeux.c mode_de_jeux.h
	$(cc) $(option) mode_de_jeux.c -c

bonus.o: bonus.c bonus.h
	$(cc) $(option) bonus.c -c

reap.o: reap.c reap.h
	$(cc) $(option) reap.c -c

affichage.o:affichage.c affichage.h
	$(cc) $(option) affichage.c -c

obus.o:obus.c obus.h
	$(cc) $(option) obus.c -c

char.o: char.c char.h
	$(cc) $(option) char.c -c

sauvegarde.o: sauvegarde.h sauvegarde.c
	$(cc) $(option) sauvegarde.c -c

map.o: map.c map.h
	$(cc) $(option) map.c -c

traitement_fm.o:traitement_fm.c traitement_fm.h
	$(cc) $(option) traitement_fm.c -c

collisions.o: collisions.c collisions.h
	$(cc) $(option) collisions.c -c

texture.o: texture.c texture.h
	$(cc) $(option) texture.c -c

polygones.o: polygones.c polygones.h
	$(cc) $(option) polygones.c -c

point_vecteur.o: point_vecteur.c point_vecteur.h
	$(cc) $(option) point_vecteur.c -c

allocation_memoire.o: allocation_memoire.c allocation_memoire.h
	$(cc) $(option) allocation_memoire.c -c

file_msg.o: file_msg.c file_msg.h
	$(cc) $(option) file_msg.c -c

liste.o: liste.c liste.h
	$(cc) $(option) liste.c -c


test_fm: test_fm.c type_fm.h
	$(cc) $(option) test_fm.c type_fm.h -o test_fm


test_reception : test_reception.c type_fm.h
	$(cc) $(option) test_reception.c type_fm.h -o test_reception

test_texture: test_texture.c texture.o allocation_memoire.o
	$(cc) $(option) test_texture.c texture.o allocation_memoire.o -o test_texture -lm $(o_sdl) $(o_opengl)


test_sdl_opengl:test_sdl_opengl.c
	$(cc) $(option) test_sdl_opengl.c -o test_sdl_opengl $(o_sdl) $(o_opengl)

test_char: test_char.c char.o collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o
	$(cc) $(option) test_char.c char.o collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o -o test_char -lm

test_collisions: test_collisions.c collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o

	$(cc) $(option) test_collisions.c collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o -o test_collisions -lm

test_fuite_mem  :liste.o point_vecteur.o allocation_memoire.o polygones.o test_fuite_mem.c
	$(cc) $(option) liste.o point_vecteur.o allocation_memoire.o polygones.o test_fuite_mem.c -o test_fuite_mem -lm

test_polygone: test_polygone.c liste.o point_vecteur.o allocation_memoire.o polygones.o
	$(cc) $(option) test_polygone.c liste.o point_vecteur.o allocation_memoire.o polygones.o -o test_polygone -lm

test_liste : test/test_liste.c liste.o point_vecteur.o allocation_memoire.o
	$(cc) $(option) test/test_liste.c liste.o point_vecteur.o allocation_memoire.o -o test_liste -lm

test_point_vecteur : test_points_vecteur.c point_vecteur.o
	$(cc) $(option) test_points_vecteur.c point_vecteur.o -o test_point_vecteur -lm


clean:
	rm *.o
