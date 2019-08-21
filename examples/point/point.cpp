#include <xtd/xtd.properties>
#include <iostream>
#include <string>

class point {
public:
  point() = default;
  point(int x, int y) : x_(x), y_(y) {}

  // Must be specified because the copy contructor of property_ class is deleted.
  // The implicit or default copy constructor is not sufficient.
  point(const point& point) : x_(point.x_), y_(point.y_) {}

  point& operator=(const point& point) = default;

  // Declare a X property of type int:
  property_<int, readonly_> x {
    get_ {return this->x_;}
  };

  // Declare a Y property of type int:
  property_<int, readonly_> y {
    get_ {return this->y_;}
  };

  friend std::ostream& operator<<(std::ostream& os, const point& point) {return os << "[X = " << point.x << ", Y = " << point.y << "]";}

private:
  int x_ = 0;
  int y_ = 0;
};

int main(int argc, char* argv[]) {
  point p1 {12, 24};
  std::cout << "p1 = " << p1 << std::endl;

  point p2 = p1;
  std::cout << "p2.X = " << p2.x << std::endl;
  std::cout << "p2.Y = " << p2.y << std::endl;

}

// This code produces the following output :
//
// p1 = [X = 12, Y = 24]
// p2.X = 12
// p2.Y = 24
