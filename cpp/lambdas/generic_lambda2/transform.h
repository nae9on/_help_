/*
 * transform.h
 *
 *  Created on: 17 Feb 2022
 *      Author: akadar
 */

#pragma once

#include <ostream>
#include <functional>

namespace algebra
{

template <typename T>
struct point
{
    point() = default;
    point(T x_, T y_)
        : x{x_}
        , y{y_}
        {}
    T x{};
    T y{};
};

//namespace
//{
//auto identity = [](point<int> a) { return a; };
//}

template <typename T>
auto get_identity_lambda()
{
    return [](point<T> a) { return a; };
}

template <typename T>
class transform{
public:
    using op_type = std::function<point<T>(point<T>)>;
    transform()
        : Distort(get_identity_lambda<T>())
        , UnDistort(get_identity_lambda<T>())
    {}
    transform(op_type Distort_, op_type UnDistort_)
        : Distort(Distort_)
        , UnDistort(UnDistort_)
    {}
    point<T> GetDistortedPoint(const point<T>& p)
    {
        return point<T>(Distort(p));
    }
    point<T> GetUnDistortedPoint(const point<T>& p)
    {
        return point<T>(UnDistort(p));
    }
private:
    op_type Distort;
    op_type UnDistort;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, point<T> p)
{
    return os << p.x << " " << p.y;
}
}
