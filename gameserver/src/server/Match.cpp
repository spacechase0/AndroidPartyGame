#include "server/Match.hpp"

#include <algorithm>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>

#include "game/MatchData.hpp"
#include "net/match/Packets.hpp"
#include "net/lobby/MatchStatusPacket.hpp"
#include "server/Client.hpp"
#include "server/match/NetStage.hpp"
#include "server/Server.hpp"

namespace server
{
    using namespace net::match;
    
    Match::Match( Server& theServer, const game::MatchData& data, Client* host )
    :   server( theServer ),
        name( data.name ),
        mapId( data.map ),
        maxPlayers( data.maxPlayers ),
        thread( &Match::run, this )
    {
        players.push_back( host );
        //thread.launch();
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
        
        const auto& mapData = server.maps[ mapId ];
        playerData.clear();
        for ( const auto& player : players )
        {
            game::PlayerData data( player->user );
            data.pos = mapData.getStart();
            playerData.push_back( data );
        }
        
        net::lobby::MatchStatusPacket packet( net::lobby::MatchStatusCode::StartMatch, asData() );
        net::match::MatchStartDataPacket packet2( mapData, playerData );
        for ( auto player : players )
        {
            player->send( packet );
            player->setNetStage( std::unique_ptr< net::NetStage >( new match::NetStage( server, ( * player ), ( * player->conn ), ( * this ) ) ) );
            player->send( packet2 );
        }
    }
    
    bool Match::hasStarted() const
    {
        return matchStarted;
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
        
        net::lobby::MatchStatusPacket packet( net::lobby::MatchStatusCode::MatchStatus, asData() );
        for ( auto player : players )
        {
            if ( player == client )
                continue;
            
            player->send( packet );
        }
        return true;
    }
    
    void Match::playerLeft( Client* client )
    {
        sf::Lock lock( playersM );
        auto it = std::find( players.begin(), players.end(), client );
        if ( it != players.end() )
        {
            players.erase( it );
            
            net::lobby::MatchStatusPacket packet( net::lobby::MatchStatusCode::MatchStatus, asData() );
            for ( auto player : players )
            {
                player->send( packet );
            }
        }
    }
    
    void Match::playerRolledDie( Client* client )
    {
        sf::Lock lock( playersM );
        auto it = std::find( players.begin(), players.end(), client );
        if ( it == players.end() || it - players.begin() != currentTurn || roll != 0xFF )
            return;
        
        roll = rand() % 6;
        DiceRollPacket packet( roll );
        for ( auto& player : players )
        {
            player->send( packet );
        }
        
        lastMove.restart();
    }
    
    game::MatchData Match::asData() const
    {
        game::MatchData data( name, mapId, maxPlayers );
        
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
            update();
            
            sf::sleep( sf::milliseconds( 10 ) );
        }
    }
    
    void Match::update()
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
        
        if ( roll != 0xFF && lastMove.getElapsedTime().asSeconds() >= TIME_MOVE )
        {
            --roll;
            playerData[ currentTurn ].move( server.maps[ mapId ] );
            server.log("[INFO] $ moved to ($,$)\n", playerData[currentTurn].username,playerData[currentTurn].pos.x, playerData[currentTurn].pos.y);
            
            if ( roll == 0xFF )
            {
                currentTurn = ( currentTurn + 1 ) % playerData.size();
            }
            
            lastMove.restart();
        }
    }
}
