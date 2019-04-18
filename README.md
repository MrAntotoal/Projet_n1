# Projet_n+1
Projet Tuteuré L3 Info

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

|type_action|     action     |a_repeter|
|:---------:|:--------------:|:-------:|
|1          |avance          |1        |
|2          |recule          |1        |
|3          |droite          |1        |
|4          |gauche          |1        |
|5          |droite_tourelle |1        |
|6          |gauche_tourelle |1        |
|7          |droite_shield   |1        |
|8          |gauche_shield   |1        |
|10         |tire            |0        |
pour le reste on verra plus tard

* a_reperter -> on repete cette action jusqu'au signe d'interuption

* signe d'interuption
-le numero -> stop a_repeter
exemple -1 = stop avance

## info pour reponse_t


|type| info  |
|:--:|:-----:|
|100 |toucher|
|-100|mort   |


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

|num mode de jeux| mode|
|:--------------:|:---:|
|0               | ffa |



