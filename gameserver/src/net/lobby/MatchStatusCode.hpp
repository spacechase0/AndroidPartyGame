#ifndef NET_LOBBY_MATCHSTATUSCODE_HPP
#define NET_LOBBY_MATCHSTATUSCODE_HPP

#include <SFML/Config.hpp>

namespace net
{
    namespace lobby
    {
        enum MatchStatusCode : sf::Uint8
        {
            MatchNotExist,
            MatchWasFull,
            KickedFromMatch,
            JoinedMatch,
            LeftMatch,
            StartMatch,
            
            NONE,
        };
    }
}

#endif // NET_LOBBY_MATCHSTATUSCODE_HPP

