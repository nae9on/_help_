#include "header.h"
#include "utility.h"

namespace algebra
{

template<typename T>
double slope(point<T> p)
{
    return p.y/p.x;
}

template double slope(point<float> p);

}
