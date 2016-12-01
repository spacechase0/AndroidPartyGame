#include "server/DummyUserDatabase.hpp"

namespace server
{
    void DummyUserDatabase::update()
    {
        // TODO: This will crash if the user logs out before the 'request' finishes
        // Unlikely to happen with this setup, but with a real database it will be an issue.
        for ( auto& callback : callbacks )
            callback();
        callbacks.clear();
    }
    
    void DummyUserDatabase::checkLogin( const std::string& user, const std::string& pass, LoginCallback&& callback )
    {
        net::prelogin::LoginStatusCode ret = net::prelogin::LoginStatusCode::NONE;
        
        auto it = users.find( user );
        if ( it == users.end() )
            ret = net::prelogin::LoginStatusCode::NoSuchUser;
        else if ( it->second != pass )
            ret = net::prelogin::LoginStatusCode::LoginFailed;
        else
            ret = net::prelogin::LoginStatusCode::LoginSuccessful;
        
        callbacks.push_back( [ ret, callback ](){ callback( ret ); } );
    }
    
    void DummyUserDatabase::registerUser( const std::string& user, const std::string& pass, LoginCallback&& callback )
    {
        net::prelogin::LoginStatusCode ret = net::prelogin::LoginStatusCode::NONE;
        
        auto it = users.find( user );
        if ( it != users.end() )
            ret = net::prelogin::LoginStatusCode::UserAlreadyExists;
        else
        {
            ret = net::prelogin::LoginStatusCode::RegisterSuccessful;
            users.insert( { user, pass } );
        }
        
        callbacks.push_back( [ ret, callback ](){ callback( ret ); } );
    }
}
