/*
 * ObserverI.h
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 */

#ifndef BEHAVIORAL_OBSERVER_OBSERVERI_H_
#define BEHAVIORAL_OBSERVER_OBSERVERI_H_

// template on the type of the information passed
// to the observers in the case of an event
template<class T>
class IObserver{
public:
    virtual void update(const T&) = 0;
    virtual ~IObserver() = default;
};

#endif /* BEHAVIORAL_OBSERVER_OBSERVERI_H_ */
