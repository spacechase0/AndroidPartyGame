#include "server/Match.hpp"

#include "game/MatchData.hpp"
#include "server/Client.hpp"

namespace server
{
    Match::Match( Server& theServer, const game::MatchData& data, Client* host )
    :   server( theServer ),
        name( data.name ),
        maxPlayers( data.maxPlayers )
    {
        players.push_back( host );
    }
    
    const Client* Match::getHost() const
    {
        if ( players.size() == 0 ) return nullptr;
        return players[ 0 ];
    }
    
    const std::vector< Client* > Match::getPlayers() const
    {
        return players;
    }
    
    game::MatchData Match::asData() const
    {
        game::MatchData data( name, maxPlayers );
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
}
