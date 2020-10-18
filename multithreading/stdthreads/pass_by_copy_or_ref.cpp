#include <thread>

#include <iostream>
#include <functional>

struct X
{
    int x{1};
};

void Print1(X Obj)
{
    std::cout<<"In Print1 "<<Obj.x<<std::endl;
    Obj.x = 100;
}

void Print2(X& Obj)
{
    std::cout<<"In Print2 "<<Obj.x<<std::endl;
    Obj.x = 100;
}

int main()
{
    /*
     * In below, std::ref is a type function from <functional> needed to tell the std::thread
     * variadic template ctor to treat Obj as a reference otherwise it will be passed by value.
     */

    X Obj;
    std::thread Thread1{Print1, Obj}; // OK pass by copy
    //std::thread Thread1{Print1, std::ref(Obj)}; // OK pass by copy
    //std::thread Thread2{Print2, Obj}; // Error
    std::thread Thread2{Print2, std::ref(Obj)}; // OK pass by reference
    Thread1.join();
    Thread2.join();
    std::cout<<"In main "<<Obj.x<<std::endl;
    std::cout<<"End of main"<<std::endl;
    return 0;
}
