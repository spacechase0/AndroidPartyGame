#ifndef NET_CONNECTION_HPP
#define NET_CONNECTION_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <sstream>
#include <stdexcept>

namespace server { class Server; }
namespace client { class Client; }

namespace net
{
    class Packet;
    
    class Connection
    {
        public:
            void update();
            
            inline bool isConnected() { return socket.getLocalPort() == 0; }
            
            std::size_t available() const;
            std::size_t read( void* data, std::size_t amount );
            template< typename T >
            T readValue()
            {
                if ( available() < sizeof( T ) )
                    throw std::underflow_error( "Not enough data in buffer." );
                
                T t;
                read( &t, sizeof( T ) );
                return t;
            }
            
            void write( void* data, std::size_t amount );
            
            // I don't feel like this belongs here since reading packets is in NetStage
            // But it's kinda clunky in NetStage as well. :/
            void write( const Packet* packet );
        
        private:
            sf::TcpSocket socket;
            std::stringstream recvBuffer;
            std::size_t recvBufferSize = 0;
            std::string sendBuffer;
            
            friend class server::Server;
            friend class client::Client;
    };
}

#endif // NET_CONNECTION_HPP
