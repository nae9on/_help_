/*
 * dynamicCast.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019
 */

#include <iostream>
#include <typeinfo> // for typeid
// Note: when using typeid, the name of the type returned is implementation defined.

#include <exception>

class Container{ // Abstract class
public:
	Container(){
		std::cout<<"Base class constructor called"<<std::endl;
		incrementCount();
	}
	void incrementCount(){
		count++;
	}
	static void printCount(){
		std::cout<<"Total containers derived from base = "<<count<<std::endl;
	}
	virtual int returnSize() const=0; // pure virtual function returning the size of container

	virtual double& operator[](int i) const=0; // pure virtual function returning the element [i] of container

	// virtual makes sure that first derived class destructor is called.
	// for this reason the destructor of an abstract class should always be virtual.
	virtual ~Container(){
		std::cout<<"Base class destructor called"<<std::endl;
	}
private:
	static unsigned count;
};
unsigned Container::count = 0;

class vecContainer : public Container { // Implementation class
public:
	vecContainer(unsigned _size): size{_size}, data{new double[size]{}} {
		std::cout<<"Derived class vecContainer's constructor called"<<std::endl;
	}
	void printSize(){
		std::cout<<"Size of vecContainer = "<<size<<std::endl;
	}
	int returnSize() const{
		return size;
	}
	double& operator[](int i) const{
		return data[i];
	}
	~vecContainer(){
		delete[] data;
		std::cout<<"Derived class vecContainer's destructor called"<<std::endl;
	}
private:
	unsigned size;
	double* data;
};

class arrayContainer : public Container { // Implementation class
public:
	arrayContainer(unsigned _size): size{_size}, data{new double[size]{}} {
		std::cout<<"Derived class arrayContainer's constructor called"<<std::endl;
	}
	void printLength(){
		std::cout<<"Length of arrayContainer = "<<size<<std::endl;
	}
	int returnSize() const{
		return size;
	}
	double& operator[](int i) const{
		return data[i];
	}
	~arrayContainer(){
		delete[] data;
		std::cout<<"Derived class arrayContainer's destructor called"<<std::endl;
	}
private:
	unsigned size;
	double* data;
};

// A function which accepts any container
void printContainerData(Container& c){
	for (int i=0; i<c.returnSize(); i++)
		std::cout<<c[i]<<"\t";
	std::cout<<std::endl;
}

int dynamicCast()
{
	/*
	 * dynamic_cast does run-time type check [1].
	 * The run-time type check done by dynmic_cast is an overhead. It check's if the result
	 * of the type conversion is a valid and complete object of the requested class. This is
	 * considered a performance issue for some situations as it does this by traversing the
	 * inheritance tree which for large trees could be computationally expensive.
	 * dynamic_cast only works on pointers and references, unlike static_cast which can also
	 * work on variables.
	 */

	//Container b; // Error cannot declare variable of an abstract class
	//vecContainer* d1; // Allocates memory for a pointer on stack but does not create an object

	if(0)
	{
	// Derived class constructor implicitly calls base class constructor first.
	vecContainer d1(5);
	printContainerData(d1);
	Container::printCount();
	// Derived class destructor called automatically as d1 goes out of scope.
	// Derived class destructor implicitly calls base class destructor after.
	}

	if(0)
	{
	vecContainer* d1 = new vecContainer(5);
	std::cout<<"The type of d1 is "<<typeid(d1).name()<<std::endl;
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
	std::cout<<"The type of b1 is "<<typeid(b1).name()<<std::endl;
	std::cout<<"The type of b2 is "<<typeid(b2).name()<<std::endl;

	//b1->printSize(); // Error, base class has no printSize() function
	//b2->printLength(); // Error, base class has no printLength() function

	if(0)
	{

	// Note the different ways

	if(vecContainer* temp = dynamic_cast<vecContainer*>(b1)) // assignment + nullptr test
		temp->printSize(); // prints 5

	if(arrayContainer* temp = dynamic_cast<arrayContainer*>(b1)) // Evaluates to nullptr
		temp->printLength();

	if(vecContainer* temp = dynamic_cast<vecContainer*>(b2)) // Evaluates to nullptr
		temp->printSize();

	if(arrayContainer* temp = dynamic_cast<arrayContainer*>(b2))
		temp->printLength(); // prints 7

	}

	// In the below statement a dynamic_cast to a wrong pointer fails and evaluates to nullptr
	//dynamic_cast<arrayContainer*>(b1)->printLength();

	// In the below statement a static_cast to a wrong pointer returns as if nothing were wrong!
	//static_cast<arrayContainer*>(b1)->printLength();

	if(0)
	{
	static_cast<vecContainer*>(b1)->printSize(); // May not be safe but fortunately is safe now
	static_cast<arrayContainer*>(b1)->printLength(); // Not safe, prints wrong
	static_cast<vecContainer*>(b2)->printSize(); // Not safe, prints wrong
	static_cast<arrayContainer*>(b2)->printLength(); // May not be safe but fortunately is safe now
	}

	delete b1; // consider using smart pointers
	delete b2;
	}

	// dynamic_cast raises std::bad_cast exception when the run-time check performed on references
	// to polymorphic class types fails.
	if(1){
		vecContainer v1(5); // 5 elements
		Container& c1 = dynamic_cast<Container&> (v1); // OK v1 contains a complete Container object
		std::cout<<"Size = "<<c1.returnSize()<<std::endl;

		try{
			arrayContainer v2(2);
			Container& c2 = dynamic_cast<Container&> (v2);
			vecContainer& ac = dynamic_cast<vecContainer&> (c2);
			// std::bad_cast raised since arrayContainer is an incomplete object of vecContainer
			ac.printSize();
		}catch(const std::exception& e){
			std::cout<<"Dynamic cast failed "<<e.what()<<std::endl;
		}
	}

	std::cout<<"End!"<<std::endl;

	return 0;
}
