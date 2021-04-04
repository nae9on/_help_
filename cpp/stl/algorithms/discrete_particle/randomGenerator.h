/*
 * randomGenerator.h
 *
 *  Created on: 28 Oct 2019
 *      Author: ahkad
 */

#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include <ctime>
#include <random>

namespace DP{

class randGen{
        using distType = std::uniform_real_distribution<double>;
public:
        randGen(double min = -1, double max = 1){
                seed = static_cast<unsigned>(std::rand()*time(0)); //time(0)
                rng_engine = std::mt19937(seed);
                setDist(min,max);
        }
        void setDist(double min, double max){
                dist = distType(min,max);
        }
        double getNum() {
                return dist(rng_engine);
        }
private:
        unsigned seed;
        std::mt19937 rng_engine;
        distType dist;
};

}

#endif /* RANDOMGENERATOR_H_ */
