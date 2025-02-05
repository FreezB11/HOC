//client 
#include "./src/hoc.h++"

int main(){
    std::string URI = "hoc://hsay:yash0403@localhost:3142/<DB?_NAME>";
    HOC::_connect(URI);
}