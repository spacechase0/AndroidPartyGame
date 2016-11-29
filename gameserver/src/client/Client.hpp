#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <type_traits>
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
            
            void update();
            
            bool connect();
            void disconnect();
            inline bool isConnected() const { return conn.socket.getLocalPort() != 0; }
            
            void send( const net::Packet* packet );
            template< typename T >
            typename std::enable_if< std::is_base_of< net::Packet, T >::value >::type
            send( const T& packet )
            {
                send( &packet );
            }
            
            std::function< void () > onStageChange;
            net::NetStage* getNetStage();
            const net::NetStage* getNetStage() const;
            void setNetStage( std::unique_ptr< net::NetStage > theStage );
        
        private:
            net::Connection conn;
            std::unique_ptr< net::NetStage > stage;
            std::unique_ptr< net::NetStage > pendingStage;
    };
}

#endif // CLIENT_CLIENT_HPP
