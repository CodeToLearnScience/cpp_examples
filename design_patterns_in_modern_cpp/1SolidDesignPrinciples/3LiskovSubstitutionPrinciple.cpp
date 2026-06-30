#include <iostream>

using namespace std;

class Rectangle {
protected:
  int width, height;

public:
  Rectangle(int width, int height) : width(width), height(height) {}
  [[nodiscard]] int getWidth() const { return width; }
  [[nodiscard]] int getHeight() const { return height; }
  virtual void setWidth(int w) { width = w; }
  virtual void setHeight(int h) { height = h; }
  [[nodiscard]] int getArea() const { return height * width; }
};

void process(Rectangle &r) {
  int w = r.getWidth();
  r.setHeight(10);
  cout << "Expected area: " << w * 10 << " got: " << r.getArea() << "\n";
}

// now lets say you want to inherit this Rectangle and create a Square class
class Square : public Rectangle {
protected:
  int size;

public:
  Square(int s) : Rectangle(s, s) {}
  void setWidth(int w) override { this->width = this->height = w; }
  void setHeight(int h) override { this->width = this->height = h; }
};

// one way to fix Liskov substitution
// The idea of Liskov substitution principle is that you should be able to
// substitute a derived class (here Square derived from Rectangle) into any
// location where a base class is being used (process method, where Rectangle
// base class is passed)
struct RectangleFactory {
  static Rectangle create_rectangle(int w, int h) { return Rectangle{w, h}; }
  static Rectangle create_square(int s) { return Square{s}; };
};

int main() {
  Rectangle r{3, 4};

  process(r);
  Square s{5};
  // now we can see we get different area and Liskov substitution principle
  // fails which says One solution would be to make a factory
  process(s);

  auto rr = RectangleFactory::create_rectangle(3, 4);
  process(rr);
  auto ss = RectangleFactory::create_square(5);
  process(ss);
}
