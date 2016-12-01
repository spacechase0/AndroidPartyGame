#ifndef GAME_TILEDATA_HPP
#define GAME_TILEDATA_HPP

#include <vector>

namespace game
{
    struct TileData
    {
        enum Type : sf::Uint8
        {
            Blue,
            Red,
            Special,
            
            EMPTY,
        } type = EMPTY;
        
        bool hasStar = false;
        std::vector< sf::Vector2u > next;
    };
}

#endif // GAME_TILEDATA_HPP
