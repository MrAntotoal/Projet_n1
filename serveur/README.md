# Info trame

|Message dans le buffer|	Résultat|	En plus	|En pratique	|Temps|
|:---------------------|:---------|:--------|:------------|:----|
|CREER_EQUIPE	|avec le créateur comme chef d’équipe	|	||	X|
|REJOINDRE_EQUIPE	|rejoint l’équipe |	numéro de l’équipe a rejoindre (char 256)|	Buff + \0 + numéro 	|X|
|QUITTER_EQUIPE	|quitte et si plus de membre supprime	|	||	X|
|MENU_JOUEUR	|envoie le code du menu au joueur|	 (plusieurs menu. )	| si plusieurs Buff + \0 + numéro sinon buff|	X|
|MENU_CHOIX_EQ	|envoie le code du menu choix équipe|	|	|	X|
|START	|envoie ordre début partie	| 	|  | 	X|
| END |	fin de partie	|	|	| 5-15 min|
|DEPLACEMENT	||	direction|	Buff + \0 + (z,s,q,d) |	X|
|TIR	|	|munition spécial|	Buff + \0 + (0-9)|	X
|MORT	||||			X|
|TUER||		numéro char ?|Buff + \0 + (0-256)|	X|
|TIMEOUT	||	|Buff |2 s|
|PSEUDO_POK |(le programme client recoit server disconnected mais doit relancer init_connection) le serveur déconnecte le client, le client doit donc se reconnecter avant de retenter| pseudo déjà utilisé ||X|
|DISABLE_BUTT | désactive les boutons | ||X|
|MODE_JEUX|+1 pour décision mode | numéro |Buff +/0 + (0-256)|X|
| INVITER_AMI| |pseudo de l'ami | Buff + /0 + pseudo + /0 | X|
| NEW_BUTT| change les boutons du joueur | code des boutons g, h, d, U| Buff + /0 + code bouton x4 | 1 minute ou toucher |

TO DO :
  faire les déplacements en premier (sémaphore entre programme traitement et jeux)

Table de hash pour les pseudos ?
