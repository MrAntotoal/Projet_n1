package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Parcelable;
import android.support.annotation.Nullable;
import android.support.annotation.RequiresApi;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

import java.io.IOException;
import java.net.Socket;

public class Pseudo extends Activity {

    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.pseudo);


        Button Go = findViewById(R.id.button);
        final EditText nickname = findViewById(R.id.editText);


        Go.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                CreationJoueur P = new CreationJoueur();
                Thread lp = new Thread(P);
                lp.start();
                try {
                    lp.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                Joueur.setMessage(nickname.getText().toString());
                EnvoieMessage message = new EnvoieMessage();
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                switch(Joueur.getReponse()){
                    case "MENU_JOUEUR":
                        Intent i;
                        i = new Intent(Pseudo.this, Formation.class);
                        startActivity(i);
                        finish();
                        break;
                    case "PSEUDO_POK":
                        nickname.setText("");
                        nickname.setHintTextColor(getResources().getColor(R.color.rouge));
                        nickname.setHint("Pseudo déjà existant");
                        break;
                }
            }
        });
    }
}
