#include <cmath>
#include "arithmetic.h"

//void funcX(){}; // error
//class X{}; X cx; // error
//int x; // error

void funcY();
class Y;
extern int y;

double getAbs(double r, double i){
    return std::sqrt(r*r+i*i);
}
