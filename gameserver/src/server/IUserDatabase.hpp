#ifndef SERVER_IUSERDATABASE_HPP
#define SERVER_IUSERDATABASE_HPP

#include <functional>
#include <string>

#include "net/prelogin/LoginStatusCode.hpp"

namespace server
{
    class IUserDatabase
    {
        public:
            virtual ~IUserDatabase();
            
            virtual void update() = 0;
            
            typedef std::function< void ( net::prelogin::LoginStatusCode ) > LoginCallback;
            
            virtual void checkLogin( const std::string& user, const std::string& pass, LoginCallback&& callback ) = 0;
            virtual void registerUser( const std::string& user, const std::string& pass, LoginCallback&& callback ) = 0;
    };
}

#endif // SERVER_IUSERDATABASE_HPP
