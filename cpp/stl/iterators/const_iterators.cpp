/*
 * const_iterators.cpp
 *
 *  Created on: 16 Aug 2020
 *      Author: ahkad
 */

#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

int const_iterators(){

    std::vector<int> vec(10,7);
    const std::vector<int> cvec = vec;

    std::cout<<"Type = "<<type_id_with_cvr<decltype(vec.begin())>().pretty_name()<<"\n";
    std::cout<<"Type = "<<type_id_with_cvr<decltype(vec.cbegin())>().pretty_name()<<"\n";
    std::cout<<"Type = "<<type_id_with_cvr<decltype(cvec.begin())>().pretty_name()<<"\n";
    std::cout<<"Type = "<<type_id_with_cvr<decltype(cvec.cbegin())>().pretty_name()<<"\n";

    for(const auto& e:cvec) std::cout<<e<<" ";
    std::cout<<std::endl;

    return 0;
}



