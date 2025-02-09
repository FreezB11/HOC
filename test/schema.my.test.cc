#include <iostream>
#include <string>

template <typename T>
struct database{
    T schema;
};

template <typename T>
database<T>* addSchema(){

    database <T> *db;
    return db;
}

struct UserSchema{
    int id;
    int age;
    std::string name;
    std::string job_status;
};


int main(){
    UserSchema test = {
        .id = 43334,
        .age = 29,
        .name = "yash",
        .job_status = "employed",
    };
    database<UserSchema> *db = addSchema<UserSchema>();

    db->schema  = test;
    std::cout << db->schema.id;

}