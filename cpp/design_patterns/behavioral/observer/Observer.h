/*
 * Observer.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_OBSERVER_H_
#define BEHAVIORAL_OBSERVER_OBSERVER_H_

#include "ObserverI.h"
#include "Result.h"

#include<iostream>

class CObserver: public IObserver<SResult>{
public:
    CObserver(){}
    void update(const SResult& data) override{
        accum+=data.current_data-data.old_data;
    }
    void print(){
        std::cout<<"accum = "<<accum<<std::endl;
    }
    virtual ~CObserver() override = default;
private:
    int accum{0};
};

#endif /* BEHAVIORAL_OBSERVER_OBSERVER_H_ */
