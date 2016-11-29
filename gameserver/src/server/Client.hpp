#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP

#include <memory>
#include <type_traits>

#include "server/ClientTransition.hpp"

namespace net
{
    class Connection;
    class NetStage;
    class Packet;
}

namespace server
{
    class Server;
    class Client
    {
        public:
            Client( Server& theServer, std::unique_ptr< net::Connection > theConn );
            ~Client();
            
            ClientTransition update();
            
            void disconnect();
            bool isConnected() const;
            
            void send( const net::Packet* packet );
            template< typename T >
            typename std::enable_if< std::is_base_of< net::Packet, T >::value >::type
            send( const T& packet )
            {
                send( &packet );
            }
            
            net::NetStage* getNetStage();
            const net::NetStage* getNetStage() const;
            void setNetStage( std::unique_ptr< net::NetStage > theStage );
            
            std::string user;
        
        private:
            Server& server;
            std::unique_ptr< net::Connection > conn;
            std::unique_ptr< net::NetStage > stage;
            std::unique_ptr< net::NetStage > pendingStage;
            
            friend class Server;
    };
}

#endif // SERVER_CLIENT_HPP
