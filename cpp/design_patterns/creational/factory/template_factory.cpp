/*
 * template_factory.cpp
 *
 *  Created on: 21 Jun 2020
 *      Author: ahkad
 */

#include "button.h"
#include "UI.h"
#include <memory>

template<typename T>
class someOS_UI: public UI{
public:
    someOS_UI(){}
    std::unique_ptr<Button> createButton() const override{
        return std::make_unique<T>();
    }
    ~someOS_UI(){}
};

int main_template_factory(){ // main_template_factory

    std::unique_ptr<UI> d1(new someOS_UI<WindowsButton>());
    d1->doSomething();

    std::unique_ptr<UI> d2(new someOS_UI<LinuxButton>());
    d2->doSomething();

    return 0;
}
