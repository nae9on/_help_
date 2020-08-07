/*
 * EventManager.h
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

class CEventManager{
    using eventType = std::string;
public:
    void subscribe(IObserver* obs){
        observer_list.push_back(obs);
    }
    void unsubscribe(IObserver* obs){
        observer_list.erase(std::remove(observer_list.begin(), observer_list.end(), obs),
                observer_list.end());
    }
    void notifyAll(int old_data, int current_data){
        for(const auto& elem : observer_list) elem->update(old_data, current_data);
    }
private:
    std::vector<IObserver*> observer_list;
};

#endif /* BEHAVIORAL_OBSERVER_EVENTMANAGER_H_ */
