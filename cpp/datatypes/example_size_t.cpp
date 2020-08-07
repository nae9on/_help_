/*
 * example_size_t.cpp
 *
 *  Created on: Oct 19, 2019
 *      Author: akadar
 *
 * What for and why size_t?
 * 1. size_t is a typedef for one of the fundamental unsigned integer types. It could be unsigned int,
 * unsigned long, or unsigned long long or another unsigned type depending on the implementation.
 * 2. size_t is the type returned by the sizeof operator.
 * 3. It can represent the size of any object in bytes (example a gigantic static array of 4 GB).
 * 4. It is widely used in the standard library for array indexing and loop counting.
 * 5. Programs that use other types, such as unsigned int, for array indexing may fail on, e.g.
 * 64-bit systems when the index exceeds UINT_MAX.
 * 6. For containers, size_type is usually defined as std::size_t.
 *
 * References:
 * https://en.cppreference.com/w/cpp/types/size_t
 * Check your stack overflow post.
 *
 * Hex to decimal
 * https://www.rapidtables.com/convert/number/hex-to-decimal.html
 *
 */

#include <iostream>
#include <vector>
#include <climits>

int example_size_t(){

	// Signed types
	std::cout<<"Char min/max "<<CHAR_MIN<<" "<<CHAR_MAX<<"\n";
	std::cout<<"Int min/max "<<INT_MIN<<" "<<INT_MAX<<"\n";
	std::cout<<"Long min/max "<<LONG_MIN<<" "<<LONG_MAX<<"\n";

	// Unsigned types
	std::cout<<"UChar max "<<UCHAR_MAX<<"\n";
	std::cout<<"UInt max "<<UINT_MAX<<"\n";
	std::cout<<"ULong max "<<ULONG_MAX<<"\n";

	std::cout<<"Size of std::size_t is = "<<sizeof(std::size_t)<<" bytes\n";

	std::vector<char> vec(2*UINT_MAX,0);
	for(unsigned int i = 0; i<2*UINT_MAX; ++i) vec[i] = 'a'; // Problematic

	unsigned int i = UINT_MAX+1; std::cout<<i<<"\n";

	return 0;
}
