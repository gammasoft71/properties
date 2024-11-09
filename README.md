# properties

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

### For more information see
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
#include <xtd/properties>
#include <iostream>
#include <string>

class person {
public:
  person() noexcept = default;
  person(person &&) noexcept = default;

  // Must be specified because the copy contructor of property class is deleted.
  // The implicit or default copy constructor is not sufficient.
  person(const person& other) noexcept : name_(other.name_), age_(other.age_) {}

  person& operator=(person&&) noexcept = default;
  person& operator=(const person&) noexcept = default;
  
  // Declare a name property of type std::string:
  property_<std::string> name {
    get_ {return name_;},
    set_ {name_ = value;}
  };
  
  // Declare an age property of type int:
  property_<int> age {
    get_ {return age_;},
    set_ {age_ = value;}
  };
  
  friend std::ostream& operator<<(std::ostream& os, const person& value) {return os << "[name = " << value.name << ", age = " << value.age << "]";}
   
private:
  std::string name_ = "N/A";
  int age_ = 0;
};

int main(int argc, char* argv[]) {
  std::cout << "Simple Properties" << std::endl;
    
  // Create a new person object:
  person p;
  
  // Print out the name and the age associated with the pers:
  std::cout << "person details - " << p << std::endl;

  // Set some values on the pers object:
  p.name = "Joe";
  p.age = 99;
  std::cout << "person details - " << p << std::endl;

  // Increment the age property:
  p.age += 1;
  std::cout << "person details - " << p << std::endl;
}
```

Console output:

```
Simple Properties
person details - [name = N/A, age = 0]
person details - [name = Joe, age = 99]
person details - [name = Joe, age = 100]
```

## Getting Started

* [Installation](docs/downloads.md) provides download and install documentation.
* [Portability](docs/portability.md) provides information about C++, libraries dependency, Operating System suported, Compilators and Devepment Environment tools.
* [Examples](docs/examples.md) provides some examples.

______________________________________________________________________________________________

© 2021 Gammasoft.
