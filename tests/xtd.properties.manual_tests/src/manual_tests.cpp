//{ Region header text.
#include <xtd/xtd.properties.hpp>
#include <iostream>
#include <string>
//}

template< class T >
struct type_identity {
  using type = T;
};

class Person {
public:
  property_<int> Age {
    get_ {return this->age;},
    set_ {this->age = value;}
  };
  
  property_<int> Age2 {32};
  
  property_<int, Person> Age3 {84};
  
  void SetAge3(int age3) {this->Age3 = age3;}
  
private:
  int age = 0;
};

int main() {
  Person p;
  std::cout << "p.Age = " << p.Age << std::endl;
  p.Age = 42;
  std::cout << "p.Age = " << p.Age << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "p.Age2 = " << p.Age2 << std::endl;
  p.Age2 = 24;
  std::cout << "p.Age2 = " << p.Age2 << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "p.Age3 = " << p.Age3 << std::endl;
  p.SetAge3(48);
  std::cout << "p.Age3 = " << p.Age3 << std::endl;
}
