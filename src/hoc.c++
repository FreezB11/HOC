#include "hoc.h++"
#include <bits/algorithmfwd.h>

int HOC_S::server_port = 3142;
int HOC_S::server_s = socket(AF_INET , SOCK_STREAM, 0);

sockaddr_in HOC_S::addr_s = {
            .sin_family = AF_INET,
            .sin_port = htons(server_port),
            .sin_addr = {
                .s_addr = INADDR_ANY
                },
};

void doc::insert(const std::string& key, value val){
    data[key] = val;
}

void doc::fetch() const{
    std::cout << "{";
    for(const auto&[key, val] : data){
        std::cout << key << ": ";
        std::visit([](const auto& v){std::cout << v;} , val);
        std::cout << ", ";
    }
    std::cout << "}\n";
}

void collection::insert(const doc& _doc){
    docx.push_back(_doc);
}

void collection::find(std::function<bool(const doc&)> condition) const{
    for(const auto& _doc: docx){
        if(condition(_doc)){
            _doc.fetch();
        }
    }
}

void collection::update(std::function<bool(const doc&)> condition, const std::string& key, doc::value newValue) {
    for (auto& doc : docx) {
        if (condition(doc)) {
            doc.insert(key, newValue);
        }
    }
}

void collection::remove(std::function<bool(const doc&)> condition){
    docx.erase(std::remove_if(docx.begin(), docx.end(), condition), docx.end());
}

void collection::save2file(const std::string& filename){
    std::ofstream file(filename);
    for (const auto& doc : docx) {
        file << "{ ";
        for (const auto& [key, value] : doc.data) {
            file << key << ": ";
            std::visit([&file](const auto& v) { file << v; }, value);
            file << ", ";
        }
        file << " }\n";
    }
    file.close();
}

void collection::findAll() const{
    for(const auto& doc: docx){
        doc.fetch();
    }
}


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