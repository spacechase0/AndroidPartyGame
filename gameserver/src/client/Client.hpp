#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <util/Logger.hpp>

#include "net/Connection.hpp"
#include "net/NetStage.hpp"

namespace client
{
    class Client
    {
        public:
            Client();
            
            util::Logger log;
            
            bool connect();
            void disconnect();
            inline bool isConnected() const { return conn.socket.getLocalPort() != 0; }
            
            void send( const net::Packet* packet );
        
        private:
            net::Connection conn;
            std::unique_ptr< net::NetStage > stage;
    };
}

#endif // CLIENT_CLIENT_HPP
