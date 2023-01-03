//
// Created by stefan on 02.01.2023.
//
#ifndef TRIAL_THREAD_H
#define TRIAL_THREAD_H

class Server;
class Thread {
private:
    int clientSocket;
    Server * pServer;

public:
    Thread ( int sock, Server * pServer ) : pServer (pServer), clientSocket (sock) {

    }

private:
    void run ();

public:
    static void * threadLaunch ( void * argument ) {

        auto pThread = static_cast < Thread * > ( argument );
        pThread->run ();


        delete pThread;
        return nullptr;
    }
};


#endif //TRIAL_THREAD_H
