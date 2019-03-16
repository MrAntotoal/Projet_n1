package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

import java.io.IOException;
import java.net.Socket;

public class Pseudo extends Activity {
    final int PORT = 1977;
    final String ip = "192.168.1.28";
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.pseudo);


        Button Go = (Button) findViewById(R.id.button);
        final EditText nickname = (EditText) findViewById(R.id.editText);


        Log.d("affichage", "AVANT CREATION JOUEUR");
        try {
            CreationJoueur P = new CreationJoueur();//TODO je dois le mettre dans un thread pour fonctionnement
            Thread lp = new Thread(P);
            lp.start();
            lp.join();
            final Joueur J = P.J;
            Log.d("affichage", "APRES CREATION JOUEUR");
        Go.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //String mes = nickname.getText().toString();
                J.setMessage(nickname.getText().toString());
                EnvoieMessage message=null;
                message = new EnvoieMessage();
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                switch(J.getReponse()){
                    case "MENU_JOUEUR":
                        Intent i;
                        i = new Intent(Pseudo.this, Formation.class);
                        //i.putExtra("data", J);
                        startActivity(i);
                        break;
                    case "PSEUDO_POK":
                        nickname.setHint("Pseudo déjà existant");
                        break;
                }
            }
        });
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


}
