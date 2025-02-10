#include "src/hoc.hh"

int main() {
    HOC database("data.txt");
    database.start_server(8080);
    return 0;
}
