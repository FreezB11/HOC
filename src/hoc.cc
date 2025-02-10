#include "hoc.hh"
#include <fstream>
#include <sstream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// -------------------- DATABASE SERVER IMPLEMENTATION -------------------- //

HOC::HOC(const std::string& filename) : filename(filename) {
    load_data();
}

void HOC::store(const std::string& id, const std::map<std::string, std::string>& data) {
    database[id] = data;
    save_data();
}

std::string HOC::fetch(const std::string& key) {
    std::ostringstream result;

    if (database.count(key)) {
        for (const auto& [field, value] : database[key]) {
            result << field << ":" << value << ",";
        }
        std::string output = result.str();
        return output.empty() ? "Not found" : output.substr(0, output.size() - 1);
    }

    for (const auto& [id, record] : database) {
        if (record.count(key)) {
            return "ID:" + id + "," + key + ":" + record.at(key);
        }
    }
    return "Key not found";
}

void HOC::update(const std::string& id, const std::map<std::string, std::string>& newData) {
    if (database.count(id)) {
        for (const auto& [key, value] : newData) {
            database[id][key] = value;
        }
        save_data();
    }
}

void HOC::delete_entry(const std::string& id) {
    database.erase(id);
    save_data();
}

void HOC::load_data() {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, pair, key, value;
        getline(iss, id, '|');

        std::map<std::string, std::string> record;
        while (getline(iss, pair, ',')) {
            std::istringstream pairStream(pair);
            getline(pairStream, key, ':');
            getline(pairStream, value);
            record[key] = value;
        }
        database[id] = record;
    }
}

void HOC::save_data() {
    std::ofstream file(filename);
    for (const auto& [id, record] : database) {
        file << id << "|";
        for (const auto& [key, value] : record) {
            file << key << ":" << value << ",";
        }
        file << "\n";
    }
}

void HOC::start_server(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int opt = 1;

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "HOC Database Server started on port " << port << "\n";

    while (true) {
        int client_fd = accept(server_fd, NULL, NULL);
        char buffer[1024] = {0};
        read(client_fd, buffer, 1024);
        std::istringstream ss(buffer);
        std::string command, key, value;
        ss >> command >> key;
        getline(ss, value);
        value.erase(0, value.find_first_not_of(" "));

        std::string response;
        if (command == "STORE") {
            store(key, {{"data", value}});
            response = "Stored\n";
        } else if (command == "FETCH") {
            response = fetch(key) + "\n";
        } else if (command == "UPDATE") {
            update(key, {{"data", value}});
            response = "Updated\n";
        } else if (command == "DELETE") {
            delete_entry(key);
            response = "Deleted\n";
        } else {
            response = "Invalid command\n";
        }

        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }
}

// -------------------- CLIENT IMPLEMENTATION -------------------- //

HOCClient::HOCClient(const std::string& host, int port) : host(host), port(port) {}

void HOCClient::store(const std::string& id, const std::string& data) {
    send_request("STORE " + id + " " + data);
}

std::string HOCClient::fetch(const std::string& key) {
    return send_request("FETCH " + key);
}

void HOCClient::update(const std::string& id, const std::string& data) {
    send_request("UPDATE " + id + " " + data);
}

void HOCClient::delete_entry(const std::string& id) {
    send_request("DELETE " + id);
}

std::string HOCClient::send_request(const std::string& message) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host.c_str());

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    send(sock, message.c_str(), message.size(), 0);

    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    close(sock);
    return std::string(buffer);
}
