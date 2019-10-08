/*
 * simple_array.cpp
 *
 *  Created on: Aug 27, 2019
 *      Author: akadar
 *
 * std::array
 * std::array is the simplest and was introduced in C++11. std::array container has some
 * advantages over a C-style array (int a[]). Its interface makes it more convenient to
 * find its size, and use with STL-style iterator-based algorithms. At the same time it
 * is equally fast. The most important advantage of std::array over C-style array is that
 * it saves users from surprising and nasty implicit conversions to pointer.
 * Note that std::array container allocates memory on the stack.
 * References
 * [1] http://www.cplusplus.com/reference/array/array/
 * [2] https://stackoverflow.com/questions/30263303/stdarray-vs-array-performance
 *
 * std::valarray is a standard non-STL container (called "almost container" by Bjarne)
 * std::valarray is the next simplest and was introduced in C++03. It is variable size
 * unlike std::array and has mathematical functions defined for numeric computation such as
 * +, -, cosine, sine etc. It also allows data slicing. std::valarray container allocates
 * memory on the heap like std::vector.
 * References
 * [3] http://www.cplusplus.com/reference/valarray/valarray/
 * [4] https://stackoverflow.com/questions/8965562/what-is-the-difference-between-stdvalarray-and-stdarray
 *
 * std::vector
 * std::vector is even more convenient than std::valarray. std::vector is thought to be less
 * performant than std::valarray and std::array. However, the exact performance difference is
 * debatable.
 * References
 * [5] http://www.cplusplus.com/reference/vector/vector/
 * [6] https://stackoverflow.com/questions/1602451/c-valarray-vs-vector
 *
 */

#include <iostream>
#include <array>
#include <valarray>

class Shape{
public:
	virtual void show() const = 0;
	virtual ~Shape(){}
private:
};

class Circle: public Shape{
public:
	void show() const {
		std::cout<<"In Circle, y = "<<y<<"\n";
	}
	int getCircle(){
		return y;
	}
private:
	int y;
};

int simple_array(){

	std::array<double,10> arr1;
	for (size_t i = 0; i<10; i++) arr1[i] = i;

	std::valarray<double> arr2;
	arr2.resize(10);
	for (size_t i = 0; i<10; i++) arr2[i] = i;
	arr2+=10;

	Circle arry[3];
	std::array<Circle,3> arr2y;

	Shape* ptr = arry;
	ptr->show(); // OK, ptr points to arry[0]
	(ptr+1)->show(); // disaster, because size(Circle)>size(Shape) and ptr[1] does not point to arry[1]
	(ptr+2)->show(); // disaster, because size(Circle)>size(Shape) and ptr[2] does not point to arry[2]

	// Shape* ptr2 = arr2y; // Error no implicit conversion, disaster prevented.

	return 0;
}
