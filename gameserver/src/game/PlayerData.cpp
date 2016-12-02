#include "game/PlayerData.hpp"

#include "game/MapData.hpp"
#include "game/TileData.hpp"
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
    
    void PlayerData::move( const MapData& map )
    {
        const TileData& tile = map.getTile( pos.x, pos.y );
        pos = tile.next[ 0 ];
        // TODO: Implement branching, stopping for events, ...
    }
    
    net::Buffer& operator >> ( net::Buffer& buffer, PlayerData& player )
    {
        buffer >> static_cast< UserData& >( player );
        buffer >> player.stars >> player.coins >> player.pos;
        return buffer;
    }
    
    net::Buffer& operator << ( net::Buffer& buffer, const PlayerData& player )
    {
        buffer << static_cast< const UserData& >( player );
        buffer << player.stars << player.coins << player.pos;
        return buffer;
    }
}
