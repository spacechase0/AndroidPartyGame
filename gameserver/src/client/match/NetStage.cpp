#include "client/match/NetStage.hpp"

#include "client/Client.hpp"
#include "net/match/Packets.hpp"
#include "net/PacketId.hpp"

namespace client
{
    namespace match
    {
        using namespace net;
        using namespace net::match;
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn, const game::MatchData& theMatch )
        :   net::match::NetStage( theConn ),
            client( theClient ),
            matchInfo( theMatch ),
            match( theClient, ( * this ) )
        {
            using namespace std::placeholders;
            
            // Can't set this in Match constructor since this would still be constructing
            onMatchStartData = [ this ](){ match.cachedBoard = false; };
            onDiceRoll = [ this ]( sf::Uint8 num ){ match.onDiceRoll( num ); };
            
            addHandler( PacketId::MatchStartData, std::bind( &NetStage::handleMatchStartData, this, _1 ) );
            addHandler( PacketId::DiceRoll      , std::bind( &NetStage::handleDiceRoll      , this, _1 ) );
        }
        
        void NetStage::rollDie()
        {
            client.send( DiceRollPacket() );
        }
        
        void NetStage::handleMatchStartData( const net::Packet* packet )
        {
            auto data = static_cast< const MatchStartDataPacket* >( packet );
            
            client.log( "[INFO] Got match start data.\n" );
            map = data->map;
            players = data->players;
            for ( unsigned int i = 0; i < players.size(); ++i )
            {
                if ( players[ i ].username == client.user )
                {
                    match.myTurn = i;
                    break;
                }
            }
            
            if ( onMatchStartData )
                onMatchStartData();
        }
        
        void NetStage::handleDiceRoll( const net::Packet* packet )
        {
            auto roll = static_cast< const DiceRollPacket* >( packet );
            
            client.log( "[INFO] Got dice roll: $\n", static_cast< int >( roll->num ) );
            
            if ( onDiceRoll )
                onDiceRoll( roll-> num );
        }
    }
}
