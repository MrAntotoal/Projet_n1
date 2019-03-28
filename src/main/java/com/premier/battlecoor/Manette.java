package com.premier.battlecoor;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.Window;
import android.widget.Button;

public class Manette extends Activity {
    /*
    Dans cette classe, tous les boutons seront définis
    Lorsque cette classe sera opérationelle
     */


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.manette);

        //Declaration des boutons
        //Conducteur
        Button ConducteurGauche = findViewById(R.id.CG);
        Button ConducteurDroite = findViewById(R.id.CD);
        Button Haut = findViewById(R.id.Haut);
        Button Bas  = findViewById(R.id.Bas);

        //Tireur
        Button TireurGauche = findViewById(R.id.TG);
        Button TireurDroite = findViewById(R.id.TD);
        Button Feu = findViewById(R.id.FEU);

        //PROTECTEUR
        Button ProtecteurGauche = findViewById(R.id.PG);
        Button ProtecteurDroite = findViewById(R.id.PD);
        Button Protection = findViewById(R.id.PROTECTION);


        //ACTION A REALISER

    }
}
