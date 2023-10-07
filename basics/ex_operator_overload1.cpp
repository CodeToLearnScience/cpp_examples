#include <iostream>
#include <string>

struct Vector2{

  float x, y;

  Vector2(float x, float y) 
    : x(x), y(y){}

  ///one way to add 
  Vector2 Add(const Vector2& other) const
  {
    return Vector2(x+other.x, y+other.y);
  }

  ///operator overloading
  Vector2 operator+(const Vector2& other) const
  {
    return Add(other);
    ///or
    ///return Vector2(x+other.x, y+other.y);

  }

  ///we can use above operator to write add 
  ///function another way
  Vector2 add(const Vector2& other) const
  {
    return *this + other;
  }

  ///we can use above operator to write add 
  ///one more way
  Vector2 Add2(const Vector2& other) const
  {
    return operator+(other);
  }

  ///boolean
  bool operator==(const Vector2& other) const
  {
    return x==other.x && y==other.y;
  }

 ///boolean negation
  bool operator!=(const Vector2& other) const
  {
    return !(*this==other);
    ///or
   /// return !operator==(other);
  }

};


std::ostream& operator<<(std::ostream& stream, const Vector2&  other)
{

  stream << other.x <<"," << other.y;

}

int main()
{

  Vector2 position(4.0f, 4.0f);
  Vector2 speed(0.5f, 1.5f);

  Vector2 result = position.Add(speed);
  
  Vector2 add = position+speed;
  
  std::cout<< add << "\n";
    
  return 0;
}
