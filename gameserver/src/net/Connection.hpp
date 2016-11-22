#ifndef NET_CONNECTION_HPP
#define NET_CONNECTION_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <sstream>
#include <stdexcept>

namespace server { class Server; }
namespace client { class Client; }

namespace net
{
    class Connection
    {
        public:
            void update(); // Call when data is available (SocketSelector)
            
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
            
            /// TODO SEND
        
        private:
            sf::TcpSocket socket;
            std::stringstream buffer;
            std::size_t currBufferSize = 0;
            
            friend class server::Server;
            friend class client::Client;
    };
}

#endif // NET_CONNECTION_HPP
