package com.premier.battlecoor;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.widget.Button;

public class ManetteT extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.manette_tireur);

        Button Gauche = findViewById(R.id.gaucheT);
        Button Droite = findViewById(R.id.droiteT);
        //TODO Button Special = findViewById(R.id.SpecialF);
        Button Tirer = findViewById(R.id.tirer);

        Tirer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("TIR "+Joueur.getNumChar()+" 0");
                EnvoieMessage tir = new EnvoieMessage();
                Thread t =new Thread(tir);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Gauche.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        if(!Joueur.GT) {
                            Joueur.GT = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 6 1");
                            EnvoieMessage G = new EnvoieMessage();
                            Thread tg = new Thread(G);
                            tg.start();
                            try {
                                tg.join();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                        return true;
                        case MotionEvent.ACTION_UP:
                            Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -6 0");
                            EnvoieMessage SG = new EnvoieMessage();
                            Thread tsg = new Thread(SG);
                            tsg.start();
                            try {
                                tsg.join();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            return true;
                }
                return false;
            }
        });

        Droite.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        if(!Joueur.DT) {
                            Joueur.DT = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 5 1"); //TODO recupérer le numéro du char
                            EnvoieMessage G = new EnvoieMessage();
                            Thread tg = new Thread(G);
                            tg.start();
                            try {
                                tg.join();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            return true;
                        }
                    case MotionEvent.ACTION_UP:
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -5 0"); //TODO recupérer le numéro du char
                        EnvoieMessage SG = new EnvoieMessage();
                        Thread tsg = new Thread(SG);
                        tsg.start();
                        try {
                            tsg.join();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        return true;
                }
                return false;
            }
        });
    }
}
