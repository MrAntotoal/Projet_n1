cc=gcc
option=-Wall
o_sdl=`sdl-config --cflags --libs` -lSDL_image
o_opengl=-lGL -lGLU



run: run.c affichage.o sauvegarde.o map.o collisions.o texture.o polygones.o point_vecteur.o allocation_memoire.o liste.o
	$(cc) $(option) run.c affichage.o sauvegarde.o  map.o collisions.o texture.o polygones.o point_vecteur.o allocation_memoire.o liste.o -o run -lm $(o_sdl) $(o_opengl)
affichage.o:affichage.c affichage.h
	$(cc) $(option) affichage.c -c

sauvegarde.o: sauvegarde.h sauvegarde.c
	$(cc) $(option) sauvegarde.c -c

map.o: map.c map.h
	$(cc) $(option) map.c -c

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

liste.o: liste.c liste.h
	$(cc) $(option) liste.c -c

clean:
	rm *.o
	rm run
