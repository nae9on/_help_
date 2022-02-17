/*
 * transform.cpp
 *
 *  Created on: 17 Feb 2022
 *      Author: akadar
 */

#include "transform.h"

namespace algebra
{

namespace
{
auto identity = [](int a) { return a; };
}

transform::transform()
    : Distort(identity)
    , UnDistort(identity)
{}

transform::transform(op_type Distort_, op_type UnDistort_)
    : Distort(Distort_)
    , UnDistort(UnDistort_)
{}

point transform::GetDistortedPoint(const point& p)
{
    return point(Distort(p.x), Distort(p.y));
}

point transform::GetUnDistortedPoint(const point& p)
{
    return point(UnDistort(p.x), UnDistort(p.y));
}

// function template definition
std::ostream& operator<<(std::ostream& os, point p)
{
    return os << p.x << " " << p.y;
}
}
