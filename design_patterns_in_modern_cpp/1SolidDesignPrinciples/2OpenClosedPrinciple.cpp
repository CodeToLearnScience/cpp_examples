#include <iostream>
#include <vector>

using namespace std;

namespace usual_approach {
enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
  string title;
  Color color;
  Size size;
};

struct ProductFilter {
  vector<Product *> by_color(const vector<Product *> &products, Color color) {

    vector<Product *> result;
    for (const auto &product : products) {

      if (product->color == color) {
        result.push_back(product);
      }
    }
    return result;
  }
  // if manages comes back to says add filter by size, then we will have to
  // modify this code as follows. But by open to extension and close to
  // modification principle, this is not right thing to do
  vector<Product *> by_size(const vector<Product *> &products, Color size) {

    vector<Product *> result;
    for (const auto &product : products) {

      if (product->color == size) {
        result.push_back(product);
      }
    }
    return result;
  }
};

void example() {

  // designated initializer list
  Product apple{.title = "Apple", .color = Color::red, .size = Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::green, Size::large};

  vector<Product *> products;
  products.push_back(&apple);
  products.push_back(&tree);
  products.push_back(&house);

  ProductFilter pf;
  auto res = pf.by_color(products, Color::green);
  for (const auto &product : res) {
    cout << product->title << "\n";
  }
}

} // namespace usual_approach

// open and close principle. Open for extension, close for modification. We use
// enterprise pattern which is also called specification pattern. Pattern
// related to data and working with data
namespace specification_pattern {

template <typename T> struct AndSpecification;

template <typename T> struct Specification {
  virtual bool is_specified(T *item) = 0;
  // since we had to declare lot of variables for AndSpecification, we can
  // declare custom operators
  AndSpecification<T> operator&&(Specification<T> &&other) {
    return AndSpecification<T>(*this, other);
  }
};

template <typename T> struct Filter {
  virtual vector<T *> filter(vector<T *> products, Specification<T> &spec) = 0;
};

// now implement filter
struct BetterFilter : Filter<usual_approach::Product> {

  vector<usual_approach::Product *> result;

  vector<usual_approach::Product *>
  filter(vector<usual_approach::Product *> items,
         Specification<usual_approach::Product> &spec) override {
    for (const auto &item : items) {
      if (spec.is_specified(item)) {
        result.push_back(item);
      }
    }
    return result;
  }
};

// implement color specification
struct ColorSpecification : Specification<usual_approach::Product> {
  usual_approach::Color color;
  ColorSpecification(usual_approach::Color color) : color(color) {}
  bool is_specified(usual_approach::Product *item) override {
    return item->color == color;
  }
};

// implement size specification
struct SizeSpecification : Specification<usual_approach::Product> {
  usual_approach::Size size;
  SizeSpecification(usual_approach::Size size) : size(size) {}
  bool is_specified(usual_approach::Product *item) override {
    return item->size == size;
  }
};
// implement combination of color and size
template <typename T> struct AndSpecification : Specification<T> {
  Specification<T> &first;
  Specification<T> &second;
  AndSpecification(Specification<T> &first, Specification<T> &second)
      : first(first), second(second) {}
  bool is_specified(T *item) override {
    return (first.is_specified(item) && second.is_specified(item));
  }
};

void example() {
  using namespace usual_approach;
  // designated initializer list
  Product lappy{.title = "Laptop", .color = Color::red, .size = Size::small};
  Product green_app{"Green Apple", Color::green, Size::large};
  Product hut{"Hut", Color::blue, Size::large};

  vector<Product *> products1;
  products1.push_back(&lappy);
  products1.push_back(&green_app);
  products1.push_back(&hut);

  cout << "Color specification:\n";
  BetterFilter bf;
  ColorSpecification cs(Color::green);
  auto res = bf.filter(products1, cs);
  for (const auto &product : res) {
    cout << product->title << "\n";
  }

  cout << "And specification\n";
  SizeSpecification large(Size::large);
  AndSpecification<Product> green_and_large(cs, large);
  auto res1 = bf.filter(products1, green_and_large);
  for (const auto &item : res1) {
    cout << item->title << " is green and large\n";
  }

  cout << "Using the AndSpecification operator&&\n";
  auto spec1 = ColorSpecification(Color::red) && SizeSpecification(Size::small);
  auto res2 = bf.filter(products1, spec1);
  for (const auto &item : res2) {
    cout << item->title << " is red and small\n";
  }
}

} // namespace specification_pattern

int main() {
  usual_approach::example();
  specification_pattern::example();
}
