//client 
#include "./src/hoc.h++"
#include <iostream>
#include <string>
#include <sstream>

int main(){
    std::string URI = "hoc://hsay:yash0403@localhost:3142/<DB?_NAME>";
    // HOC::_connect(URI);
    std::string _parm[5];
    std::stringstream iss(URI);
    
    collection users;
    doc player1, player2;
    player1.insert("name", "alice");
    player1.insert("age",25);

    player2.insert("name", "yash");
    player2.insert("age", 30);

    users.insert(player1);
    users.insert(player2);

    io::log<INFO>("before update\n");
    users.findAll();

    users.update([](const doc& _doc){
        return std::get<int>(_doc.data.at("age")) == 25;
    }, "age", 26);
    io::log<INFO>("after update\n");

    users.findAll();

    users.save2file("db.txt");

    // users.remove([](const doc& _doc){
    //     return std::get<int>(_doc.data.at("age")) == 26;
    // });

    io::log<INFO>("after delete\n");
    users.findAll();

    return 0;
}