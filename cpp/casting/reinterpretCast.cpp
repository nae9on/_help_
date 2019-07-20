/*
 * reinterpretCast.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: akadar
 */

// References
// [1] https://docs.microsoft.com/en-us/cpp/cpp/reinterpret-cast-operator?view=vs-2019

#include <iostream>

int main_reinterpret(){

	/* Allows any pointer to be converted into any other pointer type.
	 * However, it cannot cast away const.
	 * It is the most unsafe cast, and should be used only when the desired
	 * conversion is inherently low-level.
	 * The result of a reinterpret_cast cannot safely be used for
	 * anything other than being cast back to its original type.
	 *
	 */

	// A practical use of reinterpret_cast is in a hash function (refer to [1])

	return 0;
}


