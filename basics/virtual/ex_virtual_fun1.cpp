///virtual functions allow you to override methods in sub-classes
///If we don't use virtual functions, we will run into problem 
///with polymorphism

///virtual functions dispatch something called dynamic dispatch
///however there is some overhead. But for most applications it doesn't matter
#include <iostream>

class Entity{

  public:
   virtual std::string get_name(){return "Entity";}
   //std::string get_name(){return "Entity";}
};

class Player : public Entity{
  public:
    Player(std::string name) : m_name(name){}

    std::string get_name() override{return m_name;}
   // std::string get_name() {return m_name;}
  private:
    std::string m_name;
};

void print_name(Entity* entity)
{
  std::cout << entity->get_name() << "\n";

}

int main()
{

  ///All will be fine with this usage without virtual functions
  Entity* e = new Entity();
  
  std::cout << e->get_name() << "\n";

  std::cout <<"---------------------------" << "\n";

  Player* p = new Player("Boeing");

  std::cout << p->get_name() << "\n";

  //////////////////////////////////////////////////////////
  ///here is the problem if we don't use virtual functions
  Entity* entity = p;
  ///if we don't use virtual functions this will print Entity instead of Boeing
  std::cout << entity->get_name() << "\n";  

  ///if we don't use virtual functions, both will print entity
  print_name(e);
  print_name(p);

  return 0;
}
