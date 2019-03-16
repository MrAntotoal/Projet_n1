package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

public class Pseudo extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.pseudo);
        Button Go = (Button) findViewById(R.id.button);
        final EditText nickname = (EditText) findViewById(R.id.editText);
        Go.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String mes = nickname.getText().toString();
                EnvoieMessage message = new EnvoieMessage(mes);
                Thread t = new Thread(message);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                switch(message.getReponse()){
                    case "MENU_JOUEUR":
                        Intent i;
                        i = new Intent(Pseudo.this, Formation.class);
                        startActivity(i);
                        break;
                    case "PSEUDO_POK":
                        nickname.setHint("Pseudo déjà existant");
                        break;
                }
            }
        });
    }


}
