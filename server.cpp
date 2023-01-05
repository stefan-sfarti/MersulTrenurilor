#include "server.h"

void Server::run() {
    setsockopt (this->lSocket, SOL_SOCKET, SO_REUSEADDR, & this->optValue, sizeof (this->optValue) );
    this->servAddrCfg.sin_addr.s_addr = htonl ( INADDR_ANY );
    this->servAddrCfg.sin_port = htons ( port );
    this->servAddrCfg.sin_family = AF_INET;

    bind ( this->lSocket, reinterpret_cast < sockaddr * > ( & this->servAddrCfg ), sizeof ( this->servAddrCfg ) );
    listen ( this->lSocket, 100 );

    while (true) {
        socklen_t clientAddrLen;

        int clientSock = accept ( this->lSocket, reinterpret_cast < sockaddr * > ( & this->servAddrCfg ), & clientAddrLen );
        auto arg = new Thread ( clientSock, this );

        pthread_t threadId;
        pthread_create ( & threadId, nullptr, & Thread :: threadLaunch, static_cast < void * > ( arg ) );
    }
}



int main () {
    Server s;
    s.run();
    return 0;
}
