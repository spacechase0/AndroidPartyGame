#ifndef SERVER_DUMMYUSERDATABASE_HPP
#define SERVER_DUMMYUSERDATABASE_HPP

#include <functional>
#include <list>
#include <map>
#include <string>

#include "server/IUserDatabase.hpp"

namespace server
{
    class DummyUserDatabase : public IUserDatabase
    {
        public:
            virtual void update() override;
            
            virtual void checkLogin( const std::string& user, const std::string& pass, LoginCallback&& callback ) override;
            virtual void registerUser( const std::string& user, const std::string& pass, LoginCallback&& callback ) override;
            
        private:
            std::map< std::string, std::string > users;
            std::list< std::function< void () > > callbacks;
    };
}

#endif // SERVER_DUMMYUSERDATABASE_HPP
