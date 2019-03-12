package com.premier.battlecoor;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;

public class Pseudo extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.pseudo);
        Button Go = (Button) findViewById(R.id.button);
        final EditText nickname = (EditText) findViewById(R.id.editText);
        Go.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String mes = nickname.getText().toString();
                Thread t = new Thread(new EnvoieMessage(mes));
                t.start();
            }
        });
    }


}
