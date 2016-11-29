#include "server/Server.hpp"

#include <memory>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

#include "game/MatchData.hpp"
#include "net/Connection.hpp"
#include "server/Client.hpp"
#include "server/DummyUserDatabase.hpp"
#include "server/Match.hpp"

namespace server
{
    Server::Server()
    :   log( "server.log" ),
        users( new DummyUserDatabase() ),
        lobbyThread( &Server::runLobby, this ),
        lobby( * this ),
        listenerThread( &Server::listen, this )
    {
    }
    
    Server::~Server()
    {
    }
    
    void Server::addMatch( std::unique_ptr< Match > match )
    {
        sf::Lock lock( matchesM );
        matches.insert( std::move( match ) );
    }
    
    void Server::removeMatch( Match* match )
    {
        sf::Lock lock( matchesM );
        for ( auto it = matches.begin(); it != matches.end(); ++it )
        {
            if ( it->get() == match )
            {
                matches.erase( it );
                break;
            }
        }
    }
    
    Match* Server::findMatch( const std::string& host )
    {
        sf::Lock lock( matchesM );
        for ( auto& match : matches )
            if ( match->getHost()->user == host )
                return match.get();
        
        return nullptr;
    }
    
    std::vector< game::MatchData > Server::getMatchData() const
    {
        sf::Lock lock( matchesM );
        
        std::vector< game::MatchData > ret;
        ret.reserve( matches.size() );
        
        for ( const auto& match : matches )
            ret.push_back( match->asData() );
        
        return ret;
    }
    
    void Server::run()
    {
        lobbyThread.launch();
        listenerThread.launch();
        
        while ( isRunning() )
        {
            {
                sf::Lock lock( clientsM );
                auto it = clients.begin();
                while ( it != clients.end() )
                {
                    Client& client = ( * it->get() );
                    auto trans = client.update();
                    
                    if ( !client.isConnected() )
                    {
                        it = clients.erase( it );
                    }
                    else if ( trans.type != ClientTransition::None )
                    {
                        if ( trans.type == ClientTransition::Lobby )
                            lobby.moveToLobby( std::move( * it ) );
                        else if ( trans.type == ClientTransition::Match )
                            ; // TODO
                        it = clients.erase( it );
                    }
                    else ++it;
                }
            }
            users->update();
            
            sf::sleep( sf::milliseconds( 10 ) );
        }
    }
    
    void Server::stop()
    {
        log( "[INFO] Stopping server...\n" );
        running = false;
        listener.close();
    }
    
    void Server::runLobby()
    {
        while ( isRunning() )
        {
            lobby.update();
            sf::sleep( sf::milliseconds( 10 ) );
        }
    }
    
    void Server::listen()
    {
        //sf::TcpListener listener;
        if ( listener.listen( GAME_PORT ) != sf::Socket::Done )
        {
            log( "[ERROR] Failed to listen. Stopping server.\n" );
            stop();
            return;
        }
        
        while ( isRunning() )
        {
            std::unique_ptr< net::Connection > conn( new net::Connection() );
            if ( listener.accept( conn->socket ) != sf::Socket::Done )
                continue;
            conn->socket.setBlocking( false );
            
            log( "[INFO] New connection.\n" );
            std::unique_ptr< Client > client( new Client( ( * this ), std::move( conn ) ) );
            
            sf::Lock lock( clientsM );
            clients.push_back( std::move( client ) );
        }
    }
}
