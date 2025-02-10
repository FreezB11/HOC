#include "src/hoc.hh"

int main() {
    HOCClient client("127.0.0.1", 8080);

    client.store("1", "name:Yashraj,age:20,city:Mumbai");
    std::cout << "Stored data.\n";

    std::cout << "Fetched: " << client.fetch("1") << "\n";
    std::cout << "Fetch by Name: " << client.fetch("name") << "\n";

    return 0;
}
