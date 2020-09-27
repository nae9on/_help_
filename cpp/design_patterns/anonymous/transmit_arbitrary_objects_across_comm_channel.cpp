/*
 * This example illustrates a blueprint for the "receiver end" of a system for transmitting
 * arbitrary objects across a communication channel in a type-safe manner. More generally, these
 * techniques can be used to invoke a function based on a string supplied by a user
 * and to manipulate objects of unknown type through interfaces discovered through RTTI.
 *
 * Reference: Page 649, 22.2.4 The C++ Programming Language - Bjarne Stroustrup
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>

// ----------------------------------------------------------------------------
// shape interface class
class shape
{
public:
    virtual std::string getname() const = 0;
    virtual void draw() const = 0;
    virtual ~shape() = default;
};
// standard shapes implementing shape interface class
class circle: public shape
{
public:
    std::string getname() const override { return name; }
    void draw() const override { std::cout<<name<<"\n"; }
private:
    std::string name{"circle"};
};

class square: public shape
{
public:
    std::string getname() const override { return name; }
    void draw() const override { std::cout<<name<<"\n"; }
private:
    std::string name{"square"};
};

class triangle: public shape
{
public:
    std::string getname() const override { return name; }
    void draw() const override { std::cout<<name<<"\n"; }
private:
    std::string name{"triangle"};
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// all entities (shapes, colors etc) that allow I/O should implement io_obj
class io_obj
{
public:
    virtual ~io_obj() = default;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// extended shapes which extend standard shapes and implementing io_obj
/*
 * This is an example of how a concrete class (standard_shape) can be fitted into a
 * class hierarchy using an abstract class (io_obj)
 */
template<typename standard_shape>
class extended_shape: public standard_shape, public io_obj
{
public:
    extended_shape() = default;
    static io_obj* new_io() { return new extended_shape{}; }
};

using extended_circle = extended_shape<circle>;
using extended_square = extended_shape<square>;
using extended_triangle = extended_shape<triangle>;
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
using ptr2f = io_obj*(*)(); // pointer to function returning io_obj*
std::map<std::string, ptr2f> entities_map;
io_obj* get_obj(const std::string& str)
{
    if(entities_map.find(str)!=entities_map.cend())
    {
        auto func = entities_map[str];
        return func();
    }
    return nullptr;
}
// ----------------------------------------------------------------------------

int main()
{
    entities_map.emplace("circle", &extended_circle::new_io);
    entities_map.emplace("square", &extended_square::new_io);
    entities_map.emplace("triangle", &extended_triangle::new_io);

    // Read objects from a file etc
    std::vector<std::string> entities_in_file{"square","circle","red","green","triangle"};

    for(const auto& str : entities_in_file)
    {
        std::unique_ptr<io_obj> uptr{get_obj(str)};
        if(auto sp = dynamic_cast<shape*>(uptr.get()))
        {
            sp->draw();
        }
        else
        {
            std::cout<<str<<" is not a shape\n";
        }
    }

    return 0;
}
