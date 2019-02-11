#info trame
|Message dans le buffer	|Résultat	|en plus	|En pratique	|Temps|
|CREER_EQUIPE	|avec le créateur comme chef d’équipe	| |		X|
|REJOINDRE_EQUIPE	|rejoint l’équipe |	numéro de l’équipe a rejoindre (char 256)|	Buff + \0 + numéro |	X|
|QUITTER_EQUIPE	|quitte et si plus de membre supprime	|||		X|

|MENU_JOUEUR|	envoie le code du menu au joueur|	** plusieurs menu ?	**| si +ieurs Buff + \0 + numéro sinon buff	|X|
|MENU_CHOIX_EQ|	envoie le code du menu choix équipe	|||		X|

|START|	envoie ordre début partie|||			X|
|END	|fin de partie	|	||	5-15 min|

|DEPLACEMENT	|	direction	||Buff + \0 + (z,s,q,d) |	X|
|TIR	|	munition spécial||	Buff + \0 + (0-9)	|X|
|MORT	|||			X|
|TUER	|	|numéro char ?	|Buff + \0 + (0-256)|	X|

|POSITION	|	(dans la matrice ?)	||Buff + \0 + (0-256) + (0-256) 	
			ou si pas assez (0-512) ou (0-1024)	|1 s|
