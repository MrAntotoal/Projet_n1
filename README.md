# Projet_n+1
Projet Tuteuré L3 Info

### lib a install :
``` sudo apt-get install libsdl1.2-dev```

``` sudo apt-get install freeglut3-dev```

``` sudo apt-get install libsdl-image1.2-dev```

``` sudo apt-get install libsdl-ttf2.0-dev```

# doc pour communication avec la file de message + lancement jeux a la fin 

rapelle des struct :

* requete pour parler au jeux 
```c
typedef struct{
  long mtype;
  char numero_char;
  char type_action;
  char a_repeter;
}requete_t;
```

* reponse du jeux au serveur
```c
typedef struct{
  long mtype;
  char numero_char;
  char type;
}reponse_t;
```

(ne pas oublier comme je l'ai fait ) long mtype pour le numero de celui a qui on envoie

## info valeurs requete_t
* numero char -> ba le num du char (debut a 1)
* type_action a_repeter

|type_action|      action      |a_repeter|
|:---------:|:----------------:|:-------:|
|1          |avance            |1        |
|2          |recule            |1        |
|3          |droite            |1        |
|4          |gauche            |1        |
|5          |droite_tourelle   |1        |
|6          |gauche_tourelle   |1        |
|7          |droite_shield     |1        |
|8          |gauche_shield     |1        |
|10         |tire              |0        |
|11         |activer bouclier  |0        |
|12         |stop bouclier     |0        |
|20         |special conducteur|0        |
|21         |special tireur    |0        |
|22         |special bouclier  |0        |
pour le reste on verra plus tard

* a_reperter -> on repete cette action jusqu'au signe d'interuption

* signe d'interuption
-le numero -> stop a_repeter
exemple -1 = stop avance

## info pour reponse_t


|numero_char|type|         info        |
|:---------:|:--:|:-------------------:|
|char n     |100 |        toucher      |
|char n     |-100|         mort        |
|char n     |30  |special conducteur ok|
|char n     |31  |special tireur ok    |
|char n     |32  |special bouclier ok  |
|-1         |0   |fin de partie        |

## lancement du jeux

```
./run <mode de jeux> <nbr de chars> <equipe char 0> ... <nom dossier map> <extention image fond>
```

### exemple

```
./run 0 4 1 2 3 4 test png
```
pour l'instant il faut ``` test png ```

### petit tableau

les modes de jeux c'est avec des tickets et un timeout 

|num mode de jeux|   mode  |
|:--------------:|:-------:|
|0               |ffa 1 vie|
|1               |   ffa   |
|2               |   tdm   |


