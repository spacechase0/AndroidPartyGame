#ifndef GAME_USERDATA_HPP
#define GAME_USERDATA_HPP

#include <string>

namespace net
{
    class Buffer;
}

namespace game
{
    struct UserData
    {
        std::string username;
        //std::string password;
        
        int color = 0xFF00FFFF;
    };
    
    net::Buffer& operator >> ( net::Buffer& buffer, UserData& user );
    net::Buffer& operator << ( net::Buffer& buffer, const UserData& user );
}

#endif // GAME_USERDATA_HPP
