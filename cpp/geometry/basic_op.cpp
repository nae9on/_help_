/*
 * basic_op.cpp
 *
 *  Created on: 18 Nov 2019
 *      Author: ahkad
 */

#include <iostream>

#include <boost/geometry.hpp>

namespace bg = boost::geometry;
using point2d = bg::model::point<double, 2, bg::cs::cartesian>;
using point3d = bg::model::point<double, 3, bg::cs::cartesian>;
using seg = bg::model::segment<point2d>;
using line = bg::model::linestring<point2d>;

int basic_op(){

	point2d p1(1, 1), p2(2, 2);
	std::cout << "Distance p1-p2 is: " << bg::distance(p1, p2) << std::endl;

	point3d p3(1, 0, 0), p4(0, 1, 0);
	std::cout << "Distance p3-p4 is: " << bg::distance(p3, p4) << std::endl;

	seg s1; // a segment has only two points
	s1.first = point2d(0,0);
	s1.second = point2d(1,0);
	std::cout << "Distance s1-p1 is: " << bg::distance(s1, p1) << std::endl;

	line l1; // a line can have as many points
	l1.push_back(point2d(0,0));
	l1.push_back(point2d(1,0));
	l1.push_back(point2d(2,0));
	std::cout << "Distance l1-p1 is: " << bg::distance(l1, p1) << std::endl;

	auto c1 = bg::cross_product(p3,p4);
	std::cout << "Cross-product p3-p4 = "<<bg::dsv(c1)<<"\n";

	return 0;
}
