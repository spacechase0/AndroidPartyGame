#ifndef CLIENT_MATCH_MATCH_HPP
#define CLIENT_MATCH_MATCH_HPP

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
        };
    }
}

#endif // CLIENT_MATCH_MATCH_HPP
