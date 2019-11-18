/*
 * rtree_search.cpp
 *
 *  Created on: 18 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <boost/random.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
using point2d = bg::model::point<double, 2, bg::cs::cartesian>;
using value = std::pair<point2d, size_t>;

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

class comp{
public:
	comp() = delete;
	comp(point2d ref_):ref{ref_}{}
	bool operator()(const value& v1, const value& v2){
		return(bg::distance(v1.first,ref) < bg::distance(v2.first,ref));
	}
private:
	point2d ref;
};

class rndGen{
	using dist = boost::random::uniform_real_distribution<double>;
	using rng = boost::mt19937;
public:
	rndGen(){
		d = dist(0,1);
		r = rng(std::time(0));
	}
	double operator()(){
		return d(r);
	}
private:
	dist d;
	rng r;
};

int rtree_search(){

	constexpr size_t NP = 1000000, QP = 5;

	rndGen rg;

	// create vector<pair> for reference solution
	std::vector<value> vec;

	// create rtree using default constructor
	bgi::rtree<value, bgi::quadratic<16>> rtree;

	// insert some points
	point2d ref(0,0);
	dt elapsed_seconds_vec, elapsed_seconds_rtree;
	for(size_t i=0 ; i<NP; ++i)
	{
		double x{rg()}, y{rg()};
	    value val = value(std::make_pair(point2d(x,y), i));

	    auto begin = clk::now();
	    vec.push_back(val);
	    elapsed_seconds_vec+=clk::now()-begin;

	    begin = clk::now();
	    rtree.insert(val);
	    elapsed_seconds_rtree+=clk::now()-begin;
	}
	std::cout<<"Init time vec = "<<elapsed_seconds_vec.count()<<"sec\n";
	std::cout<<"Init time rtree = "<<elapsed_seconds_rtree.count()<<"sec\n\n";

	// find QP nearest values to ref point using nth_element
	auto tbeg1 = clk::now();
	std::nth_element(vec.begin(),vec.begin()+QP,vec.end(),comp(ref));
	auto tend1 = clk::now();

	// find QP nearest values to ref point using rtree
	std::vector<value> result_n;
	auto tbeg2 = clk::now();
	rtree.query(bgi::nearest(ref, QP), std::back_inserter(result_n));
	auto tend2 = clk::now();

	// reference results using nth_element
	std::cout<<"Index of nearest points: ";
	for(auto it=vec.cbegin(); it!=(vec.cbegin()+QP); ++it){
		std::cout<<it->second<<" ";
	}
	std::cout<<"\nTime taken = "<<dt(tend1-tbeg1).count()<<"sec\n\n";

	// display results
	std::cout << "knn query point:" << std::endl;
	std::cout << bg::wkt<point2d>(ref) << std::endl;
	std::cout << "knn query result:" << std::endl;
	BOOST_FOREACH(value const& v, result_n)
	    std::cout << bg::wkt<point2d>(v.first) << " - " << v.second << std::endl;
	std::cout<<"Time taken = "<<dt(tend2-tbeg2).count()<<"sec\n";
	return 0;
}
