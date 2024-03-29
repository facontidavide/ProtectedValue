# ProtectedValue

Simple wrapper to make the access to
a specific value mutex protected.

In addition to the naive "setters and getters" that you may expect,
it provides a RAII interface that simplifies
accessing the object by reference, in a thread-safe way.

## Example

Let's use this custom type, to make the example more interesting.

```cpp
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
```

This is the way the wrapper can be used to access the object in a
thread-safe way:

```cpp
Protected<Point> point(Point{ 1, 2 });

// set() and get() use value semantic, this means that a copy is being made.
point.set(Point{ 42, 69 });
std::cout << "access by value (copy) => " << point.get() << std::endl;

if(auto val = point.getConstPtr())
{
  // inside this scope, we are mutex protected (read-only mutex)
  // and the value can be accessed directly through const reference
  std::cout << "access by const reference => " << (*val) << std::endl;
}

if(auto val = point.getMutablePtr())
{
  // inside this scope, we are mutex protected (read-write mutex)
  // and the value can be accessed directly through reference.
  val->x = 68;
  std::cout << "access by non-const reference => " << (*val) << std::endl;
}
```

The expected output on the console is:

```
access by value (copy) => [x:42, y:69]
access by const reference => [x:42, y:69]
access by non-const reference => [x:68, y:69]
```
