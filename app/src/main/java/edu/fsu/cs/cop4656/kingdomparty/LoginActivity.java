package edu.fsu.cs.cop4656.kingdomparty;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;



public class LoginActivity extends AppCompatActivity {

    private EditText confirmPassword;
    private Button login;
    private EditText password;
    private EditText username;
    public static String mUsername;
    public static String mPassword;
    private TextView promptText;
    private ImageButton helpButton;
    public static boolean check = true;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        username = (EditText) findViewById(R.id.username);
        confirmPassword = (EditText) findViewById(R.id.confirmPswd);
        password = (EditText) findViewById(R.id.password);
        login = (Button) findViewById(R.id.login_button);
        promptText = (TextView) findViewById(R.id.signUpText);
        helpButton = (ImageButton) findViewById(R.id.helpButton);
    }

    public void myLoginHandler(View v) {
        if (v == login) {
            if (login.getText().toString().equals("Log In"))
                confirmPassword.getText().clear();
            if (checkFields()) {
                Intent myIntent = new Intent(this, MainActivity.class);
                startActivity(myIntent);
            } else
                pressedSignUp();
        } else if (v == promptText) {
            if (login.getText().toString().equals("Log In")) {
                confirmPassword.setVisibility(View.VISIBLE);
                login.setText("Sign Up");
                promptText.setText("Already have an account? Log in!");
            } else {
                confirmPassword.setVisibility(View.GONE);
                login.setText("Log In");
                promptText.setText("Need an account? Sign Up!");
            }
        } else if (v == helpButton){
            Intent myIntent = new Intent(this, HelpActivity.class);
            startActivity(myIntent);
        }
    }

    private void pressedSignUp() {
        Toast.makeText(this, "Sign Up", Toast.LENGTH_LONG);
    }

    private boolean checkFields() {
        check = true;
        String message = "Invalid ";

        mUsername = username.getText().toString();
        mPassword = password.getText().toString();
        if (mUsername.length() == 0) {
            message = message.concat("Username");
            check = false;
        } else {
            for (int i = 0; i < mUsername.length(); i++) {
                Log.e("USERNAME",mUsername);
                Log.e("PASSWORD",mPassword);
                String url = "http://kingdomparty.spacechase0.com/checklogin.php?username="+mUsername+"&password="+mPassword;
                CheckLogin checkLogin = new CheckLogin();
                checkLogin.doInBackground(url);


                if (!Character.isLetterOrDigit(mUsername.charAt(i))) {
                    username.getText().clear();
                    message = message.concat("Username");
                    check = false;
                    break;
                }
            }
        }

        if (confirmPassword.getVisibility() == View.VISIBLE) {
            if (!password.getText().toString().equals(confirmPassword.getText().toString())) {
                password.getText().clear();
                confirmPassword.getText().clear();
                message = message.concat((message.equals("Invalid Username")) ? "/Password" : "Password");
                check = false;
            } else if (password.getText().toString().length() == 0) {
                password.getText().clear();
                confirmPassword.getText().clear();
                message = message.concat((message.equals("Invalid Username")) ? "/Password" : "Password");
                check = false;
            }
        } else if (password.getText().toString().length() == 0) {
            message = message.concat((message.equals("Invalid Username")) ? "/Password" : "Password");
            check = false;
        }
        if (!check) {
            Toast.makeText(this, message, Toast.LENGTH_LONG).show();
        }
        return check;
    }
}

class CheckLogin extends AsyncTask<String , Void ,String> {
    String server_response;
    String Artist_Name;
    String Song_Name;
    @Override
    protected String doInBackground(String... strings) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        URL url;
        HttpURLConnection urlConnection = null;

        try {
            url = new URL(strings[0]);
            urlConnection = (HttpURLConnection) url.openConnection();
            int responseCode = urlConnection.getResponseCode();

            if (responseCode == HttpURLConnection.HTTP_OK) {
                server_response = readStream(urlConnection.getInputStream());
                if(server_response.equals("authentic")){

                    LoginActivity.check = true;
                    Log.e("AUTHENTIC","SERVER");


                }
                else{

                    LoginActivity.check = false;

                }
                
                Log.v("CatalogClient", server_response);

            }
          

        } catch (Exception e) {
            Log.e("ERROR","SERVER");
            e.printStackTrace();
        }


        return null;
    }



    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        Log.e("Response", "" + server_response);
    }
    private String readStream(InputStream is) {
        try {
            ByteArrayOutputStream bo = new ByteArrayOutputStream();
            int i = is.read();
            while(i != -1) {
                bo.write(i);
                i = is.read();
            }
            return bo.toString();
        } catch (IOException e) {
            return "";
        }
    }
}


