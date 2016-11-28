#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <util/Logger.hpp>

#include "net/Connection.hpp"

namespace client
{
    class Client
    {
        public:
            Client();
            
            util::Logger log;
            
            bool connect();
            
            inline bool isConnected() const { return conn.socket.getLocalPort() != 0; }
        
        private:
            net::Connection conn;
    };
}

#endif // CLIENT_CLIENT_HPP
