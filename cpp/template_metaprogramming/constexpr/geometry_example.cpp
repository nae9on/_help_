/*
 * geometry_example.cpp
 *
 *  Created on: 20 Jul 2020
 *      Author: ahkad
 */

#include <iostream>
#include <cmath>

class point{
public:
    constexpr point(): x{0.0f}, y{0.0f}{}
    constexpr point(const float x_, const float y_): x{x_}, y{y_}{}
    constexpr float getx() const {return x;} // const has nothing to do with constexpr here
    constexpr float gety() const {return y;}
    void setx(const float x_){x=x_;}
    void sety(const float y_){y=y_;}

    friend constexpr point operator+(const point& p1, const point& p2){
        return point(p1.getx()+p2.getx(),p1.gety()+p2.gety());
    }

    constexpr point operator/(float div) const{
        return point(x/div,y/div);
    }

    friend constexpr float dist(const point& p1, const point& p2){
        float dx{p1.getx()-p2.getx()}; // more than 1 statements only possible with C++14 or higher
        float dy{p1.gety()-p2.gety()};
        return std::sqrt(dx*dx+dy*dy);
    }

    // cannot be constexpr because I/O statements are generally not permitted
    // in constexpr functions (Item 15, Scott::EMC++)
    friend std::ostream& operator<<(std::ostream& os, const point& p){
        return p.gety()>=0 ?
                os<<p.getx()<<"+"<<p.gety()<<"j" :
                os<<p.getx()<<""<<p.gety()<<"j";
    }
private:
    float x;
    float y;
};

class line{
public:
    constexpr line(const point& start_, const point& stop_):
            start{start_},stop{stop_},
            length{dist(start,stop)},
            m{std::atan((stop.gety()-start.gety())/(stop.getx()-start.getx()))},
            c{start.gety()-m*start.getx()}{}
    constexpr float getlength() const {return length;}
    constexpr float getslope() const {return m;}
    constexpr point reflect(const point& p) const
    {
        float x1{p.getx()};
        float y1{p.gety()};
        float d{(x1 + (y1 - c)*m)/(1 + m*m)};
        float x2{2*d - x1};
        float y2{2*d*m - y1 + 2*c};
        return point(x2,y2);
    }
private:
    point start, stop;
    float length;
    float m;
    float c;
};

int geometry_example()
{
    // points
    constexpr point p1(-1.0f,0.0f), p2(1.0f,0.0f);
    constexpr point mid = (p1 + p2)/2;
    std::cout<<"mid piont = "<<mid<<std::endl;

    constexpr float d{dist(p1,p2)};
    std::cout<<"d = "<<d<<std::endl;

    // line
    constexpr line L(p1,p2);
    constexpr float length = L.getlength();
    constexpr float slope = L.getslope();
    std::cout<<"length = "<<length<<" slope = "<<slope;

    // reflection
    constexpr point y(0.0f,7.0f);
    constexpr point r = L.reflect(y);
    std::cout<<"\nReflection = "<<r<<std::endl;

    return 0;
}
