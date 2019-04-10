package com.premier.battlecoor;

import android.text.Editable;
import android.util.Log;

import java.io.IOException;
import java.io.Serializable;
import java.net.Socket;

// Cette classe est ok plus besoin de la modifer
public class Joueur  {
    final int PORT = 1977;
    private static String ip = "192.168.43.240";


    private static String pseudo;
    private static String role; //uniquement utile au début de la manette
    private static String numChar;
    private static String mes;
    private static Socket s;
    private static String reponse; //reponse du serveur
    public static boolean changerButtons = false;


    //Gestion des boutons
    protected static boolean GT = false, DT = false, HC = false, BC = false, GC = false, DC = false, GP = false, DP = false;

    Joueur() throws IOException {
        s = new Socket(ip, PORT);
    }

    public  static void setNumChar(String num){
        numChar = num;
    }

    public  static String getNumChar(){
        return numChar;
    }

    public  static Socket getSocket(){
        return s;
    }

    public static void fermerSocket() throws IOException {
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

    public static void setRole(String papel){
        switch (papel) {
            case "ROLE 0":
                role = "Conducteur";
                break;
            case "ROLE 1":
                role = "Tireur";
                break;
            case "ROLE 2":
                role = "Protecteur";
                break;
        }
    }
    public static String getRole(){return role;}
}
