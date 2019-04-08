#!/usr/bin/env bash

if(($#==1))
then
    ./run $1
    nom=$(echo "$1" | cut -f1 -d '.')
    mkdir $nom
    mv map.map $nom/$nom.map
    mv $1 $nom/
    echo "bien passer"
else
    echo "editeur <fichier image> -> sortie fichier avec l'image et la map"
fi;
