![properties picture](docs/pictures/properties.png)
[![build status](https://travis-ci.org/gammasoft71/properties.svg)](https://travis-ci.org/gammasoft71/properties) 
[![Build status](https://ci.appveyor.com/api/projects/status/v7q0cn0kocokvpoa?svg=true)](https://ci.appveyor.com/project/gammasoft71/properties)
[![codecov](https://codecov.io/gh/yfiumefreddo/properties/branch/master/graph/badge.svg)](https://codecov.io/gh/gammasoft71/properties)
[![license GPL v3](https://img.shields.io/badge/license-GPL%20v3-004080.svg)](LICENSE.md) 
[![© GAMMA Soft](https://img.shields.io/badge/©-GAMMA%20Soft-004080.svg)](https://gammasoft71.wixsite.com/gammasoft) 
[![std c++14](https://img.shields.io/badge/std-c++14-004080.svg)](https://cppreference.com) 
[![os Windows, macOS, linux](https://img.shields.io/badge/os-Windows,%20macOS,%20linux-004080.svg)](.)
[![Try online](https://img.shields.io/badge/try-online-004080.svg)](https://wandbox.org/permlink/vAG6uvDfTeYS8M4z)

# properties

* **properties** add c#-like property accessor to your c++ class.
* **properties** is distributed as a single header file.

## What is it ?

A property is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.

## There are three types of properties :

### readwrite :

The property accessor can be read and write.

```c++
class foo {
public:
  ...
  
  property<int> number {
    property_get {return this->number_;},
    property_set {this->number_ = value;}
  };
  
  ...
  
private:
  int number_ = 0;
};
```

### readonly :

The property accessor can be read only.

```c++
class foo {
public:
  ...
  
  property<int, readonly> number {
    property_get {return this->number_;}
  };
  
  ...
  
private:
  int number_ = 0;
};
```

### writeonly :

The property accessor can be write only.

```c++
class foo {
public:
  ...
  
  property<int, writeonly> number {
    property_set {this->number_ = value;}
  };
  
  ...
  
private:
  int number_ = 0;
};
```

## Read and write properties full example

person.cpp:

```c++
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
person details - name = N/A, age = 0
person details - name = Joe, age = 99
person details - name = Joe, age = 100
```
You can try and play this example [here](https://wandbox.org/permlink/vAG6uvDfTeYS8M4z).

For more examples see [examples](examples).

See the online [Reference guide](https://gammasoft71.github.io/properties-doc/).


