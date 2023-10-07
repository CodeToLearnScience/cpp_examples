///pure virtual functions allows us to define a virtual
///function in a base class, which does not have implementations
///but forces sub-classes to have that implementations. Usefull
///to define interfaces
///interface is template class that does not implement details
///but just an interface for subclasses

#include <iostream>

class Entity{

  public:
   //pure virtual function
   virtual std::string get_name() = 0;
};

class Player : public Entity{
  public:
    Player(std::string name) : m_name(name){}

    std::string get_name() override{return m_name;}
  private:
    std::string m_name;
};

void print_name(Entity* entity)
{
  std::cout << entity->get_name() << "\n";

}

int main()
{

  ///We can't instantiate base class havig pure virtual function
  //Entity* e = new Entity();
  
  ///We can instantiate sub-class
  Entity *e = new Player("Volks");
    
  std::cout << e->get_name() << "\n";

  std::cout <<"---------------------------" << "\n";

  Player* p = new Player("Boeing");

  std::cout << p->get_name() << "\n";

  Entity* entity = p;
  std::cout << entity->get_name() << "\n";  

  print_name(e);
  print_name(p);

  return 0;
}
