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
    
    return 0;
}