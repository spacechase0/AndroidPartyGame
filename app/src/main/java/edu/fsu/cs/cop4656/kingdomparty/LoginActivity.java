package edu.fsu.cs.cop4656.kingdomparty;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
    }

    public void attemptLogin(View view) {
        if(view == findViewById(R.id.loginButton)){
            Intent mIntent = new Intent(this, MainActivity.class);
            startActivity(mIntent);
        }
    }
}
