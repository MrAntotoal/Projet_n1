package com.premier.battlecoor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.ImageButton;

public class Acceuil extends Activity {
    private static final String TAG = "Acceuil";
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.acceuil);
        Log.d("affichage", "DANS ACCEUIL");
        Log.d(TAG, "onCreate: started.");
        ImageButton imageButton =  (ImageButton) findViewById(R.id.imageButton);
        int imageRessource = getResources().getIdentifier("@drawable/images", null, this.getPackageName() );
        imageButton.setImageResource(imageRessource);

        imageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i;
                i = new Intent(Acceuil.this, Pseudo.class);
                startActivity(i);
            }
        });
    }
}
