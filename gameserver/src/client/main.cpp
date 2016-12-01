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
    
    /*{
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
                lobby->createMatch( game::MatchData( "My Match", 2 ) );
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
    }*/
    {
        c.update();
        client::match::NetStage* match = dynamic_cast< client::match::NetStage* >( c.getNetStage() );
        if ( match == nullptr )
            c.log( "PROBLEMS!!!" );
        
        sf::RenderWindow window( sf::VideoMode( 400, 800 ), "Kingdom Party" );
        window.setFramerateLimit( 30 );
        
        sf::Font font;
        font.loadFromFile("DejaVuSans.ttf");
        
        sf::Text a;
        a.setFont(font);
        a.setCharacterSize(20);
        a.setString("user1");
        a.setColor(sf::Color::Black);
        a.setOrigin( a.getLocalBounds().width / 2, a.getLocalBounds().height / 2 + 50 );
        
        sf::RectangleShape ar;
        ar.setSize( sf::Vector2f(16, 30) );
        ar.setFillColor( sf::Color( 150, 200, 255 ) );
        ar.setOutlineColor( sf::Color::Black );
        ar.setOutlineThickness( 2 );
        ar.setOrigin(8, 30);
        
        sf::Text b=a;
        b.setString("user2");
        b.setOrigin( b.getLocalBounds().width / 2, b.getLocalBounds().height / 2 + 50 );
        sf::RectangleShape br=ar;
        br.setFillColor( sf::Color( 255, 200, 150 ) );
        
        sf::Color tiles[ 16 ];
        for ( int i = 0; i < 16; ++i )
        {
            if ( i % 4 == 0 )
                tiles[ i ] = sf::Color::Green;
            else if ( i % 2 == 0 )
                tiles[ i ] = sf::Color::Red;
            else
                tiles[ i ] = sf::Color::Blue;
        }
        
        int ax=100,ay=200;
        int bx=300,by=350;
        
        int c = 0;
        
        std::string s;
        int ac=12,as=1;
        int bc=26,bs=0;
        
        while ( window.isOpen() )
        {
            sf::Event event;
            while ( window.pollEvent( event ) )
            {
                if ( event.type == sf::Event::Closed )
                    window.close();
                else if ( event.type == sf::Event::MouseButtonPressed )
                {
                    if(c==0)
                    {
                        ax += 50;
                        s = "1";
                        ac+=3;
                    }
                    else if ( c == 1)
                    {
                        by += 50;
                        bx -= 100;
                        s = "3";
                        bc-=3;
                    }
                    else if ( c == 2)
                    {
                        ax += 150;
                        ay += 100;
                        s = "5";
                        ac-=3;
                    }
                    else if ( c == 3)
                    {
                        bx -=100;
                        s = "2";
                        bc-=20;
                        bs+=1;
                    }
                    
                    ++c;
                }
            }
            
            window.clear( sf::Color::White );
            
            float x = 0, y = 0;
            for ( int i = 0; i < 16; ++i )
            {
                sf::CircleShape shape;
                shape.setRadius( 20 );
                shape.setOrigin( 20, 20 );
                shape.setFillColor( tiles[ i ] );
                shape.setPosition( 100 + x, 200 + y );
                if(i==12)
                {
                    shape.setOutlineColor(sf::Color(250,250,100));
                    shape.setOutlineThickness(5);
                }
                window.draw( shape );
                
                if ( i < 4 ) x += 50;
                else if ( i < 8 ) y += 50;
                else if ( i < 12 ) x -= 50;
                else if ( i < 16 ) y -= 50;
            }
            
            a.setPosition( ax, ay );
            ar.setPosition( ax, ay );
            b.setPosition( bx, by );
            br.setPosition( bx, by );
            window.draw(ar);
            window.draw(a);
            window.draw(br);
            window.draw(b);
            
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(30);
            t.setString("user1: \n  "+util::toString(ac)+" coins\n  "+util::toString(as)+" star");
            t.setPosition(25,675);
            t.setColor(sf::Color::Black);
            window.draw(t);
            t.setString("user2: \n  "+util::toString(bc)+" coins\n  "+util::toString(bs)+" stars");
            t.setPosition(225,675);
            window.draw(t);
            
            t.setCharacterSize(50);
            t.setString(s);
            t.setPosition(200-t.getLocalBounds().height/2,50);
            window.draw(t);
            
            window.display();
        }
    }
}
