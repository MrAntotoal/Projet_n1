package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

import java.io.IOException;

import static com.premier.battlecoor.R.*;

public class Formation extends Activity {
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(layout.formation);

        Button M = (Button) findViewById(id.monter);
        Button R = (Button) findViewById(id.rejoindre);
        final EditText Num = (EditText) findViewById(id.numchar);

        //Recuperation des donnees Joeur de l'activité précédente
        Intent i = getIntent();


        M.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("CREER_EQUIPE");
                EnvoieMessage N = new EnvoieMessage();
                Thread t = new Thread(N);
                t.start();

                //TODO CHANGEMENT DACTIVITE
            }
        });

        R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Recupérer le num du char
                String num_char =  Num.getText().toString();
                Joueur.setMessage("REJOINDRE_EQUIPE "+num_char);
                EnvoieMessage N = new EnvoieMessage();
                Thread t = new Thread(N);
                t.start();

                //TODO CHANGEMENT DACTIVITE
            }
        });

    }

}

