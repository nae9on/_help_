#include <cmath>
#include "arithmetic.h"

//void funcX(){}; // error
//class X{}; X cx; // error
//int x; // error

void funcY();
class Y;
extern int global_y;
static int xx = 1;

double getAbs(double r, double i){
 return std::sqrt(r*r+i*i);
}
