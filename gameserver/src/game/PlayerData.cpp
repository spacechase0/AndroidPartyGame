#include "game/PlayerData.hpp"

#include "net/Buffer.hpp"

namespace game
{
    PlayerData::PlayerData()
    {
    }
    
    PlayerData::PlayerData( const std::string& theUser )
    {
        username = theUser;
    }
    
    net::Buffer& operator >> ( net::Buffer& buffer, PlayerData& player )
    {
        buffer >> static_cast< UserData& >( player );
        buffer >> player.stars >> player.coins >> player.pos;
    }
    
    net::Buffer& operator << ( net::Buffer& buffer, const PlayerData& player )
    {
        buffer << static_cast< const UserData& >( player );
        buffer << player.stars << player.coins << player.pos;
    }
}
