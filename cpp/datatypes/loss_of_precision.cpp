/*
 * loss_of_precision.cpp
 *
 *  Created on: 23 Jul 2020
 *      Author: ahkad
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

// From FLIR
template<class T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
AlmostEqual(const T a, const T b,  const T epsilon = 1.0e-06)
{
    std::cout<<"Deduced type = "<<type_id_with_cvr<T>().pretty_name()<<"\n";

    constexpr T minPrecision = 0.1;

    if (std::isnan(a) || std::isnan(b) || std::isinf(a) || std::isinf(b))
    {
        std::cout<<std::fixed<<std::setprecision(15)
        <<a<<" and/or "<<b<<" are nan and/or inf\n";
        return false;
    }
    T difference = std::fabs(a-b);

    if (difference <= epsilon)
    {
        std::cout<<std::fixed<<std::setprecision(15)
        <<a<<" and "<<b<<" are almost equal in absolute sense\n";
        return true;
    }
    // We do not want to compare big numbers,
    // especially when then have no mantissa.
    if (difference > minPrecision)
    {
        std::cout<<std::fixed<<std::setprecision(15)
        <<a<<" and "<<b<<" are two big to be compared\n";
        return false;
    }
    T largest = std::max(std::fabs(a), std::fabs(b));
    T rangeRelDiff = epsilon * largest;

    bool check = difference <= rangeRelDiff;

    if(check)
        std::cout<<std::fixed<<std::setprecision(15)
        <<a<<" and "<<b<<" are almost equal in relative sense\n";
    else
        std::cout<<std::fixed<<std::setprecision(15)
        <<a<<" and "<<b<<" are not equal in relative sense\n";

    return check;
}

int loss_of_precision()
{
    // possible loss of precision when int is converted to float
    int i{16777217};
    float f = i;
    std::cout<<std::fixed<<std::setprecision(15)<<f<<"\n";

    // possible loss of precision when int is added to float
    int x{16777216};
    float y{1.0f};
    std::cout<<std::fixed<<std::setprecision(15)<<x+y<<"\n";

    // possible loss of precision when two floats are added
    float f1{16777216.0f};
    float f2{3.5f};
    std::cout<<std::fixed<<std::setprecision(15)<<f1+f2<<"\n";

    // Rule of thumb 7 digits should be same for almost equal to be true

    AlmostEqual(1.123456f,1.123456f);

    AlmostEqual(1.123456f,1.123458f);

    AlmostEqual(1123.456f,1123.458f);

    AlmostEqual(1.123456f,1.123457f); // note are almost equal!

    AlmostEqual(1123.456f,1123.457f); // note are almost equal!

    std::cout<<"end of main"<<std::endl;

    return 0;
}


