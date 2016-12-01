#ifndef SERVER_CLIENTTRANSITION_HPP
#define SERVER_CLIENTTRANSITION_HPP

namespace server
{
    class ClientTransition
    {
        public:
            enum Type
            {
                None,
                Lobby,
                Match,
            };
            
            ClientTransition( Type type = None );
            
            Type type;
    };
}

#endif // SERVER_CLIENTTRANSITION_HPP
