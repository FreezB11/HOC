#include "../lib/timer.hh"
#include "../lib/log.hh"
// #pragma once 
#define _XOPEN_SOURCE_EXTENDED 1
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
// for the basic fucntion of db
#include <iostream>
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>
#include <functional>
#include <fstream>

class doc{
    public:
        // support different datatypes
        using value = std::variant<int, double, std::string>;
        // to store key val pair for the data
        std::unordered_map<std::string, value> data;

        void insert(const std::string& key, value val);
        void fetch() const;
};

class collection{
    private:
        std::vector<doc> docx;
    public:
        void insert(const doc& _doc);
        void find(std::function<bool(const doc&)> condition) const;
        void update(std::function<bool(const doc&)> condition, const std::string& key, doc::value newValue);
        void remove(std::function<bool(const doc&)> condition);
        void save2file(const std::string& filename);
        void findAll() const;
};

// user side code 
namespace HOC{
    // database 
    /*
        insert()
        find()
        update()
        delete()
    */

    int _connect(std::string URI);
}

// server side
namespace HOC_S{
    extern int server_port;
    extern int server_s;
    extern sockaddr_in addr_s;
    int _listen();
}