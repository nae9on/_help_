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
#include <stdexcept>

class A
{
public:
    // virtual added to make base a run-time polymorphic type
    virtual ~A(){}
};
class B: public virtual A{};
class B1: public B{};
class B2: public B{};
class D: public B1, public B2{};

class Date{};
class IO
{
public:
    virtual ~IO(){}
};
class dateIO: public Date, public IO{};

Date* getDateOutViaIO(IO* pio)
{
    return dynamic_cast<Date*>(pio); // Destination type need not be polymorphic
}

int dynamicCast()
{
	/*
	 * dynamic_cast does run-time type check [1].
	 * The run-time type check done by dynmic_cast is an overhead. It check's if the result
	 * of the type conversion is a valid and complete object of the destination class. This is
	 * considered a performance issue for some situations as it does this by traversing the
	 * inheritance tree which for large trees could be computationally expensive.
	 * dynamic_cast only works on pointers and references, unlike static_cast which also
	 * work for objects (of both fundamental and user-defined types).
	 */

    /*
     * Source type must be polymorphic for dynamic_cast to work
     */
    Date* pdate = new Date;
    //dateIO* pdateio = dynamic_cast<dateIO*>(pdate)); // Error source type is not polymorphic
    (void) pdate;

    /*
     * Common usage Base* -> Derived*
     */
    B1* pb1 = new D;
    if(D* pd = dynamic_cast<D*>(pb1))
    {
        (void) pd;
        std::cout<<"Two reasons why the operation is successful:\n"
                 <<"1. operand pb1 is of type B1* and B1 is a run-time polymorphic type\n"
                 <<"2. *pb1 holds a complete D object\n\n";
    }
    else
    {
        // When no complete object of destination type is contained withing the source object
        std::cout<<"dynamic_cast evaluates to a nullptr\n\n";
    }
    (void) pb1;

    /*
     * Derived* -> Base* does not need a cast
     */
    Date* pdate1 = new dateIO;
    (void) pdate1;

    /*
     * Interesting example of wrapping a concrete type in a polymorphic type
     * for transmissiom through a polymorphic type system and than unwrap later
     */
    IO* pio = new dateIO; // dateIO object contains a concrete type Date object
    Date* pdate2 = getDateOutViaIO(pio);
    (void) pdate2;

    /*
     * dynamic_cast raises std::bad_cast exception when the run-time check performed
     * on reference to polymorphic class type fails.
     */
    try
    {
        IO obj;
        D& rd = dynamic_cast<D&>(obj); // D and IO are un-related
        (void) rd;
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what()<<"\n\n";
    }

    /*
     * What happens in case of a shared object (when virtual inheritance is used)?
     */
    A* pa = new D;
    if(B* pb = dynamic_cast<B*>(pa)) // ambiguous which B? B<-B1<-D or B<-B2<-D
    {
        (void) pb;
    }
    else
    {
        std::cout<<"dynamic_cast evaluates to a nullptr\n\n";
    }
    (void) pa;

	std::cout<<"End!"<<std::endl;

	return 0;
}
