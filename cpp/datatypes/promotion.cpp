/*
 * promotion.cpp
 *
 *  Created on: 22 Jul 2020
 *      Author: ahkad
 *
 * Ref: https://stackoverflow.com/questions/5563000/implicit-type-conversion-rules-in-c-operators
 */

#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

int promotion()
{
    /* Promotion rules from low precendence to high precedence
     * 1. long double (highest precedence)
     * 2. double
     * 3. float
     * 4. unsigned long long int
     * 5. long long int
     * 6. unsigned long int
     * 7. long int
     * 8. unsigned int
     * 9. signed int
     * 10. all others (lowest precedence)
     */

    // Examples
    unsigned int x{0};
    signed int y{-1};
    auto z = x+y; // Rule 8 - signed int gets promoted to unsigned int
    // Note: -Wconversion warning is not issued but -Wsign-conversion warning is issued
    std::cout<<"Type = "<<type_id_with_cvr<decltype(z)>().pretty_name()<<"\n";
    std::cout<<z<<std::endl;

    float xf{0.0f};
    // Rule 3 - signed int gets promoted to float
    // -Wconversion warning is issued because int and float are both 4 bytes and conversion
    // from large int's to float can result into loss of precision
    auto zf = xf+y;
    std::cout<<"Type = "<<type_id_with_cvr<decltype(zf)>().pretty_name()<<"\n";
    std::cout<<zf<<std::endl;

    double xd{0.0};
    // Rule 2 - float gets promoted to double
    auto zd = xd+xf;
    std::cout<<"Type = "<<type_id_with_cvr<decltype(zd)>().pretty_name()<<"\n";
    std::cout<<zd<<std::endl;
    return 0;
}


