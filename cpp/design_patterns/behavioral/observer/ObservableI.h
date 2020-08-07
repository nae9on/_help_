/*
 * ObservableI.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_EVENTMANAGER_H_
#define BEHAVIORAL_OBSERVER_EVENTMANAGER_H_

#include "ObserverI.h"

#include <vector>
#include <string>
#include <algorithm>

// IObservable = CEventManager
// It is not really an interface class!
// template on the type of the information passed
// to the observers in the case of an event
template<typename T>
class IObservable{
public:
    void subscribe(IObserver<T>* obs){ // or attach
        if(obs) observer_list.push_back(obs);
    }
    void unsubscribe(IObserver<T>* obs){ // or detach
        auto it = std::find(observer_list.begin(), observer_list.end(), obs);
        if (it != observer_list.end())
        {
            observer_list.erase(it);
        }
    }
    void notifyAll(const T& data){
        for(const auto& elem : observer_list)
        {
            if(elem) elem->update(data);
        }
    }
private:
    std::vector<IObserver<T>*> observer_list;
};

#endif /* BEHAVIORAL_OBSERVER_EVENTMANAGER_H_ */
