package com.premier.battlecoor;

import java.io.IOException;

public class CreationJoueur implements Runnable {

    Joueur J;
    @Override
    public void run() {
        try {
            J = new Joueur();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
