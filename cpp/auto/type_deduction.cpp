/*
 * type_deduction.cpp
 *
 *  Created on: 10 Nov 2019
 *      Author: ahkad
 *
 *  auto type deduction works the same way as template deduction for most cases.
 *  Refer to type_deduction example in templates directory.
 *
 *  References:
 *  [1] Effective Modern C++ - Scott Meyers (Item 1-4)
 */

#include <iostream>
#include <vector>
#include <typeinfo> // for typeid(T).name()
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T>
void f(T& a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void g(T&& a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void h(T a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

int type_deduction(){

	int x1{0};
	const int x2{0};
	const int& x3{0};

	// Case 1
	std::cout<<"Case 1\n";
	auto& f1 = x1; std::cout<<"Type f1 is "<<type_id_with_cvr<decltype(f1)>().pretty_name()<<"\n";
	auto& f2 = x2; std::cout<<"Type f2 is "<<type_id_with_cvr<decltype(f2)>().pretty_name()<<"\n";
	auto& f3 = x3; std::cout<<"Type f3 is "<<type_id_with_cvr<decltype(f3)>().pretty_name()<<"\n";

	// Case 2
	std::cout<<"Case 2\n";
	auto&& g1 = x1; std::cout<<"Type g1 is "<<type_id_with_cvr<decltype(g1)>().pretty_name()<<"\n";
	auto&& g2 = x2; std::cout<<"Type g2 is "<<type_id_with_cvr<decltype(g2)>().pretty_name()<<"\n";
	auto&& g3 = x3; std::cout<<"Type g3 is "<<type_id_with_cvr<decltype(g3)>().pretty_name()<<"\n";
	auto&& g4 = 1;  std::cout<<"Type g4 is "<<type_id_with_cvr<decltype(g4)>().pretty_name()<<"\n";

	// Case 3
	std::cout<<"Case 3\n";
	auto h1 = x1; std::cout<<"Type h1 is "<<type_id_with_cvr<decltype(h1)>().pretty_name()<<"\n";
	auto h2 = x2; std::cout<<"Type h2 is "<<type_id_with_cvr<decltype(h2)>().pretty_name()<<"\n";
	auto h3 = x3; std::cout<<"Type h3 is "<<type_id_with_cvr<decltype(h3)>().pretty_name()<<"\n";
	auto h4 = 1;  std::cout<<"Type h4 is "<<type_id_with_cvr<decltype(h4)>().pretty_name()<<"\n";

	std::cout<<"**************************************************\n";

	int* y1 = &x1;
	const int* y2 = &x2;
	const int* const y3 = &x3;

	// Case 1
	std::cout<<"Case 1\n";
	auto& fp1 = y1; std::cout<<"Type fp1 is "<<type_id_with_cvr<decltype(fp1)>().pretty_name()<<"\n";
	auto& fp2 = y2; std::cout<<"Type fp2 is "<<type_id_with_cvr<decltype(fp2)>().pretty_name()<<"\n";
	auto& fp3 = y3; std::cout<<"Type fp3 is "<<type_id_with_cvr<decltype(fp3)>().pretty_name()<<"\n";

	// Case 2
	std::cout<<"Case 2\n";
	auto&& gp1 = y1; std::cout<<"Type gp1 is "<<type_id_with_cvr<decltype(gp1)>().pretty_name()<<"\n";
	auto&& gp2 = y2; std::cout<<"Type gp2 is "<<type_id_with_cvr<decltype(gp2)>().pretty_name()<<"\n";
	auto&& gp3 = y3; std::cout<<"Type gp3 is "<<type_id_with_cvr<decltype(gp3)>().pretty_name()<<"\n";

	// Case 3
	std::cout<<"Case 3\n";
	auto hp1 = y1; std::cout<<"Type hp1 is "<<type_id_with_cvr<decltype(hp1)>().pretty_name()<<"\n";
	auto hp2 = y2; std::cout<<"Type hp2 is "<<type_id_with_cvr<decltype(hp2)>().pretty_name()<<"\n";
	auto hp3 = y3; std::cout<<"Type hp3 is "<<type_id_with_cvr<decltype(hp3)>().pretty_name()<<"\n";

	std::cout<<"**************************************************\n";

	return 0;
}
