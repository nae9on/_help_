/*
 * reuse_template_parameters.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: akadar
 *
 *  Template parameters can be reused in the template parameter list.
 */

#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

// coordinates can be single-precision (i.e. float) or double-precision
template<typename T = double> class coordinates{
public:
	using value_type = T;
	coordinates(){
		print_types();
	}
	void print_types(){
		std::cout<<"coordinates class instantiated with type \""
				<<type_id_with_cvr<T>().pretty_name() <<"\"\n";
	}
private:
	T c1;
	T c2;
	T c3;
};

// velocity can be single-precision (i.e. float) or double-precision
template<typename T = float> class velocity{
public:
	using value_type = T;
	velocity(){
		print_types();
	}
	void print_types(){
		std::cout<<"velocity class instantiated with type \""
				<<type_id_with_cvr<T>().pretty_name() <<"\"\n";
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
		std::cout<<"Coordinates \""<<type_id_with_cvr<C>().pretty_name() <<"\"\n";
		std::cout<<"Velocity \""<<type_id_with_cvr<V>().pretty_name() <<"\"\n";
		std::cout<<"Pressure \""<<type_id_with_cvr<P>().pretty_name() <<"\"\n";
	}
private:
	C coord;
	V vel;
	P pressure;
};

int reuse_template_parameters(){

	// explicit type parameters provided
	coordinates<double> c1;
	velocity<float> v1;
	Acoustic<coordinates<double>,velocity<float>,float> a1(c1,v1,0.0);

	std::cout<<"\n";

	// default type parameters used (note <> is mandatory)
	coordinates<> c2;
	velocity<> v2;
	Acoustic<coordinates<double>,velocity<float>> a2(c2,v2,0.0);

	return 0;
}
