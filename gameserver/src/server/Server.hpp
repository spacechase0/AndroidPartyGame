#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <list>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
#include <util/Logger.hpp>

namespace server
{
    class Client;
    class Match;
    
    class Server
    {
        public:
            Server();
            ~Server();
            
            util::Logger log;
            
            void run();
            void stop();
            inline bool isRunning() const { return running; }
        
        private:
            bool running = true;
            
            sf::Mutex clientsM;
            std::list< std::unique_ptr< Client > > clients;
            
            std::list< Match > matches;
            
            sf::Thread listenerThread;
            sf::TcpListener listener;
            void listen();
    };
}

#endif // SERVER_SERVER_HPP
