package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import static com.premier.battlecoor.R.id;
import static com.premier.battlecoor.R.layout;

public class Formation extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(layout.formation);

        Button M = findViewById(id.monter);
        Button R = findViewById(id.rejoindre);
        final EditText Num = findViewById(id.numchar);

        M.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("CREER_EQUIPE");
                Thread t = new Thread(new EnvoieMessage());
                try {
                    t.start();
                    t.join();
                    Joueur.setNumChar(Joueur.getReponse());
                    Joueur.setMessage("ROLE");
                    Log.d("affichage", "demande de role");
                    Thread u = new Thread(new EnvoieMessage());
                    u.start();
                    u.join();
                    Log.d("affichage", "role--> "+Joueur.getReponse());
                    Joueur.setRole(Joueur.getReponse());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                //Changement d'activité
                startActivity(new Intent(Formation.this, lobbyChef.class));

            }
        });

        R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Recupérer le num du char
                String num_char =  Num.getText().toString();
                Joueur.setNumChar(num_char);
                Joueur.setMessage("REJOINDRE_EQUIPE "+num_char); //le joueur souhaite rejoindre le char numéro num_char
                EnvoieMessage N = new EnvoieMessage();
                Thread t = new Thread(N);
                //en réponse le joueur dispose de son rôle
                try {
                    t.start();
                    t.join();
                    //TODO si il est impossible de rejoindre l'equipe
                    Joueur.setMessage("ROLE");
                    //Demande du role au serveur
                    Thread u = new Thread(new EnvoieMessage());
                    u.start();
                    u.join();
                    Joueur.setRole(Joueur.getReponse());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                //Changement d'activité
                startActivity(new Intent(Formation.this, lobbySoldat.class));
            }
        });
    }
}

