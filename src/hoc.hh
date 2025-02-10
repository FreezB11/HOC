#ifndef HOC_HH
#define HOC_HH

#include <iostream>
#include <string>
#include <map>
#include <vector>

// server -> database
class HOC {
public:
    HOC(const std::string& filename);
    void store(const std::string& id, const std::map<std::string, std::string>& data);
    std::string fetch(const std::string& key);
    void update(const std::string& id, const std::map<std::string, std::string>& newData);
    void delete_entry(const std::string& id);
    void start_server(int port);

private:
    std::string filename;
    std::map<std::string, std::map<std::string, std::string>> database;
    void load_data();
    void save_data();
};

//client
class HOCClient {
public:
    HOCClient(const std::string& host, int port);
    void store(const std::string& id, const std::string& data);
    std::string fetch(const std::string& key);
    void update(const std::string& id, const std::string& data);
    void delete_entry(const std::string& id);

private:
    std::string host;
    int port;
    std::string send_request(const std::string& message);
};

#endif
