package com.premier.battlecoor;

import android.app.Activity;
import android.util.Log;
import android.widget.EditText;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.net.Socket;
import java.net.UnknownHostException;

public class EnvoieMessage  implements Runnable{
    //TODO confirmation du serveur pour s'assurer que le pseudo est unique
    //message erreur pseudo non existat déjà
    //Mettre la socekt en variable envoie message
    private String pseudo;
    private Socket s;
    private String res; //reponse du serveur
    EnvoieMessage(String nickname){
        pseudo = nickname;
    }
    @Override
    public void run() {
        final int PORT = 1977;
        final String ip = "192.168.1.28";
        try {
            /*Socket*/ s = new Socket(ip, PORT);
            InputStream in = s.getInputStream();
            OutputStream out = s.getOutputStream();
            BufferedReader reader =new BufferedReader(new InputStreamReader(in));

            //envoie de la requête au serveur
            PrintWriter writer = new PrintWriter(out);
            writer.print(pseudo);
            writer.flush();


            //attente bloquante de la reponse su serveur
            Log.d("affichage", "TESTTEST");
            String reponse = reader.readLine();

            Log.d("affichage", "Réponse reçu : "+reponse);


            //Vérification unicité du pseudo
            res = reponse;
            /*Modification pour ne pas perdre la connextion
            if( reponse.equals("PSEUDO_POK")) {

            }
            if (reponse.equals("MENU_JOUEUR")) {

            }

            s.close();
            ***************************************/
        }
        catch (UnknownHostException e1) {
            e1.printStackTrace();
        }
        catch (IOException e2){
            e2.printStackTrace();
        }

    }

    public void fermerSocket() throws IOException {
        s.close();
    }

    public String getReponse(){
        return res;
    }
}
