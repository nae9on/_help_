#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <chrono>

void Print(const std::string& Str, int Num)
{
  for(int i=0; i<Num; ++i)
  {
      std::cout<<Str;
      std::chrono::milliseconds Duration(1);
      std::this_thread::sleep_for(Duration);
  }
}

struct MyPrint
{
    MyPrint(const std::string& Str, int Num)
        : s_Str{Str}
        , s_Num{Num}{}

    void operator()()
    {
        for(int i=0; i<s_Num; ++i)
        {
            std::cout<<s_Str<<" ";
            std::chrono::milliseconds duration(1);
            std::this_thread::sleep_for(duration);
        }
    }

    std::string s_Str{};
    int s_Num{};
};

int main()
{
    constexpr int Num{2};
    std::string First{"1"};
    std::thread T0{Print, First, Num}; // Pass First by copy
    std::thread T1{Print, std::ref(First), Num}; // Pass First by reference
    std::thread T2{MyPrint("2", Num)}; // Pass a function object for the thread to execute
    std::thread T3{MyPrint("3", Num)};
    std::thread T4{MyPrint("4", Num)};
    std::thread T5{MyPrint("5", Num)};
    T0.join();
    T1.join();
    T2.join();
    T3.join();
    T4.join();
    T5.join();

    std::cout<<"\nEnd of main"<<std::endl;

    return 0;
}
