#ifndef GAME_USERDATA_HPP
#define GAME_USERDATA_HPP

namespace game
{
    struct UserData
    {
        std::string username;
        std::string password;
        
        int color = 0xFF00FFFF;
    };
}

#endif // GAME_USERDATA_HPP
