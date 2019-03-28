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
    //Cette classe envoie un message au serveur et attent toujours une réponse du serveur

    @Override
    public void run() {
        try {
            /*Socket*/
            InputStream in = Joueur.getSocket().getInputStream();
            OutputStream out = Joueur.getSocket().getOutputStream();
            BufferedReader reader =new BufferedReader(new InputStreamReader(in));

            //envoie de la requête au serveur
            PrintWriter writer = new PrintWriter(out);
            writer.print(Joueur.getMessage());
            writer.flush();


            //attente bloquante de la reponse su serveur
            Joueur.setReponse(reader.readLine());

            //verification si modification des bourons
            if(Joueur.getReponse().equals("NEW_BUTT")){


            }


        }
        catch (UnknownHostException e1) {
            e1.printStackTrace();
        }
        catch (IOException e2){
            e2.printStackTrace();
        }

    }


}
