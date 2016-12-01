#include "client/match/Match.hpp"

#include <list>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

#include "client/Client.hpp"
#include "client/match/NetStage.hpp"
#include "game/MapData.hpp"

namespace client
{
    namespace match
    {
        using namespace game;
        
        Match::Match( Client& theClient, NetStage& theNetStage )
        :   client( theClient ),
            netStage( theNetStage )
        {
        }
        
        void Match::drawBoard( sf::RenderWindow& window )
        {
            std::vector< sf::Vertex > lines;
            std::list< sf::CircleShape > spots;
            
            for ( std::size_t ix = 0; ix < netStage.map.getSize().x; ++ix )
            {
                for ( std::size_t iy = 0; iy < netStage.map.getSize().y; ++iy )
                {
                    const TileData& tile = netStage.map.getTile( ix, iy );
                    if ( tile.type == TileData::Type::EMPTY ) continue;
                    
                    sf::CircleShape shape;
                    shape.setOutlineColor( sf::Color( 0, 0, 0, 50 ) );
                    shape.setOutlineThickness( 1 );
                    shape.setRadius( 20 );
                    shape.setPosition( ix * 50 + 10, iy * 50 + 10 );
                    switch ( tile.type )
                    {
                        case TileData::Type::Blue:    shape.setFillColor( sf::Color::Blue  ); break;
                        case TileData::Type::Red:     shape.setFillColor( sf::Color::Red   ); break;
                        case TileData::Type::Special: shape.setFillColor( sf::Color::Green ); break;
                        default: shape.setFillColor( sf::Color( 255, 0, 255 ) ); break;
                    }
                    spots.push_back( shape );
                    
                    for ( auto next : tile.next )
                    {
                        sf::Vertex a( sf::Vector2f( ix * 50 + 30, iy * 50 + 30 ), sf::Color::Black );
                        sf::Vertex b( sf::Vector2f( next.x * 50 + 30, next.y * 50 + 30 ), sf::Color::White );
                        lines.push_back( a );
                        lines.push_back( b );
                    }
                }
            }
            
            client.log("draw $ $ $ $ $\n", lines.size(), spots.size(), netStage.map.getName(), netStage.map.getSize().x, netStage.map.getSize().y);
            
            window.draw( &lines[ 0 ], lines.size(), sf::PrimitiveType::Lines );
            for ( const auto& spot : spots )
                window.draw( spot );
        }
    }
}
