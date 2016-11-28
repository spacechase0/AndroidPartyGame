#include "server/Client.hpp"

#include "net/Connection.hpp"
#include "net/NetStage.hpp"

namespace server
{
    Client::Client( Server& theServer )
    :   server( theServer )
    {
        // Set default netstage
    }
    
    Client::~Client()
    {
    }
}
