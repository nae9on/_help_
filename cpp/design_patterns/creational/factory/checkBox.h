/*
 * checkBox.h
 *
 *  Created on: 21 Jun 2020
 *      Author: ahkad
 */

#ifndef CREATIONAL_FACTORY_CHECKBOX_H_
#define CREATIONAL_FACTORY_CHECKBOX_H_

#include <iostream>

class checkBox{ // Product interface class
public:
    virtual void render() const=0;
    virtual void onTick() const=0;
    virtual ~checkBox(){}
private:
    // No data members!
};

class WindowsCheckBox: public checkBox{
public:
    WindowsCheckBox(){}
    void render() const override{
        std::cout<<"Render windows check box\n";
    }
    void onTick() const override{
            std::cout<<"Do something on clicking windows check box\n";
    }
    ~WindowsCheckBox(){}
};

class LinuxCheckBox: public checkBox{
public:
    LinuxCheckBox(){}
    void render() const override{
        std::cout<<"Render Linux check box\n";
    }
    void onTick() const override{
            std::cout<<"Do something on clicking Linux check box\n";
    }
    ~LinuxCheckBox(){}
};

#endif /* CREATIONAL_FACTORY_CHECKBOX_H_ */
