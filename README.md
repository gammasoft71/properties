#properties

**another c#-like property accessor for C++11 and above.**

[![properties](docs/pictures/properties_header.png)](https://gammasoft71.wixsite.com/properties)

## Continuous Integration build status

| Operating system | Status                                                                                                                                               |
|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|
| Windows          | [![Build status](https://ci.appveyor.com/api/projects/status/r3w9ojjiecp4vf8f?svg=true)](https://ci.appveyor.com/project/gammasoft71/xtd-properties) |
| macOS            | [![Build Status](https://travis-ci.org/gammasoft71/xtd_properties.svg?branch=master)](https://travis-ci.org/gammasoft71/xtd_properties)              |
| Linux            | [![Build Status](https://travis-ci.org/gammasoft71/xtd_properties.svg?branch=master)](https://travis-ci.org/gammasoft71/xtd_properties)              |

## Download the latest stable tunit version

[![Download properties](https://img.shields.io/sourceforge/dt/properties.svg)](https://sourceforge.net/projects/properties/files/latest/download)

## Features

* **properties** add c#-like property accessor to your c++ class.
* **properties** is distributed as a single header file.

## What is it ?

A property is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.

For more information see:
* [website](https://gammasoft71.wixsite.com/properties) 
* [markdown documentations](docs/home.md)
* [sources](https://github.com/gammasoft71/properties)
* [Reference Guide](https://codedocs.xyz/gammasoft71/properties/)
* [Try it online](https://wandbox.org/permlink/aA17kJZXhJOYsTpW)

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

Console output:

```
Simple Properties
Person details - Name = N/A, Age = 0
Person details - Name = Joe, Age = 99
Person details - Name = Joe, Age = 100
```

## Getting Started

* [Installation](docs/downloads.md) provides download and install documentation.
* [Portability](docs/portability.md) provides information about C++, libraries dependency, Operating System suported, Compilators and Devepment Environment tools.
* [Examples](docs/examples.md) provides some examples.

______________________________________________________________________________________________

© 2021 Gammasoft.
