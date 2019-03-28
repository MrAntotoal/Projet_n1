package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

import static com.premier.battlecoor.R.id;
import static com.premier.battlecoor.R.layout;

public class Formation extends Activity {
    //TODO faire le timer qui s'affiche
    //TODO dans les classes lobby lorsque timer terminé lancer les manettes

    // TODO Pas dans la bonne classe: A deplacer dans lobby
    private void chargerManette(String role){
        Intent manette_conducteur=null;
        switch(role){
            case "Tireur":
                manette_conducteur = new Intent(Formation.this, ManetteT.class);
                break;
            case "Conducteur":
                manette_conducteur = new Intent(Formation.this, ManetteC.class);
                break;
            case "Protecteur":
                manette_conducteur = new Intent(Formation.this, ManetteP.class);
                break;
        }
        startActivity(manette_conducteur);
    }


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
                EnvoieMessage N = new EnvoieMessage();
                Thread t = new Thread(N);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Joueur.setNumChar(Joueur.getReponse());
                chargerManette("Conducteur"); //TODO A deplacer chargerManette(Joueur.getReponse());
                //TODO CHANGEMENT DACTIVITE
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
                t.start();                                      //en réponse le joueur dispose de son rôle
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                // chargerManette(Joueur.getReponse());//TODO A deplacer
                chargerManette("Tireur");
            }
        });

    }

}

