#include <iostream>
#include <string>
#include <memory>
#define LOG(x) \
    std::cout << x << std::endl;

/// With smart pointers when you call new, you don't have to call delete
/// smart pointers are wrappers around new and delete
/// Unique pointer is a scoped pointer. When the pointers goes out of scope, it will be destroyed
/// can't copy a unique pointer

/// default visibility is private in class but public in struct
class entity
{
public:
    entity()
    {
        std::cout << "created entity" << std::endl;
    }

    void print()
    {
        std::cout << "print entity" << std::endl;
    }

    ~entity()
    {
        std::cout << "destroyed entity" << std::endl;
    }
};

int main()
{
    LOG("---------------");
    LOG("unique pointer");
    /// unique pointer
    {
        /// create a unique pointer: scoped unique ptr
        // std::unique_ptr<entity> ent(new entity());

        /// preferred way of creating unique pointer is. This is exception safety
        std::unique_ptr<entity> ent = std::make_unique<entity>();
        ent->print();

        /// can't copy unique pointer
        // std::unique_ptr<entity> e0 = ent;
    }

    LOG("---------------");
    LOG("shared pointer");
    /// shared pointer
    /// it uses reference counter. Keep track of how many reference you have to shared pointer
    /// when reference counter goes 0, shared pointer dies

    std::shared_ptr<entity> sptr = std::make_shared<entity>();
    /// we can copy shared pointer
    std::shared_ptr<entity> e1;
    e1 = sptr;
    e1->print();

    LOG("---------------");
    LOG("weak pointer");
    /// weak pointer
    /// when you copy shared pointer to weak pointer it won't increase ref count
    /// used to store just a reference to them. Useful when we don't want to take
    /// ownership of the pointer
    std::weak_ptr<entity> wptr = e1;

    return 0;
}