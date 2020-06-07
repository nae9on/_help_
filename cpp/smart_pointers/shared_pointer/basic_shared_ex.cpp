/*
 * basic_shared_ex.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: akadar
 */

#include <iostream>
#include <memory>
#include <boost/type_index.hpp>

class Y{
public:
    Y():data{0}{++count; std::cout<<"ctor called\n";};
    Y(int data_):data{data_}{++count; std::cout<<"ctor called for data = "<<data_<<"\n";}
    Y(const Y& x){
        data = x.data;
    }
    void outData()const{std::cout<<"output data = "<<data<<"\n";}
    static int getCount(){return count;}
    ~Y(){--count; std::cout<<"dtor called for data = "<<data<<"\n";}
private:
    int data;
    static int count;
};

int Y::count = 0;

void showcount(const std::shared_ptr<Y>& sptr){
    std::cout<<"Use count = "<<sptr.use_count()<<"\n";
}

int basic_shared_ex(){

    // ways to initialize shared_ptr's
    {
        // 1. not recommended
        Y* yptr = new Y(12);
        std::shared_ptr<Y> sptr(yptr);
        //std::shared_ptr<Y> sptr2(yptr); // disaster

        // 2. recommended
        auto sptr2{std::make_shared<Y>(34)}; // Note requires c++14 support

        // 3. ok
        std::shared_ptr<Y> sptr3(new Y(56));

        // 4. also ok
        std::shared_ptr<Y> sptr4(nullptr); // Note: it is set to nullptr when not initialized
        //sptr4 = new Y(78); // Error Implicit conversion from raw pointer to shared_ptr is not allowed
        sptr4.reset(new Y(78));
        std::cout<<"End of block\n";
    }

    std::cout<<"***************************\n";

    // using shared pointer for shared ownership
    {
        auto sptr{std::make_shared<Y>(10)};

        // Note size of std::shared_ptr is = size of two pointers (one for
        // the internal raw pointer and the other for the control block)
        std::cout<<boost::typeindex::type_id_with_cvr<decltype(sptr)>()<<"\n";
        std::cout<<"Size of shared_ptr = "<<sizeof(decltype(sptr))<<"\n";

        // each resoure has its own unique control block which keeps count of the
        // number of owners of that resource
        showcount(sptr); // counter = 1

        std::shared_ptr<Y> sptr_copy1(sptr); // OK, shared ownership, counter = 2
        showcount(sptr); // counter = 2, same as showcount(sptr_copy1);

        std::shared_ptr<Y> sptr_copy2; // owns nullptr
        sptr_copy2 = sptr; // OK, shared ownership
        showcount(sptr); // counter = 3

        sptr_copy2.reset();
        showcount(sptr); // counter = 2

        sptr_copy1.reset();
        showcount(sptr); // counter = 1

        sptr.reset();
        showcount(sptr); // counter = 0
        std::cout<<"End of block\n";
    }

    std::cout<<"***************************\n";

    // move semantics
    {
        std::shared_ptr<Y> sptr1(new Y(33)), sptr2(new Y(99)), sptr3;

        sptr1 = sptr3; // Y(33) not owned by anyone and therefore destroyed
        //showcount(sptr1); showcount(sptr2); showcount(sptr3);

        sptr3 = sptr2; // ownership  of Y(99) shared
        //sptr3 = std::move(sptr2); // ownership  of Y(99) transferred
        showcount(sptr1); showcount(sptr2); showcount(sptr3);

        std::cout<<"End of block\n";
    }

    std::cout<<"***************************\n";

	std::cout<<"End main\n";
	return 0;
}
