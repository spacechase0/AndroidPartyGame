#include "server/Match.hpp"

#include <algorithm>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>

#include "game/MatchData.hpp"
#include "server/Client.hpp"
#include "server/match/NetStage.hpp"
#include "server/Server.hpp"

namespace server
{
    Match::Match( Server& theServer, const game::MatchData& data, Client* host )
    :   server( theServer ),
        name( data.name ),
        maxPlayers( data.maxPlayers ),
        thread( &Match::run, this )
    {
        players.push_back( host );
        thread.launch();
    }
    
    Match::~Match()
    {
        thread.wait();
    }
    
    void Match::start()
    {
        if ( matchStarted ) return;
        
        sf::Lock lock( playersM );
        matchStarted = true;
        for ( auto player : players )
        {
            player->setNetStage( std::unique_ptr< net::NetStage >( new match::NetStage( server, ( * player ), ( * player->conn ), ( * this ) ) ) );
        }
    }
    
    const Client* Match::getHost() const
    {
        sf::Lock lock( playersM );
        if ( players.size() == 0 ) return nullptr;
        return players[ 0 ];
    }
    
    std::vector< Client* > Match::getPlayers() const
    {
        sf::Lock lock( playersM );
        return players;
    }
    
    bool Match::tryToJoin( Client* client )
    {
        sf::Lock lock( playersM );
        
        if ( matchStarted )
            return false;
        
        if ( players.size() >= getMaxPlayers() )
            return false;
        
        players.push_back( client );
        return true;
    }
    
    void Match::playerLeft( Client* client )
    {
        sf::Lock lock( playersM );
        auto it = std::find( players.begin(), players.end(), client );
        if ( it != players.end() )
        {
            players.erase( it );
        }
    }
    
    game::MatchData Match::asData() const
    {
        game::MatchData data( name, maxPlayers );
        
        sf::Lock lock( playersM );
        for ( auto player : players )
            data.players.push_back( player->user );
        
        return data;
    }

    std::string Match::getName() const
    {
        return name;
    }
    
    sf::Uint8 Match::getMaxPlayers() const
    {
        return maxPlayers;
    }
    
    void Match::run()
    {
        while ( server.isRunning() && players.size() > 0 )
        {
            {
                sf::Lock lock( playersM );
                auto it = players.begin();
                while ( it != players.end() )
                {
                    Client& client = ( * ( * it ) );
                    auto trans = client.update();
                    
                    if ( !client.isConnected() )
                    {
                        it = players.erase( it );
                    }
                    else ++it;
                }
            }
            
            sf::sleep( sf::milliseconds( 10 ) );
        }
    }
}
