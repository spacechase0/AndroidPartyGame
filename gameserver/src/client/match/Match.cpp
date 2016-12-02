#include "client/match/Match.hpp"

#include <cstdlib>
#include <ctime>
#include <list>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "client/Client.hpp"
#include "client/match/NetStage.hpp"
#include "game/MapData.hpp"

namespace client
{
    namespace match
    {
        using namespace game;
        using namespace net::match;
        
        Match::Match( Client& theClient, NetStage& theNetStage )
        :   client( theClient ),
            netStage( theNetStage )
        {
            std::srand( std::time( nullptr ) );
            
            font.loadFromFile( "res/dejavu/ttf/DejaVuSans.ttf" );
            fontMono.loadFromFile( "res/dejavu/ttf/DejaVuSansMono.ttf" );
            icons.loadFromFile( "res/icons.png" );
            
            dieBg.setSize( sf::Vector2f( 80, 80 ) );
            dieBg.setOrigin( 40, 40 );
            dieBg.setFillColor( sf::Color( 230, 230, 230 ) );
            dieBg.setOutlineColor( sf::Color::Black );
            dieBg.setOutlineThickness( 3.f );
            
            dieFg.setFont( font );
            dieFg.setFillColor( sf::Color::Black );
            dieFg.setCharacterSize( 50 );
        }
        
        void Match::update()
        {
            if ( dieNum != 0xFF && lastMove.getElapsedTime().asSeconds() >= TIME_MOVE )
            {
                --dieNum;
                netStage.players[ currentTurn ].move( netStage.map );
                
                if ( dieNum == 0xFF )
                {
                    currentTurn = ( currentTurn + 1 ) % netStage.players.size();
                }
                
                lastMove.restart();
            }
        }
        
        void Match::doEvent( const sf::Event& event )
        {
            if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( currentTurn == myTurn && dieBg.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
                {
                    rollingDie = true;
                    dieNum = rand() % 6;
                }
            }
            else if ( event.type == sf::Event::MouseButtonReleased )
            {
                if ( rollingDie )
                {
                    netStage.rollDie();
                }
            }
        }
        
        void Match::drawBoard( sf::RenderWindow& window )
        {
            if ( !cachedBoard )
                makeBoardCache();
            
            window.draw( &lines[ 0 ], lines.size(), sf::PrimitiveType::Lines );
            for ( const auto& spot : spots )
                window.draw( spot );
        }
        
        void Match::drawUi( sf::RenderWindow& window )
        {
            dieBg.setPosition( window.getSize().x / 2, 75 );
            dieBg.setOutlineThickness( currentTurn == myTurn ? 3 : 1 );
            window.draw( dieBg );
            if ( dieNum != 0xFF )
            {
                if ( rollingDie )
                {
                    dieNum = ( dieNum + 1 ) % 6;
                }
                
                dieFg.setString( util::toString( static_cast< int >( dieNum ) ) );
                dieFg.setOrigin( dieFg.getLocalBounds().width / 2, dieFg.getLocalBounds().height / 4 * 3 );
                dieFg.setPosition( dieBg.getPosition() );
                window.draw( dieFg );
            }
        }
        
        void Match::onDiceRoll( sf::Uint8 num )
        {
            rollingDie = false;
            dieNum = num;
            lastMove.restart();
        }
        
        void Match::makeBoardCache()
        {
            lines.clear();
            spots.clear();
            
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
                    shape.setPosition( ix * GRID_SIZE + 10, iy * GRID_SIZE + 10 );
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
                        sf::Vertex a( sf::Vector2f( ix * GRID_SIZE + 30, iy * GRID_SIZE + 30 ), sf::Color::Black );
                        sf::Vertex b( sf::Vector2f( next.x * GRID_SIZE + 30, next.y * GRID_SIZE + 30 ), sf::Color::White );
                        lines.push_back( a );
                        lines.push_back( b );
                    }
                }
            }
            
            cachedBoard = true;
        }
    }
}
