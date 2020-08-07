/*
 * Observable.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_OBSERVABLE_H_
#define BEHAVIORAL_OBSERVER_OBSERVABLE_H_

#include "EventManager.h"

#include <iostream>
#include <memory>

class CObservable{
public:
    std::unique_ptr<CEventManager> events;
    CObservable(){
        events = std::make_unique<CEventManager>();
    }
    void change(int x){
        old_data = current_data;
        current_data = x;
        events->notifyAll(old_data, current_data);
    }
private:
    // state which when changes, all the observers must be notified
    int old_data{0};
    int current_data{0};
};

#endif /* BEHAVIORAL_OBSERVER_OBSERVABLE_H_ */
