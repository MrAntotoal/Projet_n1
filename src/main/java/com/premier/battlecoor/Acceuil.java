package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.ImageButton;

public class Acceuil extends Activity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.acceuil);

        ImageButton imageButton = findViewById(R.id.imageButton);
        int imageRessource = getResources().getIdentifier("@drawable/images", null, this.getPackageName() );
        imageButton.setImageResource(imageRessource);

        final EditText addr = findViewById(R.id.ipaddr);


        imageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(addr.getText().toString().length() > 6) {
                    Joueur.setIp(addr.getText().toString());
                }
                Intent i;
                i = new Intent(Acceuil.this, Pseudo.class);
                startActivity(i);
            }
        });
    }
}
