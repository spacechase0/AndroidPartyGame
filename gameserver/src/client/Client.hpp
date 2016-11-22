#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <util/Logger.hpp>

namespace client
{
    class Client
    {
        public:
            Client();
            
            util::Logger log;
            
            bool connect();
            
            inline bool isConnected() const { return socket.getLocalPort() != 0; }
        
        private:
            sf::TcpSocket socket;
    };
}

#endif // CLIENT_CLIENT_HPP
