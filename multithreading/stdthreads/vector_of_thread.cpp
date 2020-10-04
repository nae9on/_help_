#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <cassert>

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

int main()
{
    // Sum all integers from 1 to N
    constexpr std::size_t N{10000};
    constexpr std::size_t NumThreads{10};
    constexpr double ReferenceSum = N*(N+1)/2;

    std::vector<Sum> VecSum(NumThreads);
    std::vector<std::thread> VT(NumThreads); // default constructed threads are primarily useful as the target for moves.
    for(std::size_t i=0; i<VT.size(); ++i)
    {
        VecSum[i] = Sum((N/NumThreads)*i+1, (N/NumThreads)*(i+1));
        std::thread Thread{std::ref(VecSum[i])}; // important!
        VT[i] = move(Thread); // important!
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
