/*
 * Introduces the plain mutex std::mutex
 * Example Moving a std::thread (not CopyConstructible or CopyAssignable) using std::move
 *
 */

#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <cassert>
#include <mutex>
#include <string>

using namespace std::string_literals;

struct Sum
{
    Sum() = default;
    Sum(int Start, int End)
        : s_Start{Start}
        , s_End{End}{}

    void operator()()
    {
        for(int i=s_Start; i<=s_End; ++i)
        {
            s_Sum += i;
        }
    }

    int s_Start{};
    int s_End{};
    double s_Sum{};

};

std::mutex Cout_mutex;
void Write(const std::string& Str)
{
    Cout_mutex.lock();
    std::cout<<Str<<std::endl;
    Cout_mutex.unlock();
}

int main()
{
    std::size_t MaxHardwareThreads =std::thread::hardware_concurrency();
    std::cout<<"#Hardware threads available = "<<MaxHardwareThreads<<std::endl;

    // Sum all integers from 1 to N
    constexpr std::size_t N{10000};
    constexpr std::size_t NumThreads{20}; // Notice NumThreads can be greater than MaxHardwareThreads
    constexpr double ReferenceSum = N*(N+1)/2;

    std::vector<Sum> VecSum(NumThreads);

    // Default constructed threads are primarily useful as the target for moves.
    // A default-constructed (non-initialized) thread object is not joinable, and its thread id is common for all non-joinable threads.
    std::vector<std::thread> VT(NumThreads);
    for(std::size_t itr=0; itr<VT.size(); ++itr)
    {
        VecSum[itr] = Sum((N/NumThreads)*itr+1, (N/NumThreads)*(itr+1));

        // An initialized thread object represents an active thread of execution; Such a thread object is joinable, and has a unique thread id.
        std::thread Thread{std::ref(VecSum[itr])}; // create a thread and assign work

        VT[itr] = std::move(Thread); // threads can be moved but not copied

        //  A joinable thread becomes not joinable if moved from, or if either join or detach are called on them.
        if(!Thread.joinable()) // Once the thread has been moved it is not joinable anymore
        {
            Write("Temporary thread " + std::to_string(itr) + " not joinable anymore"s);
        }
    }

    for(std::size_t i=0; i<VT.size(); ++i)
    {
        VT[i].join();
    }

    double TotalSum{};
    for(std::size_t i=0; i<VT.size(); ++i)
    {
        TotalSum += VecSum[i].s_Sum;
    }

    assert(ReferenceSum==TotalSum);
    std::cout<<"End of main"<<std::endl;

    return 0;
}
