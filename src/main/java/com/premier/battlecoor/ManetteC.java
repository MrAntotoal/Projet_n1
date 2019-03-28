package com.premier.battlecoor;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.widget.Button;

//37854003
public class ManetteC extends Activity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.manette_conducteur);
        Button G = findViewById(R.id.buttonG);
        Button D = findViewById(R.id.buttonD);
        Button H = findViewById(R.id.buttonH);
        Button B = findViewById(R.id.buttonB);

        G.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN: //
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" 4 1"); //TODO recupérer le numéro du char
                        EnvoieMessage G = new EnvoieMessage();
                        Thread tg = new Thread(G);
                        tg.start();
                        try {
                            tg.join();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -4 0"); //TODO recupérer le numéro du char
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


        D.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN: //
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" 3 1"); //TODO recupérer le numéro du char
                        EnvoieMessage G = new EnvoieMessage();
                        Thread tg = new Thread(G);
                        tg.start();
                        try {
                            tg.join();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -3 0"); //TODO recupérer le numéro du char
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

        H.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN: //
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" 1 1"); //TODO recupérer le numéro du char
                        EnvoieMessage G = new EnvoieMessage();
                        Thread tg = new Thread(G);
                        tg.start();
                        try {
                            tg.join();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -1 0"); //TODO recupérer le numéro du char
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

        B.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN: //
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" 2 1"); //TODO recupérer le numéro du char
                        EnvoieMessage G = new EnvoieMessage();
                        Thread tg = new Thread(G);
                        tg.start();
                        try {
                            tg.join();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        Joueur.setMessage("DEPLACEMENT "+Joueur.getNumChar()+" -2 0"); //TODO recupérer le numéro du char
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
