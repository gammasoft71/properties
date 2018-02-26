[![properties picture](docs/pictures/properties-banner.png)](https://gammasoft71.wixsite.com/properties)
____________________________________________________________________________________

[![build status](https://travis-ci.org/gammasoft71/properties.svg)](https://travis-ci.org/gammasoft71/properties) 
[![Build status](https://ci.appveyor.com/api/projects/status/v7q0cn0kocokvpoa?svg=true)](https://ci.appveyor.com/project/gammasoft71/properties)
[![Documentation](https://img.shields.io/badge/code-documented-brightgreen.svg)](https://gammasoft71.github.io/properties-doc) 
[![codecov](https://codecov.io/gh/yfiumefreddo/properties/branch/master/graph/badge.svg)](https://codecov.io/gh/gammasoft71/properties)
[![Website](https://img.shields.io/website-up-down-green-red/http/shields.io.svg?label=properties%20website)](https://gammasoft71.wixsite.com/properties)
[![license](https://img.shields.io/github/license/gammasoft71/Switch.svg)](License.md)
[![GitHub top language](https://img.shields.io/github/languages/top/gammasoft71/properties.svg)](https://cppreference.com)
[![SourceForge Download properties](https://img.shields.io/sourceforge/dt/properties.svg)](https://sourceforge.net/projects/properties/files/latest/download)
![os Windows](https://img.shields.io/badge/os-Windows-004080.svg)
![os macOS](https://img.shields.io/badge/os-macOS-004080.svg)
![os Linux](https://img.shields.io/badge/os-Linux-004080.svg)
![os iOS](https://img.shields.io/badge/os-iOS-004080.svg)
![os android](https://img.shields.io/badge/os-android-004080.svg)
[![Try online](https://img.shields.io/badge/try-online-004080.svg)](https://wandbox.org/permlink/aA17kJZXhJOYsTpW)

# properties

* **properties** add c#-like property accessor to your c++ class.
* **properties** is distributed as a single header file.
* **properties** is a small part of [Switch](https://github.com/gammasoft71/Switch)

## What is it ?

A property is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.

## There are three types of properties :

### readwrite :

The property accessor can be read and write.

```c++
class Foo {
public:
  //...
  
  property_<int> Number {
    get_ {return this->number;},
    set_ {this->number = value;}
  };
  
  //...
  
private:
  int number = 0;
};
```

### readonly :

The property accessor can be read only.

```c++
class Foo {
public:
  //...
  
  property_<int, readonly_> Number {
    get_ {return this->number;}
  };
  
  //...
  
private:
  int number = 0;
};
```

### writeonly :

The property accessor can be write only.

```c++
class Foo {
public:
  //...
  
  property_<int, writeonly_> Number {
    set_ {this->number = value;}
  };
  
  //...
  
private:
  int number = 0;
};
```

## Read and write properties full example

person.cpp:

```c++
#include <properties/properties.hpp>
#include <iostream>
#include <string>

using namespace properties;

class Person {
public:
  Person() = default;

  // Must be specified because the copy contructor of property class is deleted.
  // The implicit or default copy constructor is not suffisant.
  Person(const Person& person) : name(person.name), age(person.age) {}

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

CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.2)

project(person)
find_package(properties REQUIRED)
add_executable(person person.cpp)
target_link_libraries(person properties)
```

Console output:

```
Simple Properties
Person details - Name = N/A, Age = 0
Person details - Name = Joe, Age = 99
Person details - Name = Joe, Age = 100
```
You can try and play this example [here](https://wandbox.org/permlink/aA17kJZXhJOYsTpW).

For more examples see [examples](examples).

See the online [Reference guide](https://gammasoft71.github.io/properties-doc/).
