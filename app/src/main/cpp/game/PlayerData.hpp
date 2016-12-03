#ifndef GAME_PLAYERDATA_HPP
#define GAME_PLAYERDATA_HPP

#include <SFML/System/Vector2.hpp>

#include "game/UserData.hpp"

namespace net
{
    class Buffer;
}

namespace game
{
    class MapData;
    
    struct PlayerData : public UserData
    {
        PlayerData();
        PlayerData( const std::string& theUser );
        
        sf::Uint8 stars = 0;
        sf::Uint16 coins = 0;
        sf::Vector2u pos = sf::Vector2u( 0, 0 );
        
        void move( const MapData& map );
    };
    
    net::Buffer& operator >> ( net::Buffer& buffer, PlayerData& player );
    net::Buffer& operator << ( net::Buffer& buffer, const PlayerData& player );
}

#endif // GAME_PLAYERDATA_HPP
