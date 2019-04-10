package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;


public class lobbyChef extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.lobby_chef);

        Button M1 = findViewById(R.id.exclure1);
        Button M2 = findViewById(R.id.exclure2);
        Button Q = findViewById(R.id.quitter);

        class Commencer implements Runnable{
            String rep;
            @Override
            public void run() {
                try{
                    Log.d("affichage", "debut");
                    InputStream in = Joueur.getSocket().getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                    rep = reader.readLine();
                    Log.d("affichage", rep);
                    while (!( rep.equals("START") || Joueur.getReponse().equals("START")) ){
                        Log.d("affichage", "J'ai reçu "+rep);
                        rep = reader.readLine();
                    }
                    Log.d("affichage", "je suis out du while");
                    startActivity(new Intent(lobbyChef.this, Manette.class));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        Commencer commencer = new Commencer();
        Thread t = new Thread(commencer);
        t.start();

        M1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("EXCLURE 1");
                EnvoieMessage message = new EnvoieMessage();
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        M2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("EXCLURE 2");
                EnvoieMessage message = new EnvoieMessage();
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Q.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("QUITTER");
                EnvoieMessage message = new EnvoieMessage();
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Intent i = new Intent(lobbyChef.this, Formation.class);
                startActivity(i);
            }
        });
    }
    protected void onDestroy() {
        super.onDestroy();
        try {
            Joueur.fermerSocket();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
