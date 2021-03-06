/*
 * new.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: akadar
 *
 *      // References
 * [1] https://en.cppreference.com/w/cpp/memory/new/operator_new
 * [2] https://en.cppreference.com/w/cpp/memory/new/operator_delete
 * [3] https://www.geeksforgeeks.org/overloading-new-delete-operator-c/
 * [4] http://www.cplusplus.com/reference/new/operator%20new/
 *
 * For some good reasons for overloading new and delete refer[3]
 *
 */

#include <iostream>
#include <vector>

class basic{
public:
	void print() const{
		std::cout<<x<<"\n";
	}

	/*
	 * new and delete operators for a class are generated by compiler by default.
	 * However, they can be disabled using the delete keyword.
	 * static is optional for these functions: whether used or not,
	 * the allocation function is a static member function.
	 */

	//static void* operator new(size_t) = delete;
	//static void  operator delete(void*, size_t) = delete;
	//static void* operator new[](size_t) = delete;
	//static void  operator delete[](void*, size_t) = delete;

private:
	double x{0};
};

class advanced{
public:
	void print() const{
		std::cout<<x<<"\n";
	}

	/*
	 * new and delete operators are generated by compiler by default.
	 * They can be overloaded as follows:
	 */

	// overloaded new and delete
	static void* operator new(size_t n) {
		 // n specifies the number of bytes of memory to be allocated
		std::cout<<"Overloaded new called for class advanced with size "<<n<<"\n";
	    void* p = std::malloc(n);
	    if (p!=nullptr)
	        return p;
	    else
	        throw std::bad_alloc{};
	}
	static void operator delete(void* p) {
		std::cout<<"Overloaded delete called for class advanced\n";
		free(p);
	}

	// overloaded new[] and delete[]
	static void* operator new[](size_t n) {
		 // n specifies the number of bytes of memory to be allocated
		std::cout<<"Overloaded new[] called for class advanced with size "<<n<<"\n";
	    void* p = std::malloc(n);
	    if (p!=nullptr)
	        return p;
	    else
	        throw std::bad_alloc{};
	}
	static void operator delete[](void* p) {
		std::cout<<"Overloaded delete[] called for class advanced\n";
		free(p);
	}

private:
	int x{0};
};

/*
 * Note that operator new is declared in the global namespace and not
 * within the std namespace.
 *
 * Also note that new and delete operators are implicitly declared in each
 * translation unit even if the <new> header is not included. They can
 * be globally overloaded if needed. Refer [1], [2] for details.
 */
// replacement of a minimal set of functions:
void* operator new(std::size_t n) {
	std::cout<<"Global new called with size "<<n<<"\n";
    void *p = std::malloc(n);
    if (p!=nullptr)
        return p;
    else
        throw std::bad_alloc{};
}
void operator delete(void* p) noexcept
{
	std::cout<<"Global delete called\n";
    std::free(p);
}
void* operator new[](std::size_t n) {
	std::cout<<"Global new[] called with size "<<n<<"\n";
    void *p = std::malloc(n);
    if (p!=nullptr)
        return p;
    else
        throw std::bad_alloc{};
}
void operator delete[](void* p) noexcept
{
	std::cout<<"Global delete[] called\n";
    std::free(p);
}

int main_new(){

	basic* b1 = new basic;
	delete b1;

	std::cout<<"\n";

	basic* b2 = new basic[2];
	delete[] b2;

	std::cout<<"\n";

	advanced* a1 = new advanced;
	delete a1;

	std::cout<<"\n";

	advanced* a2 = new advanced[2];
	delete[] a2;

	return 0;
}
