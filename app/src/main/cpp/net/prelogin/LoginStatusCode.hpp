#ifndef NET_PRELOGIN_LOGINSTATUSCODE_HPP
#define NET_PRELOGIN_LOGINSTATUSCODE_HPP

#include <SFML/Config.hpp>

namespace net
{
    namespace prelogin
    {
        enum LoginStatusCode : sf::Uint8
        {
            // Login
            NoSuchUser,
            LoginFailed,
            LoginSuccessful,
            
            // Register
            UserAlreadyExists,
            RegisterSuccessful,
            
            NONE, // Not for sending!
        };
    }
}

#endif // NET_PRELOGIN_LOGINSTATUSCODE_HPP

