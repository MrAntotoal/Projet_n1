# Info trame

|Message dans le buffer|	Résultat|	En plus	|En pratique	|Temps|
|:---------------------|:---------|:--------|:------------|:----|
|CREER_EQUIPE	|avec le créateur comme chef d’équipe	|	||	equipe|
|REJOINDRE_EQUIPE	|rejoint l’équipe |	numéro de l’équipe a rejoindre (char 256)|	Buff + \0 + numéro 	|equipe|
|QUICK_EQUIPE|vire le gars de l'équipe||Buff + /0 + pseudo + /0|equipe|
|QUITTER_EQUIPE	|quitte et si plus de membre supprime	|	||equipe|
|MENU_JOUEUR	|envoie le code du menu au joueur|	 (plusieurs menu. )	| si plusieurs Buff + \0 + numéro sinon buff|	Après connexion + pseudo ok |
|MENU_CHOIX_EQ	|envoie le code du menu choix équipe|	|	|	Choix équipe|
|START	|envoie ordre début partie	| 	|  | 	X|
| END |	fin de partie	|	|	| 5-15 min|
|DEPLACEMENT	||	type = T tourelle B bouclier C char|	Buff + \0 + type + (z,s,q,d) |	Durant partie|
|TIR	|	|munition spécial|	Buff + \0 + (0-9)|	X|
|RECHARGEMENT| | ||Durant partie|
|TIMEOUT	||	|Buff |2 s|
|PSEUDO_POK |(le programme client recoit server disconnected mais doit relancer init_connection) le serveur déconnecte le client, le client doit donc se reconnecter avant de retenter| pseudo déjà utilisé ||Connection|
|DISABLE_BUTT | désactive les boutons | ||Durant partie|
|MODE_JEUX|+1 pour décision mode | numéro |Buff +/0 + (0-256)|Décision mode de jeux|
| INVITER_AMI| |pseudo de l'ami | Buff + /0 + pseudo + /0 | Création équipe|
| NEW_BUTT| change les boutons du joueur | code des boutons g, h, d, U| Buff + /0 + code bouton x4 | 1 minute ou toucher |
|NUM_CHAR|Le client enregistre le numéro du char|numéro du char (0-256)|Buff + \0 + numéro|Début partie|
# Communication avec file de message
|Message | En pratique |
|:-------|:------------|
|DEPLACEMENT | D T/B/C z/q/s/d|
