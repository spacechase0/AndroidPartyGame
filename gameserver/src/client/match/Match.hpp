#ifndef CLIENT_MATCH_MATCH_HPP
#define CLIENT_MATCH_MATCH_HPP

#include <list>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

namespace sf
{
    class Event;
    class RenderWindow;
}

namespace client
{
    class Client;
    
    namespace match
    {
        class NetStage;
        
        class Match
        {
            public:
                Match( Client& theClient, NetStage& theNetStage );
                
                void doEvent( const sf::Event& event );
                
                void drawBoard( sf::RenderWindow& window );
                void drawUi( sf::RenderWindow& window );
                
                int currentTurn = 0;
                int myTurn = 0;
                
                void onDiceRoll( sf::Uint8 num );
            
            private:
                Client& client;
                NetStage& netStage;
                
                sf::Font font;
                sf::Font fontMono;
                sf::Texture icons;
                
                std::vector< sf::Vertex > lines;
                std::list< sf::CircleShape > spots;
                bool cachedBoard = false;
                void makeBoardCache();
                
                sf::RectangleShape dieBg;
                sf::Text dieFg;
                sf::Uint8 dieNum = 0xFF;
                bool rollingDie = false;
                
                friend class NetStage;
        };
    }
}

#endif // CLIENT_MATCH_MATCH_HPP
