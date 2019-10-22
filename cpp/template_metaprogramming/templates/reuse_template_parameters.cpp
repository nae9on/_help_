/*
 * reuse_template_parameters.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: akadar
 *
 *  Template parameters can be reused in the template parameter list.
 *  This example demonstrates that.
 */

#include <iostream>
#include <typeinfo>

// coordinates can be single-precision (float type) or double-precision (double type)
template<typename T = double> class coordinates{
public:
	using value_type = T;
	coordinates(){
		print_types();
	}
	void print_types(){
		std::cout<<"Coordinate class instantiated with type "<<typeid(T).name() <<"\n";
	}
private:
	T c1;
	T c2;
	T c3;
};

// velocity can be single-precision (float type) or double-precision (double type)
template<typename T = double> class velocity{
public:
	using value_type = T;
	velocity(){
		print_types();
	}
	void print_types(){
		std::cout<<"velocity class instantiated with type "<<typeid(T).name() <<"\n";
	}
private:
	T v1;
	T v2;
	T v3;
};

// pressure has the same value_type as velocity

// In the template definition below type V is re-used for defining the default type for P
template<typename C, typename V, typename P = typename V::value_type> class Acoustic{
public:
	Acoustic(const C& c_, const V& v_, const P& p_): coord{c_}, vel{v_}, pressure{p_} {
		print_types();
	}
	void print_types(){
		std::cout<<"Acoustic class instantiated with following types: \n";
		std::cout<<"Coordinates "<<typeid(C).name() <<"\n";
		std::cout<<"Velocity "<<typeid(V).name() <<"\n";
		std::cout<<"Pressure "<<typeid(P).name() <<"\n";
	}
private:
	C coord;
	V vel;
	P pressure;
};

int reuse_template_parameters(){

	// explicit type parameters provided
	coordinates<double> c1;
	velocity<double> v1;
	Acoustic<coordinates<double>,velocity<double>,double> a1(c1,v1,0.0);

	std::cout<<"\n\n\n";

	// default type parameters used (note <> is mandatory)
	coordinates<> c2;
	velocity<> v2;
	Acoustic<coordinates<double>,velocity<double>> a2(c2,v2,0.0);

	return 0;
}
