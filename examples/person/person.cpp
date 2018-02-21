#include <properties/properties.hpp>
#include <iostream>
#include <string>

class Person {
public:
  Person() = default;

  // Must be specified because the copy contructor of property_ class is deleted.
  // The implicit or default copy constructor is not suffisant.
  Person(const Person& person) : name(person.name), age(person.age) {}

  Person& operator=(const Person& person) = default;

  // Declare a Name property of type std::string:
  property_<std::string> Name {
    get_ {return this->name;},
    set_ {this->name = value;}
  };

  // Declare an Age property of type int:
  property_<int> Age {
    get_ {return this->age;},
    set_ {this->age = value;}
  };

  friend std::ostream& operator<<(std::ostream& os, const Person& person) {return os << "Name = " << person.Name << ", Age = " << person.Age;}

private:
  std::string name = "N/A";
  int age = 0;
};

int main(int argc, char* argv[]) {
  std::cout << "Simple Properties" << std::endl;

  // Create a new Person object:
  Person person;

  // Print out the Name and the Age associated with the person:
  std::cout << "Person details - " << person << std::endl;

  // Set some values on the person object:
  person.Name = "Joe";
  person.Age = 99;
  std::cout << "Person details - " << person << std::endl;

  // Increment the Age property:
  person.Age += 1;
  std::cout << "Person details - " << person << std::endl;
}

// This code produces the following output :
//
// Simple Properties
// Person details - Name = N/A, Age = 0
// Person details - Name = Joe, Age = 99
// Person details - Name = Joe, Age = 100
