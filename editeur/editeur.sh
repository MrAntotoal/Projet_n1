#!/usr/bin/env bash

if(($#==3))
then
    ./run $1 $2 $3
    nom=$(echo "$1" | cut -f1 -d '.')
    mkdir $nom
    mv map.map $nom/$nom.map
    mv $1 $nom/
    echo "bien passer"
else
    echo "editeur <fichier image> <resolution x> <resolution y> -> sortie fichier avec l'image et la map"
fi;
