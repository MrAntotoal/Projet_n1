# Info trame

|Message dans le buffer|	Résultat|	En plus	|En pratique	|Temps|Expéditaire|
|:---------------------|:---------|:--------|:------------|:----|:----------|
|CREER_EQUIPE	|avec le créateur comme chef d’équipe	|	||	equipe|Client|
|REJOINDRE_EQUIPE	|rejoint l’équipe ?|	numéro de l’équipe a rejoindre|	Buff + ' ' + numéro 	|equipe|client|
|ROLE|donne le role (conducteur,tireur,protecteur,...)|0 conducteur, 1 tireur,2 protecteur|Buff + ' ' + int|equipe|serveur|
|QUICK_EQUIPE|vire le gars de l'équipe||Buff + ' ' + pseudo + ' '|equipe|client|
|QUITTER_EQUIPE	|quitte et si plus de membre supprime	|	||equipe|client|
|MENU_JOUEUR	|envoie le code du menu au joueur|	 (plusieurs menu. )	| si plusieurs Buff + ' ' + numéro sinon buff|	Après connexion + pseudo ok |serveur|
|START	|envoie ordre début partie	| 	|  | 	X|serveur|
| END |	fin de partie	|	|	| 5-15 min|serveur|
|DEPLACEMENT	||	annuler déplacement : Buff + ' ' + numero_char + ' ' + -(1,2,3,4) + ' ' + '0'|	Buff + ' ' + numero_char + ' ' + (1,2,3,4,...) + ' ' + (0,1)(appuie / relache) |	Durant partie|client|
|TIR	|	|munition spécial|	Buff + ' ' + numero_char + (0-9)|	X|Client|
|RECHARGEMENT| | |	Buff + ' ' + numero_char |Durant partie|client|
|TIMEOUT	||	|Buff |2 s|
|PSEUDO_POK |(le programme client recoit server disconnected mais doit relancer init_connection) le serveur déconnecte le client, le client doit donc se reconnecter avant de retenter| pseudo déjà utilisé ||Connection|serveur|
|DISABLE_BUTT | désactive les boutons | ||Durant partie|serveur|
|MODE_JEUX|+1 pour décision mode | numéro |Buff +' ' + (0-256)|Décision mode de jeux|client|
|NEW_BUTT| change les boutons du joueur | code des boutons Tireur : F,TG,TD,TS Protecteur :P,PG,PD,PS Conducteur : AR,CG,CD,CS| Buff + ' ' + code bouton x4 | 1 minute ou toucher |serveur|
|NUM_CHAR|Le client enregistre le numéro du char|numéro du char (0-256)|Buff + ' ' + numéro|Début partie|serveur|


## info valeurs requete_t
* numero char -> ba le num du char (debut a 1)
* type_action a_repeter

|type_action|action|a_repeter|
|:---------:|:----:|:-------:|
|1          |avance|1        |
|2          |recule|1        |
|3          |droite|1        |
|4          |gauche|1        |
|5          |droite_tourelle | 1|
|6          |gauche_tourelle | 1|
|7 	|droite_shield 	|1
|8 	|gauche_shield 	|1
|10 	      |tire            | 0|
|100|changement boutton | 0|
