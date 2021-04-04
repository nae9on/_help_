/*
 * particle.h
 *
 *  Created on: 28 Oct 2019
 *      Author: ahkad
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <array>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include "randomGenerator.h"

namespace DP{

template<short DIM>
class point{
public:
	point() = default;
	point(const std::initializer_list<double>& x_){
		assert(x_.size()==DIM && "point dimension mismatch");
		std::copy(x_.begin(),x_.end(),x.begin());
	}
	point(const std::array<double, DIM>& x_){
		assert(x_.size()==DIM && "point dimension mismatch");
		std::copy(x_.begin(),x_.end(),x.begin());
	}
    double& operator[](const short& i) {
            return x[i];
    }
    double get(const short& i) const{
            return x[i];
    }
    double getDistSq(const point& p) const{
            double dist{0.0};
            for (short i = 0; i < DIM; ++i) {
                    dist+=(p.get(i)-x[i])*(p.get(i)-x[i]);
            }
            return dist;
    }
    friend std::ostream& operator<<(std::ostream& os, const point& p){
    	os<<"(";
    	for (short i = 0; i < DIM; ++i) {
    		os<<p.get(i);
    		if(i<DIM-1) os<<", ";
    	}
		os<<")";
		return os;
    }
    point& operator+=(const point& rhs){
        for (short i = 0; i < DIM; ++i) {
                x[i]+=rhs.get(i);
        }
    	return *this;
    }
    point& operator/=(const double& rhs){
        for (short i = 0; i < DIM; ++i) {
                x[i]/=rhs;
        }
    	return *this;
    }
    bool operator==(const point& rhs) const{
    	bool flag{true};
        for (short i = 0; i < DIM; ++i){
                if(this->get(i)!=rhs.get(i)){
                	flag = false;
                	break;
                }
        }
    	return flag;
    }
protected:
std::array<double, DIM> x;
};

template<short DIM>
class randPoint: public point<DIM>{
        using randPointGenType = DP::randGen;
        using point<DIM>::x;
public:
        randPoint(){
        	if(randPointGen.get()==nullptr){
        		assert(0 && "Random number generator not initialized");
        	}
			for(short i = 0; i < DIM; ++i){
				x[i] = (randPointGen.get()+i)->getNum();
			}
        }
        static void Initialize(std::vector<std::pair<double,double>> limits){
        	if(randPointGen.get()==nullptr){
        		assert(limits.size()==DIM && "point dimension mismatch");
        		std::cout<<"Initializing random number generator\n";
				randPointGen = std::unique_ptr<randPointGenType[]>(new randPointGenType[DIM]);
				for(short i = 0; i<DIM; ++i){
					(randPointGen.get()+i)->setDist(limits[i].first,limits[i].second);
				}
			}
        }
private:
        static std::unique_ptr<randPointGenType[]> randPointGen; // association
};

template<short DIM>
std::unique_ptr<DP::randGen[]> randPoint<DIM>::randPointGen = nullptr;
}
#endif /* PARTICLE_H_ */
