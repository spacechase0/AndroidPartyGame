package edu.fsu.cs.cop4656.kingdomparty;

public class Native
{
    static
    {
        System.loadLibrary( "kingdomparty-native" );
    }

    static long makeClient()
    {
        return 0;
    }
}
