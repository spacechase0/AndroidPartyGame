#ifndef NET_NETSTAGE_HPP
#define NET_NETSTAGE_HPP

#include <functional>
#include <map>
#include <memory>
#include <SFML/Config.hpp>

#include "net/Packet.hpp"

namespace net
{
    class Connection;
    
    class NetStage
    {
        public:
            enum Id : sf::Uint8
            {
                PreLogin,
                Lobby,
                Game,
            };
            typedef std::function< void ( const Packet* ) > PacketHandler;
            
            virtual ~NetStage();
            
            void update( Connection& conn );
            
            void addHandler( Packet::Id id, PacketHandler&& handler );
        
        protected:
            virtual std::unique_ptr< Packet > getPacketFromId( Packet::Id id ) const = 0;
            
        private:
            std::map< Packet::Id, PacketHandler > handlers;
            std::unique_ptr< Packet > pending;
            Packet::Length pendingLen;
    };
}

#endif // NET_NETSTAGE_HPP
