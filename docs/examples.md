| [Home](home.md) | [Downloads](downloads.md) | [Examples](examples.md) | [Documentation](documentation.md) | [Sources](https://github.com/gammasoft71/delegates) | [Project](https://sourceforge.net/projects/delegates/) | [Gammasoft](https://gammasoft71.wixsite.com/gammasoft) | [Contact](contact.md) | [Website](https://gammasoft71.wixsite.com/properties) |

# Example

person.cpp:

```c++
#include "properties.hpp"
#include <iostream>
#include <string>

class Person {
public:
  Person() = default;

  // Must be specified because the copy contructor of property class is deleted.
  // The implicit or default copy constructor is not sufficient.
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

int main() {
  std::cout << "Simple Properties" << std::endl;
    
  // Create a new Person object:
  Person person;
  
  // Print out the name and the age associated with the pers:
  std::cout << "Person details - " << person << std::endl;

  // Set some values on the pers object:
  person.Name = "Joe";
  person.Age = 99;
  std::cout << "Person details - " << person << std::endl;

  // Increment the Age property:
  person.Age += 1;
  std::cout << "Person details - " << person << std::endl;
}
```

Output:

```
Simple Properties
Person details - Name = N/A, Age = 0
Person details - Name = Joe, Age = 99
Person details - Name = Joe, Age = 100
```

[Click here to see more examples](../examples)

______________________________________________________________________________________________

© 2021 Gammasoft.
