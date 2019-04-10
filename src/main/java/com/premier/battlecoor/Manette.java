package com.premier.battlecoor;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class Manette extends Activity {
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
        Button Bas = findViewById(R.id.Bas);


        //Tireur
        Button TireurGauche = findViewById(R.id.TG);
        Button TireurDroite = findViewById(R.id.TD);
        Button Feu = findViewById(R.id.FEU);


        //TODO PROTECTEUR
        Button ProtecteurGauche = findViewById(R.id.PG);
        Button ProtecteurDroite = findViewById(R.id.PD);
        Button Protection = findViewById(R.id.PROTECTION);

        class Attente implements Runnable{
            String rep;
            @Override
            public void run() {
                try {
                    InputStream in  = Joueur.getSocket().getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                    rep = reader.readLine();
                    while ((!rep.equals("NEW_BUTT")) || (Joueur.changerButtons == false)){
                        rep = reader.readLine();
                    }
                    Joueur.changerButtons = false;
                    //TODO changement des boutons
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        switch (Joueur.getRole()) {
            case "Conducteur":
                ConducteurGauche.setVisibility(View.VISIBLE);
                ConducteurDroite.setVisibility(View.VISIBLE);
                Haut.setVisibility(View.VISIBLE);
                Bas.setVisibility(View.VISIBLE);
                break;
            case "Tireur":
                TireurGauche.setVisibility(View.VISIBLE);
                TireurDroite.setVisibility(View.VISIBLE);
                Feu.setVisibility(View.VISIBLE);
                break;
            case "Protecteur":
                ProtecteurGauche.setVisibility(View.VISIBLE);
                ProtecteurDroite.setVisibility(View.VISIBLE);
                Protection.setVisibility(View.VISIBLE);
                break;
        }

        //ACTION A REALISER
        ConducteurGauche.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.GC) {
                            Joueur.GC = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 4 1");
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
                        Joueur.GC = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -4 0"); //TODO recupérer le numéro du char
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

        ConducteurDroite.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.DC) {
                            Joueur.DC = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 3 1");
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
                        Joueur.DC = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -3 0"); //TODO recupérer le numéro du char
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

        Haut.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.HC) {
                            Joueur.HC = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 1 1"); //TODO recupérer le numéro du char
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
                        Joueur.HC = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -1 0"); //TODO recupérer le numéro du char
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

        Bas.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.BC) {
                            Joueur.BC = true;
                            Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " 2 1");
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
                        Joueur.BC = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -2 0");
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

        TireurGauche.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.GT) {
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
                        Joueur.GT = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -6 0");
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

        TireurDroite.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (!Joueur.DT) {
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
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        Joueur.DT = false;
                        Joueur.setMessage("DEPLACEMENT " + Joueur.getNumChar() + " -5 0"); //TODO recupérer le numéro du char
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

        Feu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Joueur.setMessage("TIR " + Joueur.getNumChar() + " 0");
                EnvoieMessage tir = new EnvoieMessage();
                Thread t = new Thread(tir);
                t.start();
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    protected void onDestroy() {
        super.onDestroy();
        try {
            Joueur.fermerSocket();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
