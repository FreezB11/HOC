    #include "../lib/timer.hh"
    #include "../lib/log.h"
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

        int server_port = 3142;
        int server_s = socket(AF_INET , SOCK_STREAM, 0);

        sockaddr_in addr_s = {
            .sin_family = AF_INET,
            .sin_port = htons(server_port),
            .sin_addr = {
                .s_addr = INADDR_ANY
                },
        };
        int _listen();
    }