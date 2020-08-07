/*
 * Observable.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_OBSERVABLE_H_
#define BEHAVIORAL_OBSERVER_OBSERVABLE_H_

#include "ObservableI.h"
#include "Result.h"

#include <iostream>
#include <memory>

class CObservable{
public:
    std::unique_ptr<IObservable<SResult>> events;
    CObservable()
    {
        events = std::make_unique<IObservable<SResult>>();
    }
    void change(int x)
    {
        data.old_data = data.current_data;
        data.current_data = x;
        events->notifyAll(data);
    }
private:
    // state which when changes, all the observers must be notified
    SResult data;
};

#endif /* BEHAVIORAL_OBSERVER_OBSERVABLE_H_ */
