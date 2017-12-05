#include <properties/properties.hpp>
#include <iostream>
#include <string>

using namespace properties;

class person {
public:
  person() = default;
  
  // Must be specified because the copy contructor of property class is deleted.
  // The implicit or default copy constructor is not suffisant.
  person(const person& pers) : name_(pers.name_), age_(pers.age_) {}
  
  person& operator=(const person& pers) = default;
  
  // Declare a name property of type std::string:
  property<std::string> name {
    property_get {return this->name_;},
    property_set {this->name_ = value;}
  };
  
  // Declare an age property of type int:
  property<int> age {
    property_get {return this->age_;},
    property_set {this->age_ = value;}
  };
  
  friend std::ostream& operator<<(std::ostream& os, const person& pers) {return os << "name = " << pers.name << ", age = " << pers.age;}
  
private:
  std::string name_ = "N/A";
  int age_ = 0;
};

int main(int argc, char* argv[]) {
  std::cout << "Simple Properties" << std::endl;
  
  // Create a new Person object:
  person pers;
  
  // Print out the name and the age associated with the pers:
  std::cout << "person details - " << pers << std::endl;
  
  // Set some values on the pers object:
  pers.name = "Joe";
  pers.age = 99;
  std::cout << "person details - " << pers << std::endl;
  
  // Increment the Age property:
  pers.age += 1;
  std::cout << "person details - " << pers << std::endl;
}

// This code produces the following output :
//
// Simple Properties
// person details - name = N/A, age = 0
// person details - name = Joe, age = 99
// person details - name = Joe, age = 100
