#include <thread>
#include "common.h"
#include "DbCon.h"
#include "mysql/mysql.h"
#include "Thread.h"

class Server {

public:
    void run () {
        int lSocket = socket (AF_INET, SOCK_STREAM, 0);

        int optValue = 1;
        setsockopt ( lSocket, SOL_SOCKET, SO_REUSEADDR, & optValue, sizeof (optValue) );

        sockaddr_in servAddrCfg;
        servAddrCfg.sin_addr.s_addr = htonl ( INADDR_ANY );
        servAddrCfg.sin_port = htons ( port );
        servAddrCfg.sin_family = AF_INET;

        bind ( lSocket, reinterpret_cast < sockaddr * > ( & servAddrCfg ), sizeof ( servAddrCfg ) );
        listen ( lSocket, 100 );

        while (true) {
            socklen_t clientAddrLen;

            int clientSock = accept ( lSocket, reinterpret_cast < sockaddr * > ( & servAddrCfg ), & clientAddrLen );
            auto arg = new Thread ( clientSock, this );

            pthread_t threadId;
            pthread_create ( & threadId, nullptr, & Thread :: threadLaunch, static_cast < void * > ( arg ) );
        }
    }
};


int main () {

    Server s;
    s.run();
    return 0;
}
