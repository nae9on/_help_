/*
 * abstract_factory.cpp
 *
 *  Created on: 21 Jun 2020
 *      Author: ahkad
 *
 *
 */

#include "button.h"
#include "checkBox.h"
#include <memory>

// Abstract factory interface
class UIInterface{
public:
    virtual void print() const = 0;
    virtual std::unique_ptr<Button> createButton() const=0;
    virtual std::unique_ptr<checkBox> createCheckBox() const=0;
    virtual ~UIInterface(){}
};

class WindowsFullUI: public UIInterface{
public:
    WindowsFullUI(){}
    void print() const override{
        std::cout<<"I am Windows UI\n";
    }
    std::unique_ptr<Button> createButton() const override{
        return std::unique_ptr<Button>(new WindowsButton());
    }
    std::unique_ptr<checkBox> createCheckBox() const override{
        return std::unique_ptr<checkBox>(new WindowsCheckBox());
    }
    ~WindowsFullUI(){}
};

class LinuxFullUI: public UIInterface{
public:
    LinuxFullUI(){}
    void print() const override{
            std::cout<<"I am Linux UI\n";
    }
    std::unique_ptr<Button> createButton() const override{
        return std::unique_ptr<Button>(new LinuxButton());
    }
    std::unique_ptr<checkBox> createCheckBox() const override{
        return std::unique_ptr<checkBox>(new LinuxCheckBox());
    }
    ~LinuxFullUI(){}
};

class clientApplication{
public:
    clientApplication(std::unique_ptr<UIInterface> UI_){
        UI = std::move(UI_);
        bt = UI->createButton();
        cbox = UI->createCheckBox();
    }
    void show(){
        UI->print();
        bt->onClick();
        cbox->onTick();
    }
private:
    std::unique_ptr<UIInterface> UI;
    std::unique_ptr<Button> bt;
    std::unique_ptr<checkBox> cbox;
};

int main_abstract_factory(){//main_abstract_factory
    std::string OS{"Linux"};

    std::unique_ptr<UIInterface> UI;

    if(OS=="Windows"){
        //UI.reset(new WindowsFullUI);
        UI = std::make_unique<WindowsFullUI>();
    }else if(OS=="Linux"){
        //UI.reset(new LinuxFullUI);
        UI = std::make_unique<LinuxFullUI>();
    }else{
        std::cout<<"Wrong OS"<<std::endl;
    }

    // transfer ownership of UI to the client
    //std::unique_ptr<clientApplication> app(new clientApplication(std::move(UI)));
    auto app = std::make_unique<clientApplication>(std::move(UI));

    app->show();

    std::cout<<"end of main"<<std::endl;
    return 0;
}
