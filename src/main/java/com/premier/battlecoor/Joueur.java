package com.premier.battlecoor;

import android.util.Log;

import java.io.IOException;
import java.io.Serializable;
import java.net.Socket;

public class Joueur implements Serializable {
    final int PORT = 1977;
    final String ip = "192.168.1.28";

    private static String pseudo;
    private static String mes;
    private static Socket s;
    private static String reponse; //reponse du serveur

    Joueur() throws IOException {
        s = new Socket(ip, PORT);
    }

    public void setSocket(Socket n){
        s = n;
    }

    public static Socket getSocket(){
        return s;
    }

    public void fermerSocket() throws IOException {
        s.close();
    }

    public static void setReponse(String l){
        reponse = l;
    }
    public static String getReponse(){
        return reponse;
    }

    public static String getMessage(){
        return mes;
    }
    //A modifier avant d'envoyer un message
    public static void setMessage(String message){
        mes = message;
    }
}
