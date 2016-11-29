#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP

#include <memory>

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
            
            void update();
            
            void disconnect();
            bool isConnected() const;
            
            void send( const net::Packet* packet );
        
        private:
            Server& server;
            std::unique_ptr< net::Connection > conn;
            std::unique_ptr< net::NetStage > stage;
            
            friend class Server;
    };
}

#endif // SERVER_CLIENT_HPP
