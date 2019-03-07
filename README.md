# Projet_n+1
Projet Tuteuré L3 Info

#doc pour communication avec la file de message

rapelle des struct :

* requete pour parler au jeux 
```c
typedef struct{
  signed char numero_char;
  signed char type_action;
  signed char a_repeter;
}requete_t;
```

* reponse du jeux au serveur
```c
typedef struct{
  signed char numero_char;
  signed char type;
}reponse_t;
```

## info valeurs requete_t
* numero char -> ba le num du char (debut a 1)
* type_action a_repeter

|type_action|action|a_repeter|
|:---------:|:----:|:-------:|
|1          |avance|1        |
|2          |recule|1        |
|3          |droite|1        |
|4          |gauche|1        |

pour le reste on verra plus tard

* a_reperter -> on repete cette action jusqu'au signe d'interuption

* signe d'interuption
-le numero -> stop a_repeter
exemple -1 = stop avance
