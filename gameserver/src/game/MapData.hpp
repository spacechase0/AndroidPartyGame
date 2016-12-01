#ifndef GAME_MAPDATA_HPP
#define GAME_MAPDATA_HPP

#include <map>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

#include "game/TileData.hpp"

namespace net
{
    class Buffer;
}

namespace game
{
    class MapData
    {
        public:
            bool load( const std::string& filename );
            
            std::string getName() const;
            sf::Vector2u getSize() const;
            
            TileData& getTile( unsigned int x, unsigned int y );
            const TileData& getTile( unsigned int x, unsigned int y ) const;
            
            sf::Vector2u getStart() const;
            
            sf::Vector2u findNamedTile( const std::string& name ) const;
            
            net::Buffer& operator >> ( net::Buffer& buffer );
            net::Buffer& operator << ( net::Buffer& buffer ) const;
        
        private:
            std::string name;
            sf::Vector2u size;
            std::vector< TileData > tiles;
            std::map< std::string, sf::Vector2u > namedTiles;
            sf::Vector2u start;
            
            inline unsigned int tileIndex( unsigned int x, unsigned int y ) const
            {
                return x + y * size.x;
            }
            inline sf::Vector2u tilePos( unsigned int idx ) const
            {
                return sf::Vector2u( idx % size.x, idx / size.x );
            }
    };
}

#endif // GAME_MAPDATA_HPP
