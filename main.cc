#include "lib/log.hh"

int main(){
    io::log<ERROR>("this is fucked");
    io::log<DEBUG>("the debug test");

    io::log<INFO>("this is the test");
    io::log<WARN>("this is the test");
}

