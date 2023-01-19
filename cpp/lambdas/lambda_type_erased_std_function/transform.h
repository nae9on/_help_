/*
 * transform.h
 *
 *  Created on: 17 Feb 2022
 *      Author: akadar
 */

#pragma once

#include <functional>
#include <ostream>

namespace algebra
{

struct point
{
    point() = default;
    point(int x_, int y_)
        : x{x_}
        , y{y_}
    {}
    int x{};
    int y{};
};

class transform{
public:
    using op_type = std::function<point(point)>;
    transform();
    transform(op_type, op_type);
    point GetDistortedPoint(const point& p);
    point GetUnDistortedPoint(const point& p);
private:
    op_type Distort;
    op_type UnDistort;
};

std::ostream& operator<<(std::ostream& os, point p);
}
