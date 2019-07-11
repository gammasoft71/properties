#include <xtd/xtd.properties>
#include <iostream>
#include <string>

class Point {
public:
  Point() = default;
  Point(int X, int Y) : x(X), y(Y) {}

  // Must be specified because the copy contructor of property_ class is deleted.
  // The implicit or default copy constructor is not sufficient.
  Point(const Point& point) : x(point.x), y(point.y) {}

  Point& operator=(const Point& point) = default;

  // Declare a X property of type int:
  property_<int, readonly_> X {
    get_ {return this->x;}
  };

  // Declare a Y property of type int:
  property_<int, readonly_> Y {
    get_ {return this->y;}
  };

  friend std::ostream& operator<<(std::ostream& os, const Point& point) {return os << "[X = " << point.X << ", Y = " << point.Y << "]";}

private:
  int x = 0;
  int y = 0;
};

int main(int argc, char* argv[]) {
  Point p1 {12, 24};
  std::cout << "p1 = " << p1 << std::endl;

  Point p2 = p1;
  std::cout << "p2.X = " << p2.X << std::endl;
  std::cout << "p2.Y = " << p2.Y << std::endl;

}

// This code produces the following output :
//
// p1 = [X = 12, Y = 24]
// p2.X = 12
// p2.Y = 24
