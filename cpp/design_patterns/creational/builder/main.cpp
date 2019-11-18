/*
 * main.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: akadar
 *
 * A builder design pattern is a creational design pattern which enables client code
 * to construct complex objects step by step. The pattern allows us to produce different
 * types and representations of an object using the same construction code.
 *
 * This is achieved by breaking a large constructor used to build a complex object
 * of some class into a sequence of steps (functions) which the client code can execute in a
 * specific order to create different objects. This allows separating the complex object
 * construction code from the main business logic of the class advocating single responsibility
 * principle.
 *
 * Example illustrating how a builder design pattern can be used for creating cars (both ordinary
 * and fancy) and other means of transport (such as trucks) by using the same building blocks.
 *
 * References:
 * https://sourcemaking.com/design_patterns/singleton
 *
 */

#include <iostream>
#include "builder.h"
#include <memory>

// Optional class that lists the ordered set of calls required to build a particular
// type of object.
class director{
public:
	void makeCar(builder* b){
		b->setSeats(4);
		b->setEngine(new engineD());
	}

	void makeSUV(builder* b){
		b->setSeats(2);
		b->setEngine(new engineX());
	}

	void makeTruck(builder* b){
		b->setSeats(2);
		b->setEngine(new engineH());
		dynamic_cast<truckBuilder*>(b)->setCapacity(1000);
	}
};

int builder(){

	std::unique_ptr<director> d(new director());

	// Ordinary car
	std::unique_ptr<carBuilder> c1(new carBuilder());
	d->makeCar(c1.get());
	c1->print();

	// Turbo car
	std::unique_ptr<carBuilder> c2(new carBuilder());
	d->makeSUV(c2.get());
	c2->print();

	// Truck
	std::unique_ptr<truckBuilder> t(new truckBuilder());
	d->makeTruck(t.get());
	t->print();

	return 0;
}
