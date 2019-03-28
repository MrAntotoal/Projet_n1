package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;

public class lobbyChef extends Activity {

    //TODO le timer
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.lobby_chef);

        Button M1 = findViewById(R.id.exclure1);
        Button M2 = findViewById(R.id.exclure2);
        Button Q = findViewById(R.id.quitter);


        M1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("EXCLURE_1");
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
                Joueur.setMessage("EXCLURE_2");
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
}
