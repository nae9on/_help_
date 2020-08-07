#include <QCoreApplication>
#include <iostream>
#include "boost/container/static_vector.hpp"

template <typename T, std::size_t N>
void PushBackPopWhenFull(boost::container::static_vector<T,N>& Vector, const T& ObjectToPush)
{
    if(Vector.size() == Vector.max_size())
    {
        std::copy(Vector.begin() + 1, Vector.end(), Vector.begin());
        Vector.back() = ObjectToPush;
    }
    else
    {
        Vector.push_back(ObjectToPush);
    }
}

template <typename T, std::size_t N>
void PushFrontPopWhenFull(boost::container::static_vector<T,N>& Vector, const T& ObjectToPush)
{
    if(Vector.size() == 0)
    {
        Vector.push_back(ObjectToPush);
    }
    else
    {
        T LastValue = Vector.back();

        std::copy_backward(Vector.begin(), Vector.end() - 1, Vector.end());
        Vector.front() = ObjectToPush;

        if(Vector.size() < Vector.max_size())
        {
            Vector.push_back(LastValue);
        }
    }
}

int static_vec()
{
    std::cout<<"Hello Qt\n\n";

    boost::container::static_vector<int,11> vec;
    PushBackPopWhenFull(vec,11);
    PushBackPopWhenFull(vec,12);
    PushBackPopWhenFull(vec,13);
    PushBackPopWhenFull(vec,14);
    PushBackPopWhenFull(vec,15);
    PushBackPopWhenFull(vec,16);
    //for(const auto& elem:vec) std::cout<<elem<<"\n";
    PushFrontPopWhenFull(vec,-1);
    PushFrontPopWhenFull(vec,-2);
    PushFrontPopWhenFull(vec,-3);
    PushFrontPopWhenFull(vec,-4);
    PushFrontPopWhenFull(vec,-5);
    PushFrontPopWhenFull(vec,-6);
    PushBackPopWhenFull(vec,100);
    for(const auto& elem:vec) std::cout<<elem<<"\n";

    std::cout<<"\nEnd\n";

    return 0;
}
