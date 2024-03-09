#include <iostream>
#include "protected_value.hpp"

struct Point
{
  double x = 0;
  double y = 0;
};
// To make it printable
std::ostream& operator<<(std::ostream& os, const Point& p)
{
  os << "[x:" << p.x << ", y:" << p.y << "]";
  return os;
}

int main()
{
  Protected<Point> point(Point{ 42, 69 });
  // result.get() uses a value semantic
  // (i.e., we make a copy of the object stored inside "point")
  std::cout << "access by value (copy) => " << point.get() << std::endl;

  if(auto val = point.getConstPtr())
  {
    // inside this scope, we are mutex protected (read only mutex)
    // and the value can be accessed directly through const reference
    std::cout << "access by const reference => " << (*val) << std::endl;
  }

  if(auto val = point.getMutablePtr())
  {
    // inside this scope, we are mutex protected (read-write mutex)
    // and the value can be accessed directly through reference.
    val->x = 68;
    std::cout << "access by non-const reference => " << *val << std::endl;
  }
  return 0;
}
