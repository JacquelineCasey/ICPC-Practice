

#include <unordered_map>
#include <map>
#include <functional>
#include <iostream>

struct Person {
public:
    std::string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    friend bool operator<(const Person& left, const Person& right) {
        return left.name < right.name;
    }
};


template<>
struct std::hash<Person> {
    std::size_t operator()(const Person& p) const {
       return std::hash<std::string>()(p.name);
    }
};


int main() {
    std::unordered_map<Person,int> unordered_map {};

    std::map<Person, int> map {};
    
    Person p1;
    p1.name = "Jacqueline";
    p1.age = 21;

    Person p2;
    p2.name = "Hank";
    p2.age = 40;

    
    map.insert({p2, 1234});
    map.insert({p1, 3333});

   unordered_map[p2] = 123;
   unordered_map[p1] = 1234;
     
    std::cout << "Hello, structures created\n";
    return 0;
}
