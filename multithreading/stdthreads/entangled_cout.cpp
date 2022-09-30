/*
 * Example usage of class std::thread and namespace std::this_thread
 * std::cout::operator<<() is already thread-safe.
 * However, std::cout can mix strings when concatenating with the operator<<
 * multiple time per string, across multiple threads.
 *
 * Example
 *
 * Thread 1
 * std::cout << "the quick brown fox " << "jumped over the lazy dog " << std::endl;
 * Thread 2
 * std::cout << "my mother washes" << " seashells by the sea shore" << std::endl;
 *
 * Could just as easily print like this or any other crazy order.
 * my mother washes the quick brown fox seashells by the sea shore \n
 * jumped over the lazy dog \n
 *
 * Therefore, best is to do the following
 * std::stringstream Msg;
 * Msg << "the quick brown fox " << "jumped over the lazy dog " << std::endl;
 * std::cout << msg.str();
 */

#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <chrono>

void Print(const std::string& Str, int Num)
{
  for(int i=0; i<Num; ++i)
  {
      std::cout<<Str<<"_";
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
            std::cout<<s_Str<<"_";
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
    std::string First{"1st is always 1st"};
    std::thread T0{Print, First, Num}; // Pass First by copy
    std::thread T1{Print, std::ref(First), Num}; // Pass First by reference
    std::thread T2{MyPrint("2nd is always 2nd", Num)}; // Pass a function object for the thread to execute
    std::thread T3{MyPrint("3rd is always 3rd", Num)};
    std::thread T4{MyPrint("4th is always 4th", Num)};
    std::thread T5{MyPrint("5th is always 5th", Num)};
    T0.join();
    T1.join();
    T2.join();
    T3.join();
    T4.join();
    T5.join();

    std::cout<<"\nEnd of main"<<std::endl;

    return 0;
}
