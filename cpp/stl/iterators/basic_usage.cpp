/*
 * basic_usage.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: ahkad
 *
 * Iterator is a concept.
 * All iterator classes are derived from the std::iterator base class
 *
 * References:
 * https://en.cppreference.com/w/cpp/iterator
 * http://www.cplusplus.com/reference/iterator/
 *
 */

#include <iostream>
#include <vector>
#include <list>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>

using vectype = std::list<int>;

int basic_usage(){

    /*
     * InputIterator -
     * 1. can read (one or multiple times the same value) from the pointed-to element
     * 2. can be both pre- and post-incremented
     * 3. allows only single pass (i.e. once incremented, all copies of its previous value
     * may be invalidated, refer to the stack-overflow post "What is a Single Pass Algorithm").
     */

    // Example istream_iterator an input iterator that reads from std::basic_istream
    // They are constructed from a basic_istream object, to which they become associated,
    // so that whenever operator++ is used on the iterator, it extracts an element from
    // the stream (using operator>>).
    std::ifstream ifs("data.txt");
    std::istream_iterator<char> start(ifs);
    std::istream_iterator<char> stop;

    std::cout<<*start<<"\n"; ++start;
    std::cout<<*start<<"\n"; //++start;
    std::cout<<*start<<"\n"; start++;
    std::cout<<*start<<"\n"; ++start;
    if(start==stop) std::cout<<"End of file reached\n";

    //--start; // Error, operator-- not defined
    //start=start+1; // Error, operator+ for int not defined


    /*
     * OutputIterator -
     * 1. can write to the pointed-to element
     * 2. can be both pre- and post-incremented
     * 3. allows only single pass (i.e. once incremented, all copies of its previous value may be invalidated).
     */

    // Example ostream_iterator an output iterator that writes to std::basic_ostream
    // They are constructed from a basic_ostream object, to which they become associated,
    // so that whenever an assignment operator (=) is used on the ostream_iterator (dereferenced or not)
    // it inserts a new element into the stream.

    std::ostream_iterator<int> ofs(std::cout,"\n");
    *ofs = 1; // Note pre/post increment is not needed
    ofs = 2; // Note the difference
    *ofs = 3;

    //--ofs; // Error, operator-- not defined
    //ofs=ofs+1; // Error, operator+ for int not defined

    // Combined example
    std::ifstream ifs2("data.txt");
    std::copy(std::istream_iterator<char>(ifs2),
                      std::istream_iterator<char>(),
                      std::ostream_iterator<char>(std::cout, " "));

    return 0;
}


