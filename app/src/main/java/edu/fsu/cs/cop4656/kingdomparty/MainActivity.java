package edu.fsu.cs.cop4656.kingdomparty;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import static android.R.attr.fragment;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener,
        ProfileFragment.OnFragmentInteractionListener, MatchesFragment.OnFragmentInteractionListener,
        CreateMatchFragment.OnFragmentInteractionListener {

    FragmentManager fragmentManager;
    Fragment fragment;

    Toolbar toolbar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        toolbar = (Toolbar) findViewById(R.id.toolbar);

        changeActionBarText(toolbar, "Profile");

        fragmentManager = getSupportFragmentManager();

        fragmentManager.beginTransaction().replace(R.id.flContent,ProfileFragment.newInstance("","")).commit();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        View header = navigationView.getHeaderView(0);

        String greetingText = "Hello, " + LoginActivity.mUsername + "!";
        TextView text = (TextView) header.findViewById(R.id.usernameTextView);
        text.setText(greetingText);

    }

    private void changeActionBarText(Toolbar t, String s) {
        t.setTitle(s);
        setSupportActionBar(t);
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, t, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.profile, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();
        fragment = null;

        if (id == R.id.nav_profile) {
            fragment = ProfileFragment.newInstance("", "");
            changeActionBarText(toolbar, "Profile");
        } else if (id == R.id.nav_matches) {
            fragment = MatchesFragment.newInstance("", "");
            changeActionBarText(toolbar, "Matches");
        } else if (id == R.id.nav_logout) {
            Intent mIntent = new Intent(this, LoginActivity.class);
            startActivity(mIntent);
        }

        if (fragment != null) {
            fragmentManager.beginTransaction().replace(R.id.flContent, fragment).commit();
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    @Override
    public void onFragmentInteraction(Uri uri) {

    }

    public void createMatch(View view) {
        fragment = CreateMatchFragment.newInstance("","");
        changeActionBarText(toolbar,"Create Match");
        if(fragment != null)
            fragmentManager.beginTransaction().replace(R.id.flContent,fragment).commit();
    }
}
