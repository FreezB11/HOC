#include <iostream>
#include <unordered_map>
#include <any>
#include <string>
#include <typeindex>
#include <typeinfo>

// Generic Database Class
class Database {
private:
    std::unordered_map<std::type_index, std::string> schemaRegistry;
    std::unordered_map<std::string, std::any> objectStore;

public:
    // Register a schema
    template <typename T>
    void addSchema(const std::string& schemaName) {
        schemaRegistry[std::type_index(typeid(T))] = schemaName;
        std::cout << "Schema registered: " << schemaName << std::endl;
    }

    // Store an object (only if schema exists)
    template <typename T>
    void storeObject(const std::string& id, const T& obj) {
        if (schemaRegistry.find(std::type_index(typeid(T))) == schemaRegistry.end()) {
            std::cerr << "Error: Schema for this type is not registered!" << std::endl;
            return;
        }
        objectStore[id] = obj;
        std::cout << "Stored object with ID: " << id << std::endl;
    }

    // Retrieve an object (only if schema exists)
    template <typename T>
    T* callByObj(const std::string& id) {
        if (objectStore.find(id) != objectStore.end()) {
            return std::any_cast<T>(&objectStore[id]);
        }
        return nullptr; // Not found
    }
};

// Example User-Defined Structs
struct User {
    std::string name;
    int age;
    void print() const { std::cout << "User: " << name << ", Age: " << age << std::endl; }
};

struct Product {
    std::string name;
    double price;
    void print() const { std::cout << "Product: " << name << ", Price: " << price << std::endl; }
};

int main() {
    Database db;

    // Register schemas
    db.addSchema<User>("UserSchema");
    db.addSchema<Product>("ProductSchema");

    // Store objects
    User user1 = {"Alice", 25};
    Product product1 = {"Laptop", 999.99};

    db.storeObject<User>("user_1", user1);
    db.storeObject("prod_1", product1);

    // Retrieve and Print User
    User* foundUser = db.callByObj<User>("user_1");
    if (foundUser) foundUser->print();
    else std::cout << "User not found" << std::endl;

    // Retrieve and Print Product
    Product* foundProduct = db.callByObj<Product>("prod_1");
    if (foundProduct) foundProduct->print();
    else std::cout << "Product not found" << std::endl;

    return 0;
}
