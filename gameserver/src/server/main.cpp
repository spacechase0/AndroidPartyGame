#include "server/Server.hpp"

#include <iostream>
#include <SFML/System/Thread.hpp>
#include <string>

#include "Util.hpp"

using namespace server;

int main()
{
    Server s;
    auto run = [&]{ s.run(); };
    sf::Thread runThread( run );
    runThread.launch();
    
    while ( s.isRunning() )
    {
        std::string cmd;
        std::cout << "> ";
        std::getline( std::cin, cmd );
        if ( cmd == "" || cmd == " " ) continue;
        
        auto parsed = parseCommand( cmd );
        if ( parsed[ 0 ] == "stop" || parsed[ 0 ] == "quit" || parsed[ 0 ] == "exit" )
            s.stop();
        else
        {
            std::cout << util::format( "Command '$' not recognized.\n", parsed[ 0 ] );
        }
    }
}
