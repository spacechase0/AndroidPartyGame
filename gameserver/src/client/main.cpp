#include "client/Client.hpp"
#include "client/prelogin/NetStage.hpp"
#include "client/lobby/NetStage.hpp"

#include <SFML/System/Sleep.hpp>

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
    
    {
        bool inPreLogin = true;
        c.onStageChange = [ &inPreLogin ](){ inPreLogin = false; };
        
        client::prelogin::NetStage* prelogin = dynamic_cast< client::prelogin::NetStage* >( c.getNetStage() );
        prelogin->login( "spacechase0", "password" );
        while ( inPreLogin )
        {
            c.update();
            if ( !c.isConnected() )
            {
                c.log( "[INFO] Lost connection to server.\n" );
                return 0;
            }
            
            auto status = prelogin->getLastLoginStatus();
            if ( status == net::prelogin::LoginStatusCode::NONE )
                continue;
            
            if ( status == net::prelogin::LoginStatusCode::NoSuchUser )
            {
                prelogin->registerUser( "spacechase0", "password" );
            }
            else if ( status == net::prelogin::LoginStatusCode::LoginFailed )
            {
                c.log( "[ERROR] Login failed. But this isn't implemented yet?" );
                return 0;
            }
            else if ( status == net::prelogin::RegisterSuccessful )
            {
                c.log( "[INFO] Registered $.\n", "spacechase0" );
                prelogin->login( "spacechase0", "password" );
            }
            // LoginSuccessful not checked because the loop should stop by then?
        }
        
        c.log( "[INFO] Finished prelogin stage.\n" );
    }
}
