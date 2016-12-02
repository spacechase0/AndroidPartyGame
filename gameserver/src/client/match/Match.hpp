#ifndef CLIENT_MATCH_MATCH_HPP
#define CLIENT_MATCH_MATCH_HPP

#include <list>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

namespace sf
{
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
                
                void drawBoard( sf::RenderWindow& window );
            
            private:
                Client& client;
                NetStage& netStage;
                
                std::vector< sf::Vertex > lines;
                std::list< sf::CircleShape > spots;
                bool cachedBoard = false;
                void makeBoardCache();
                
                friend class NetStage;
        };
    }
}

#endif // CLIENT_MATCH_MATCH_HPP
