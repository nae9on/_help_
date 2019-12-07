/*
 * lambdas_and_scope_rules.cpp
 *
 *  Created on: 24 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int invalid_global = 1;

/*
 * diracDelta class has a member function which returns a closure (anonymous function object).
 * This closure can be used to test if an integer is valid or invalid.
 */
class diracDelta{
public:
	diracDelta(int invalid_):invalid{invalid_}{}

	std::function<bool(int)> get_direc(){

		int invalid_local = this->invalid;

		/*
		 * Note: only local variables are captured by a lambda
		 * static variables and global variables are not captured.
		 *
		 * &invalid_local would be a disaster since invalid_local has local scope.
		 *
		 * What happens when this* is captured instead of invalid_local in the capture-clause?
		 * The result is unpredictable.
		 *
		 */
		auto lb = [invalid_local](const int& x){

			if (x == valid)	return true;

			if (x == invalid_local || x == invalid_global)
				return false;
			else
				return true;

		};

		return lb;
	}

	static int valid;

private:
	int invalid;
};

int diracDelta::valid = 2;

int lambdas_and_scope_rules(){

	std::function<bool(int)> lb;
	{
		diracDelta dl(3);
		lb = dl.get_direc();
	}

	std::vector<int> test_data{1,2,3,4,5,6,7,8,9,10};
	std::for_each(test_data.cbegin(),test_data.cend(),
			[lb](const int& elem){if(lb(elem)) std::cout<<elem<<"\n";});

	return 0;
}
