#ifndef NET_NETSTAGE_HPP
#define NET_NETSTAGE_HPP

#include <functional>
#include <map>
#include <memory>
#include <SFML/Config.hpp>
#include <type_traits>

#include "net/Packet.hpp"

namespace net
{
    class Connection;
    
    class NetStage
    {
        public:
            typedef std::function< void ( const Packet* ) > PacketHandler;
            
            NetStage( Connection& theConn );
            virtual ~NetStage();
            
            void update();
            
            void addHandler( Packet::Id id, PacketHandler&& handler );
            
            void send( const Packet* packet );
            template< typename T >
            typename std::enable_if< std::is_base_of< net::Packet, T >::value >::type
            send( const T& packet )
            {
                send( &packet );
            }
        
        protected:
            Connection& conn;
            
            virtual std::unique_ptr< Packet > getPacketFromId( Packet::Id id ) const = 0;
        
        private:
            std::map< Packet::Id, PacketHandler > handlers;
            std::unique_ptr< Packet > pending;
            Packet::Length pendingLen;
    };
}

#endif // NET_NETSTAGE_HPP
