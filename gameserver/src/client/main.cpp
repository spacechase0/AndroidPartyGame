#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics.hpp>

#include "client/Client.hpp"
#include "client/prelogin/NetStage.hpp"
#include "client/lobby/NetStage.hpp"
#include "client/match/NetStage.hpp"
#include "game/MatchData.hpp"

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
    {
        client::lobby::NetStage* lobby = dynamic_cast< client::lobby::NetStage* >( c.getNetStage() );
        
        bool hosting = false;
        lobby->onMatchList = [&]( const std::vector< game::MatchData >& matches )
        {
            c.log( "[INFO] Obtained $ matches: \n", matches.size() );
            for ( const auto& match : matches )
            {
                c.log( "[INFO] \t$ ($/$)\n", match.name, match.players.size(), static_cast< int >( match.maxPlayers ) );
                for ( const auto& player : match.players )
                    c.log( "[INFO] \t\t$\n", player );
            }
            
            if ( matches.size() == 0 )
            {
                lobby->createMatch( game::MatchData( "My Match", "test", 2 ) );
                hosting = true;
            }
            else
            {
                lobby->joinMatch( matches[ 0 ] );
            }
        };
        lobby->getMatchList();
        
        bool waiting = true;
        lobby->onMatchStart = [&]( const game::MatchData& data )
        {
            waiting = false;
        };
        
        bool started = false;
        while ( waiting )
        {
            c.update();
            
            if ( hosting && lobby->current.players.size() == lobby->current.maxPlayers )
            {
                if ( !started )
                {
                    lobby->startMatch();
                    started = true;
                }
            }
            
            sf::sleep( sf::seconds( 1 ) );
        }
    }
    {
        c.update();
        client::match::NetStage* match = dynamic_cast< client::match::NetStage* >( c.getNetStage() );
        if ( match == nullptr )
            c.log( "PROBLEMS!!!" );
        
        sf::RenderWindow window( sf::VideoMode( 400, 800 ), "Kingdom Party" );
        window.setFramerateLimit( 30 );
        
        while ( window.isOpen() )
        {
            sf::Event event;
            while ( window.pollEvent( event ) )
            {
                if ( event.type == sf::Event::Closed )
                    window.close();
            }
            
            window.clear( sf::Color::White );
            
            match->match.drawBoard( window );
            
            window.display();
        }
    }
}
