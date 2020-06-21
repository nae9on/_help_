/*
 * UI.h
 *
 *  Created on: 21 Jun 2020
 *      Author: ahkad
 */

#ifndef CREATIONAL_FACTORY_UI_H_
#define CREATIONAL_FACTORY_UI_H_

#include "button.h"
#include <memory>

// Client/Creator class
class UI{
public:
    void doSomething(){
        // Abstract button
        std::unique_ptr<Button> okButton = this->createButton();
        okButton->render();
        okButton->onClick();
        std::cout<<"\n";
    }
    /*
     * 1. Factory Method can be abstract or may return a default product.
     * 2. It does not have to create new products all the time and can return objects
     * from a cache, an object pool, or another source.
     * 3. The return type of the Factory Method should be the same as the product interface.
     */
    virtual std::unique_ptr<Button> createButton() const=0;
    virtual ~UI(){}
};

#endif /* CREATIONAL_FACTORY_UI_H_ */
