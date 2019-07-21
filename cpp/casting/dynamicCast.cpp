/*
 * dynamicCast.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

// References
// [1] https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019

#include <iostream>
#include <typeinfo>
// Note: when using typeid, the return of type name is implementation defined.

class Container{ // Interface class
private:
	static unsigned count;
public:
	Container(){
		std::cout<<"Base class constructor called\n";
		incremetCount();
	}
	void incremetCount(){
		count++;
	}
	static void printCount(){
		std::cout<<"Total containers derived from base = "<<count<<"\n";
	}
	virtual int returnSize() const=0; // pure virtual function returning the size of container
	virtual double& operator[](int i) const=0; // pure virtual function returning the element [i] of container

	// virtual makes sure that first derived class destructor is called.
	// for this reason the destructor of an abstract class should always be virtual.
	virtual ~Container(){
		std::cout<<"Base class destructor called\n";
	}
};
unsigned Container::count = 0;

class vecContainer : public Container { // Implementation class
private:
	unsigned size;
	double* data;
public:
	vecContainer(unsigned _size): size{_size}, data{new double[size]{}} {
		std::cout<<"Derived class vecContainer's constructor called\n";
	}
	void printSize(){
		std::cout<<"Size of vecContainer = "<<size<<"\n";
	}
	int returnSize() const{
		return size;
	}
	double& operator[](int i) const{
		return data[i];
	}
	~vecContainer(){
		delete[] data;
		std::cout<<"Derived class vecContainer's destructor called\n";
	}
};

class arrayContainer : public Container { // Implementation class
private:
	unsigned size;
	double* data;
public:
	arrayContainer(unsigned _size): size{_size}, data{new double[size]{}} {
		std::cout<<"Derived class arrayContainer's constructor called\n";
	}
	void printLength(){
		std::cout<<"Length of arrayContainer = "<<size<<"\n";
	}
	int returnSize() const{
		return size;
	}
	double& operator[](int i) const{
		return data[i];
	}
	~arrayContainer(){
		delete[] data;
		std::cout<<"Derived class arrayContainer's destructor called\n";
	}
};

// A function which accepts any container
void printContainerData(Container& c){
	for (int i=0; i<c.returnSize(); i++)
		std::cout<<c[i]<<"\t";
	std::cout<<"\n";
}

int main()
{
	/*
	 * dynamic_cast does run-time type check [1].
	 * The run-time type check done by dynmic_cast is an overhead.
	 * dynamic_cast only works on pointers and references.
	 */

	// Container b; // An object of an abstract class cannot be created.

	if(0)
	{
	vecContainer d1(5); // Derived class constructor implicitly calls base class constructor first.
	printContainerData(d1);
	Container::printCount();
	// Derived class destructor called automatically as d1 goes out of scope.
	// Derived class destructor implicitly calls base class destructor after.
	}

	if(0)
	{
	vecContainer* d1; // Declares a pointer but does not create an object
	Container::printCount(); // prints 0
	}

	if(1)
	{
	vecContainer* d1 = new vecContainer(5);
	std::cout<<"The type of d1 is "<<typeid(d1).name()<<"\n";
	printContainerData(*d1);
	Container::printCount();
	delete d1;
	// Note derived class destructor is not called automatically, but delete
	// is needed to free the heap memory. delete calls the derived class destructor.
	}

	if(0)
	{
	Container* b1 = new vecContainer(5);
	Container* b2 = new arrayContainer(7);
	std::cout<<"The type of b1 is "<<typeid(b1).name()<<"\n";
	std::cout<<"The type of b2 is "<<typeid(b2).name()<<"\n";

	//b1->printSize(); // Error, base class has no printSize() fn
	//b2->printLength(); // Error, base class has no printLength() fn

	if(0)
	{

	// Note the different ways

	if(vecContainer* temp = dynamic_cast<vecContainer*>(b1)) // assignment + NULL test
		temp->printSize(); // prints 5

	if(dynamic_cast<arrayContainer*>(b1)!=nullptr) // Evaluates to NULL
		dynamic_cast<arrayContainer*>(b1)->printLength(); // Does not print, program terminates and raises no exception ?

	if(dynamic_cast<vecContainer*>(b2)!=nullptr) // Evaluates to NULL
		dynamic_cast<vecContainer*>(b2)->printSize(); // Does not print

	if(dynamic_cast<arrayContainer*>(b2)!=nullptr)
		dynamic_cast<arrayContainer*>(b2)->printLength(); // prints 7
	}

	// In the below statement a dynamic_cast to a wrong pointer fails
	// dynamic_cast<arrayContainer*>(b1)->printLength();

	// In the below statement a static_cast to a wrong pointer returns as if nothing were wrong
	// static_cast<arrayContainer*>(b1)->printLength();

	if(0)
	{
	static_cast<vecContainer*>(b1)->printSize(); // May not be safe but fortunately is safe now
	static_cast<arrayContainer*>(b1)->printLength(); // Not safe, prints wrong
	static_cast<vecContainer*>(b2)->printSize(); // Not safe, prints wrong
	static_cast<arrayContainer*>(b2)->printLength(); // May not be safe but fortunately is safe now
	}

	delete b1;
	delete b2;
	}

	return 0;
}
