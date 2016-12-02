#include "game/UserData.hpp"

#include "net/Buffer.hpp"

namespace game
{
    net::Buffer& operator >> ( net::Buffer& buffer, UserData& user )
    {
        buffer >> user.username >> user.color;
        // Why would we want to read/write the password?
    }
    
    net::Buffer& operator << ( net::Buffer& buffer, const UserData& user )
    {
        buffer << user.username << user.color;
    }
}
