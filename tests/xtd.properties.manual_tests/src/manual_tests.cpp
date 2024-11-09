#include <xtd/properties>
#include <iostream>
#include <string>

class person {
public:
  property_<int> age {
    get_ {return age_;},
    set_ {age_ = value;}
  };
  
  property_<int> age2 {32};
  
  property_<int, person> age3 {84};
  
  void set_age3(int age) {age3 = age;}
  
private:
  int age_ = 0;
};

int main() {
  person p;
  std::cout << "p.age = " << p.age << std::endl;
  p.age = 42;
  std::cout << "p.age = " << p.age << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "p.age2 = " << p.age2 << std::endl;
  p.age2 = 24;
  std::cout << "p.age2 = " << p.age2 << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "p.age3 = " << p.age3 << std::endl;
  p.set_age3(48);
  std::cout << "p.age3 = " << p.age3 << std::endl;
}
