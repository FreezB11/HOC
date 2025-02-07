    #include "../lib/timer.hh"
    #include "../lib/log.hh"
    // #pragma once 

    #define _XOPEN_SOURCE_EXTENDED 1
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <fcntl.h>


    // user side code 
    namespace HOC{

        int _connect(std::string URI);
        /*
            add()
            append() / store()
            update()
            lookup()

        */

    }

    // server side
    namespace HOC_S{

        extern int server_port;
        extern int server_s;
        extern sockaddr_in addr_s;
        int _listen();
    }