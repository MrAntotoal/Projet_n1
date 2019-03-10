cc=gcc
option=-Wall
option_gl=""

run: run.c traitement_fm.o collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o
	$(cc) $(option) run.c traitement_fm.o collisions.o liste.o point_vecteur.o allocation_memoire.o polygones.o -o run -lm

traitement_fm.o:traitement_fm.c traitement_fm.h
	$(cc) $(option) traitement_fm.c -c

collisions.o: collisions.c collisions.h
	$(cc) $(option) collisions.c -c

polygones.o: polygones.c polygones.h
	$(cc) $(option) polygones.c -c

point_vecteur.o: point_vecteur.c point_vecteur.h
	$(cc) $(option) point_vecteur.c -c

allocation_memoire.o: allocation_memoire.c allocation_memoire.h
	$(cc) $(option) allocation_memoire.c -c

liste.o: liste.c liste.h
	$(cc) $(option) liste.c -c


test_fm: test_fm.c type_fm.h
	$(cc) $(option) test_fm.c type_fm.h -o test_fm

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
