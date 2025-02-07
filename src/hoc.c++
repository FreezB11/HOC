#include "hoc.h++"

int HOC_S::server_port = 3142;
int HOC_S::server_s = socket(AF_INET , SOCK_STREAM, 0);

sockaddr_in HOC_S::addr_s = {
            .sin_family = AF_INET,
            .sin_port = htons(server_port),
            .sin_addr = {
                .s_addr = INADDR_ANY
                },
};


//              "hoc://hsay:yash0403@localhost:3142/<DB?_NAME>"
int HOC::_connect(std::string URI){

    /*
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(TEMP_port);
    */
    //(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr))
    // int status_code = connect();
    return 0;
}

int HOC_S::_listen(){

    return 0;
}