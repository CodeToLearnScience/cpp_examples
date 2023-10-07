///pure virtual functions allows us to define a virtual
///function in a base class, which does not have implementations
///but forces sub-classes to have that implementations. Usefull
///to define interfaces
///interface is template class that does not implement details
///but just an interface for subclasses

#include <iostream>


class Printable
{
  public:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable
{
  public:
    std::string GetClassName() override {return "Entity";}
};

class Player : public Entity
{
  public:
    Player(std::string name) : m_name(name) {}
    std::string GetClassName() override {return "Player";}

  private:
    std::string m_name;
};

void Print(Printable* obj)
{
  std::cout << obj->GetClassName() << "\n";

}

int main()
{

  Entity* e = new Entity();

  Player* p = new Player("Sachin");

  Print(e);
  Print(p);

  return 0;
}
