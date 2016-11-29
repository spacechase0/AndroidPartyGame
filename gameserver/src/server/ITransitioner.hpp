#ifndef SERVER_ITRANSITIONER_HPP
#define SERVER_ITRANSITIONER_HPP

#include "server/ClientTransition.hpp"

namespace server
{
    class ITransitioner
    {
        public:
            virtual ~ITransitioner();
            
            virtual ClientTransition getTransition() const = 0;
    };
}

#endif // SERVER_ITRANSITIONER_HPP
