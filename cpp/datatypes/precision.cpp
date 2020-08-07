#include <iostream>
#include <cmath>
#include <iomanip>

#define fcast static_cast<float>

template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const& expected, Actual const& actual, Tolerance const& tolerance)
{
    bool result = (actual >= (expected - tolerance)) && (actual <= (expected + tolerance));
    std::cout<<std::fixed<<std::setprecision(15)<<expected<<" and "<<actual<<" are ";
    if(result){
        std::cout<<"equal for AreClose\n";
    }else{
        std::cout<<"not equal for AreClose\n";
    }
    return result;
}

template<class T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
AlmostEqual(const T a, const T b,  const T epsilon = 1.0e-06)
{
    constexpr T minPrecision = 0.1;

    if (std::isnan(a) || std::isnan(b) || std::isinf(a) || std::isinf(b))
    {
        return false;
    }
    T difference = std::fabs(a-b);

    if (difference <= epsilon)
    {
        return true;
    }
    // We do not want to compare big numbers,
    // especially when then have no mantissa.
    if (difference > minPrecision)
    {
        return false;
    }
    T largest = std::max(std::fabs(a), std::fabs(b));
    T rangeRelDiff = epsilon * largest;

    return difference <= rangeRelDiff;
}

// Q. What if all measurements in meters were expressed in millimeters?
// A. integer arithmetic can be a disaster, float can lead to loss of precision (but still not that bad)
void mm_meters()
{
    // in meters
    double measure = 105.012;

    int x = measure;
    float y = measure;
    double z = measure;

    // in millimeters
    int x1 = measure*1000;
    float y1 = measure*1000;
    double z1 = measure*1000;


    // in meters
    std::cout<<"in meters"<<std::endl;
    std::cout<<std::fixed<<std::setprecision(15)<<x<<" "<<std::sqrt(x*x)<<"\n";  // loss of precision but still not bad
    std::cout<<std::fixed<<std::setprecision(15)<<y<<" "<<std::sqrt(y*y)<<"\n";
    std::cout<<std::fixed<<std::setprecision(15)<<z<<" "<<std::sqrt(z*z)<<"\n";
    std::cout<<"\n\n";

    // in millimeters
    std::cout<<"in millimeters"<<std::endl;
    std::cout<<std::fixed<<std::setprecision(15)<<x1<<" "<<std::sqrt(x1*x1)<<"\n"; // integer overflow, disaster
    std::cout<<std::fixed<<std::setprecision(15)<<y1<<" "<<std::sqrt(y1*y1)<<"\n";
    std::cout<<std::fixed<<std::setprecision(15)<<z1<<" "<<std::sqrt(z1*z1)<<"\n";

    std::cout<<"\n";
}

// Prefer relative comparison over absolute
void compare()
{
    float a{12345.671}, b{12345.679}; // Equal upto 7 digits of precision
    AreClose(a,b,1.0e-6f);
    std::cout<<std::fixed<<std::setprecision(15)<<a<<" and "<<b<<" are ";
    if(AlmostEqual(a,b)){
        std::cout<<"equal for AlmostEqual\n";
    }else{
        std::cout<<"not equal for AreClose\n";
    }
}

// Be careful of integer overflow
void overflow()
{
    using T = int;
    T p1y = 123456;
    T p2x = 123456;
    T p2y = 0;
    T p1x = 0;
    float Intercept1 = fcast(p1y * p2x - p2y * p1x) / fcast(p2x - p1x);
    float Intercept2 = (fcast(p1y) * fcast(p2x)- fcast(p2y) * fcast(p1x)) / (fcast(p2x) - fcast(p1x));
    std::cout<<"\n\nIntercept1 "<<Intercept1<<"\nIntercept2 "<<Intercept2<<"\n\n";

    int x{2000000000}, y{-x};
    std::cout<<"x-y="<<fcast(x-y)<<"\n";
    std::cout<<"x-y="<<fcast(x)-fcast(y)<<"\n";
}

int main_precision()
{
    //mm_meters();
    //compare();
    overflow();
    return 0;
}
