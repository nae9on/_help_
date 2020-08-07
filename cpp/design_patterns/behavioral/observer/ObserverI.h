/*
 * ObserverI.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_OBSERVERI_H_
#define BEHAVIORAL_OBSERVER_OBSERVERI_H_

class IObserver{
public:
    IObserver() = default;
    virtual void update(int old_data, int current_data) = 0;
    virtual ~IObserver() = default;
};

#endif /* BEHAVIORAL_OBSERVER_OBSERVERI_H_ */
