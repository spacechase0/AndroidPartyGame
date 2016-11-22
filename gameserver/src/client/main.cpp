#include "client/Client.hpp"

using namespace client;

int main()
{
    Client c;
    if ( !c.connect() )
    {
        c.log( "[ERROR] Failed to connect to server!\n" );
        return 0;
    }
    c.log( "[INFO] Connected to server.\n" );
}
