package com.premier.battlecoor;

import android.text.Editable;
import android.util.Log;

import java.io.IOException;
import java.io.Serializable;
import java.net.Socket;

// Cette classe est ok plus besoin de la modifer
public class Joueur  {
    final int PORT = 1977;
    private static String ip = "192.168.1.103";

    private static String pseudo;
    private static String numChar;
    private static String mes;
    private static Socket s;
    private static String reponse; //reponse du serveur

    Joueur() throws IOException {
        s = new Socket(ip, PORT);
    }

    public  static void setNumChar(String num){
        numChar = num;
    }

    public  static String getNumChar(){
        return numChar;
    }
    public void setSocket(Socket n){
        s = n;
    }

    public  static Socket getSocket(){
        return s;
    }

    public void fermerSocket() throws IOException {
        s.close();
    }

    public  static void setReponse(String l){
        reponse = l;
    }
    public static String getReponse(){
        return reponse;
    }

    public  static String getMessage(){
        return mes;
    }
    //A modifier avant d'envoyer un message
    public static void setMessage(String message){
        mes = message;
    }

    public static void setIp(String add){ip = add;}
}
