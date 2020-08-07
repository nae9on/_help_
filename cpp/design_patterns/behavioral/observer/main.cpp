/*
 * main.cpp
 *
 *  Created on: 05 Jul 2020
 *      Author: ahkad
 *
 *  Example: A spreadsheet has cells that observes the source cell(s).
 *  When the source cell is changed, the dependent cells are updated from the event.
 *
 *  Each source cell is modeled as an Observable and each dependent cell is modelled
 *  as an Observer. A source cell keeps a list of dependent cells and notifies them when
 *  it is updated.
 *
 *  Each dependent cell has a certain accumulator function which accumulates all the source
 *  cells that it observes and stores the accumulated value. When a source cell changes,
 *  the accumulated value is updated.
 */

#include "Observable.h"
#include "Observer.h"

#include <vector>
#include <memory.h>

int main(){

    // create source cells (or concrete observables)
    std::vector<std::unique_ptr<CObservable>> sources(10);
    for (auto& elem : sources)
    {
        elem = std::make_unique<CObservable>();
    }

    // dependent cells (or observers)
    std::unique_ptr<CObserver> dependent1 = std::make_unique<CObserver>();
    std::unique_ptr<CObserver> dependent2 = std::make_unique<CObserver>();

    // dependent cells subscribe to source cells
    // normally the subscription or attachment takes place in the
    // configure method of the concrete observable
    for (auto& elem : sources)
    {
        elem->events->subscribe(dependent1.get());
        elem->events->subscribe(dependent2.get());
    }

    int i{1};
    for (const auto& elem : sources)
    {
        // event on observables
        elem->change(i++);
    }

    dependent1->print();
    dependent2->print();

    std::cout<<"end of main\n";
    return 0;
}
