package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class lobbySoldat extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.lobby_soldat);

        Button Q = findViewById(R.id.quitter);

        //si le jouer se fait virer par le chef
        class Quitter implements Runnable{
            String rep;
            @Override
            public void run() {
                try{
                    InputStream in = Joueur.getSocket().getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                    rep = reader.readLine();
                    while(!Joueur.getReponse().equals("OUT") || !rep.equals("OUT") ){
                        rep = reader.readLine();
                    }
                    Intent i = new Intent(lobbySoldat.this, Formation.class);
                    startActivity(i);

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        Quitter out  = new Quitter();
        Thread q= new Thread(out);
        q.start();

        class Commencer implements Runnable{
            String rep;
            @Override
            public void run() {
                try{
                    InputStream in = Joueur.getSocket().getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                    rep = reader.readLine();
                    while(!(Joueur.getReponse().equals("START") || rep.equals("START") )){
                        rep = reader.readLine();
                    }
                    startActivity(new Intent(lobbySoldat.this, Manette.class));

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        Commencer commencer = new Commencer();
        Thread t = new Thread(commencer);
        t.start();

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
                startActivity(new Intent(lobbySoldat.this, Formation.class));
            }
        });

    }

}
