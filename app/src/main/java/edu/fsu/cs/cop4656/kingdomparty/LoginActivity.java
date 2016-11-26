package edu.fsu.cs.cop4656.kingdomparty;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class LoginActivity extends AppCompatActivity {

    private EditText confirmPassword;
    private Button login;
    private EditText password;
    private EditText username;
    public static String mUsername;
    private TextView promptText;
    private ImageButton helpButton;

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
        boolean check = true;
        String message = "Invalid ";

        mUsername = username.getText().toString();
        if (mUsername.length() == 0) {
            message = message.concat("Username");
            check = false;
        } else {
            for (int i = 0; i < mUsername.length(); i++) {
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
