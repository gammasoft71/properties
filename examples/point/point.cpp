#include <properties/properties.hpp>
#include <iostream>
#include <string>

using namespace properties;

class point {
public:
  point() = default;
  point(int x, int y) : x_(x), y_(y) {}
  
  // Must be specified because the copy contructor of property class is deleted.
  // The implicit or default copy constructor is not suffisant.
  point(const point& p) : x_(p.x_), y_(p.y_) {}
  
  point& operator=(const point& p) = default;
  
  // Declare a x property of type int:
  property<int, readonly> x {
    property_get {return this->x_;}
  };
  
  // Declare a x property of type int:
  property<int, readonly> y {
    property_get {return this->y_;}
  };
  
  friend std::ostream& operator<<(std::ostream& os, const point& p) {return os << "[x = " << p.x << ", y = " << p.y << "]";}
  
private:
  int x_ = 0;
  int y_ = 0;
};

int main(int argc, char* argv[]) {
  point p1 {12, 24};
  std::cout << "p1 = " << p1 << std::endl;
  
  point p2 = p1;
  std::cout << "p2.x = " << p2.x << std::endl;
  std::cout << "p2.y = " << p2.y << std::endl;
  
}

// This code produces the following output :
//
// p1 = [x = 12, y = 24]
// p2.x = 12
// p2.y = 24
