/*
 * float2binary.cpp
 *
 *  Created on: 17 Apr 2020
 *      Author: ahkad
 */

#include <iostream>
#include "myutils.h"

int float2binary(){

	// Convert a float to its bit sequence in memory
	/*
	 * 1. Convert the integral part to its bit sequence
	 * 2. Convert the fractional part to its bit sequence
	 * 3. Concatenate them i.e. integral bit sequence on left, decimal in between and
	 * fractional bit sequence on right
	 * 4. Shift right the integral bit sequence by N digits such that the final bit
	 * sequence is of the form 0___0001.xxxx___. Note the value of N. Keep only 23 rightmost
	 * bits after the right of the decimal point and discard the remaining
	 * 5. Convert the integer N+127 to its bit sequence
	 * 6. Now concatenate the sign bit(0 or 1), 8 right most bits from the bit sequence
	 * from step 5 and 23 bits after the decimal point from step 4
	 */
	outbits<signed>(2048); // step 1
	frac2bits(0.127f); // step 2
	// 0000 0000 0000 0000 0000 1000 0000 0000.00100000100000110001001 // step 3
	// 1.000 0000 0000 001000001000 // step 4, N = 11
	outbits<signed>(138); // step 5
	// 0 10001010 00000000000001000001000 // step 6
	out<float>(2048.127f); // reference

	std::cout<<"\n";

	// When representing integers, a floating-point type has a lower precision than an integral type
	out<float>(static_cast<float>(std::pow(2,24)-1));
	out<float>(static_cast<float>(std::pow(2,24)+0));
	out<float>(static_cast<float>(std::pow(2,24)+1));

	std::cout<<"\n";

	// Example (for decimals in [0,2) there is loss of precision after 7th decimal place)
	out<float>(1.1234566f);
	out<float>(1.1234567f);
	out<float>(1.1234568f);

	out<float>(1.12345676f);
	out<float>(1.12345677f);
	out<float>(1.12345678f);

	std::cout<<"\n";

	// Example (for decimals in [2,4) there is loss of precision after 6th decimal place)
	out<float>(2.123456f);
	out<float>(2.123457f);
	out<float>(2.123458f);

	out<float>(2.1234566f);
	out<float>(2.1234567f);
	out<float>(2.1234568f);

	std::cout<<"\n";

	// Example (for decimals in [2048,4096) there is loss of precision after 3rd decimal place)
	out<float>(2048.127f);
	out<float>(2048.128f);
	out<float>(2048.129f);
	out<float>(2048.1237f);
	out<float>(2048.1238f);
	out<float>(2048.1239f);

	return 0;

}
