/*
 * side_effect_scott37.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: akadar
 */

#include <iostream>
#include <numeric> // std::accumulate (also for inner_prouct, adjacent_difference, partial_sum)
#include <vector>
#include <algorithm> // std::for_each

struct point{
	point(){
		x = 0;
		y = 0;
	}
	point(double x_, double y_){
		x = x_;
		y = y_;
	}
	friend point operator+(const point& p1, const point& p2){
		return point(p1.x+p2.x,p1.y+p2.y);
	}
	friend point operator/(const point& p1, const size_t& n){
		return point(p1.x/n,p1.y/n);
	}
	double x;
	double y;
};

/*
 * According to Scott#36, std::accumulate forbids side effects in the function object
 * passed  (i.e modification of the member variables of the passed functor is not allowed).
 * However, it seems to work pretty well here! Why?
 */
template<typename _Tp, typename value_type>
class avg_obj{
public:
	avg_obj(){
		sum = 0;
		n = 0;
	}
	void operator()(const value_type& y){ // required only for for_each
		++n;
		sum = sum + y; // adapt here for a different functionality
	}
	_Tp operator()(const _Tp& x, const value_type& y){
		++n;
		sum = sum + y; // adapt here for a different functionality
		return sum/n;
	}
	_Tp result() const{ // required only for for_each
		return sum/n;
	}
private:
	_Tp sum;
	size_t n;
};

template<>
class avg_obj<double, std::string>{
public:
	avg_obj(){
		sum = 0;
		n = 0;
	}
	void operator()(const std::string& y){
		++n;
		sum = sum + y.size();
	}
	double operator()(const double& x, const std::string& y){
		++n;
		sum = sum + y.size();
		return sum/n;
	}
	double result() const{
		return sum/n;
	}
private:
	double sum;
	size_t n;
};

template<>
class avg_obj<point, point>{
public:
	avg_obj(){
		sum = point(0,0);
		n = 0;
	}
	void operator()(const point& y){
		++n;
		sum = sum + y;
	}
	point operator()(const point& x, const point& y){
		++n;
		sum = sum + y;
		return sum/n;
	}
	point result() const{
		return sum/n;
	}
private:
	point sum;
	size_t n;
};

int side_effect_scott37(){

	std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
	double average_vec{std::accumulate(vec.cbegin(),vec.cend(),0.0,avg_obj<double,int>())};
	std::cout<<"Average = "<<average_vec<<"\n";

	std::vector<std::string> ss{"lets","begin","our","journey"};
	double avergae_str_length{std::accumulate(ss.cbegin(),ss.cend(),0.0,avg_obj<double,std::string>())};
	std::cout<<"Average string length = "<<avergae_str_length<<"\n";

	std::vector<point> pp{point(1,1),point(2.6,2.6),point(3,3)};
	point average_point{std::accumulate(pp.cbegin(),pp.cend(),point(0,0),avg_obj<point,point>())};
	std::cout<<"Average point = ("<<average_point.x<<", "<<average_point.y<<")\n";

	// Alternative using for_each
	point average_point2 = std::for_each(pp.cbegin(),pp.cend(),avg_obj<point,point>()).result();
	std::cout<<"Average point using for_each = ("<<average_point2.x<<", "<<average_point2.y<<")\n";

	return 0;
}
