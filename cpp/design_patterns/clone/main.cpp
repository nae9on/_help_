#include "header.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <valarray>

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

constexpr int N{1};
constexpr int S{10000000};

// private base = implementation detail + no further derivation required
// + no conversion from CExtWTObject* to CWTObject*
class CWTObject : public IWTObject, private CExtWTObject
{
public:    

   CWTObject()
        : data(S)
   {}

   CWTObject* original_clone() const override
   {
       //std::cout<<"New CWTObject\n";
       return new CWTObject(*this);
   };

   int GetG() const override { return g; }

   void SetX(int x_) override { x = x_; }
   void SetY(int y_) override { y = y_; }
   void SetG(int g_) override { g = g_; }

   void print() const override
   {
       std::cout<<"Print CWTObject : ";
       std::cout << GetX() << " " << GetY() << " " << GetG() << " " << std::endl;
   }

private:
   int g{};
   std::valarray<double> data;
};

int main()
{
    // Create internal
    std::shared_ptr<IWTObject> WTObj = std::make_shared<CWTObject>();
    WTObj->SetX(10);
    WTObj->SetY(20);
    WTObj->SetG(-1);
    WTObj->print();

    // Clone internal
    std::shared_ptr<IWTObject> CloneWTObj(WTObj->original_clone());

    // Create external
    std::shared_ptr<IExtWTObject> ExtWTObj(WTObj->clone());
    ExtWTObj->print();

    // Change internal
    WTObj->SetX(100);
    WTObj->SetY(200);
    WTObj->SetG(-10);
    WTObj->print();
    CloneWTObj->print();

    // Check external again
    ExtWTObj->print();

    // Timings
    auto t1 = clk::now();
    std::vector<std::shared_ptr<IWTObject>> VecInternal;
    for(int i=0; i<N; ++i)
    {
        std::shared_ptr<IWTObject> Clone(WTObj->original_clone());
        VecInternal.push_back(std::move(Clone));
    }
    auto t2 = clk::now();
    std::cout << "elapsed time clone internal: " << dt(t2-t1).count() << "s\n";

    auto t3 = clk::now();
    std::vector<std::shared_ptr<IExtWTObject>> VecExternal;
    for(int i=0; i<N; ++i)
    {
        std::shared_ptr<IExtWTObject> Clone(WTObj->clone());
        VecExternal.push_back(std::move(Clone));
    }
    auto t4 = clk::now();
    std::cout << "elapsed time clone external: " << dt(t4-t3).count() << "s\n";

    // Optional
    CWTObject Temp;
    // CExtWTObject Temp1(Temp); // error due to private base
}
