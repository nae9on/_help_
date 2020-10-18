/*
 * Producer-consumer example
 * Producer takes some time to create work. Producer pushes work into a queue.
 * Consumer pops out work from a queue. Consumer takes some time to consume work.
 *
 * Introduces the simple std::lock_guard (not CopyAssignable)
 */

#include <thread>
#include <mutex>

#include <queue>
#include <iostream>
#include <cassert>

std::mutex CoutMutex;

void Write(const char Character)
{
    std::lock_guard<std::mutex> Lck{CoutMutex};
    std::cout<<Character<<std::this_thread::get_id()<<" "<<std::flush;
}

struct AssemblyLine
{
public:
    using MS = std::chrono::milliseconds;

    void Produce(std::size_t itr)
    {
        std::this_thread::sleep_for(MS{m_TimeToProduce}); // Create work here
        m_Mutex.lock(); // Better to use std::lock_guard taking advantage of RAII
        m_Work.push(itr); // Add work here
        Write('P');
        m_Mutex.unlock();
    }

    void Consume()
    {
        if(m_Mutex.try_lock()) // Returns immediately irrespective of whether the mutex is locked by another thread or not
        {
            m_Work.pop();
            Write('C');
            m_Mutex.unlock();
            std::this_thread::sleep_for(MS{m_TimeToConsume}); // Process work here
        }
        else
        {
            // Do something else in the meantime while Producer is adding work
            Write('X');
        }
    }

    void Print()
    {
        std::queue<std::size_t> Copy;

        {
            std::lock_guard<std::mutex> Lck1{m_Mutex};
            Copy = m_Work;
        } // Ensures early unlock to minimize the critical section for m_Mutex

        std::lock_guard<std::mutex> Lck2{CoutMutex};
        std::cout << std::endl;
        std::cout << "Work remaining: ";
        while(!Copy.empty())
        {
            std::cout << Copy.front() << " ";
            Copy.pop();
        }
        std::cout << std::endl;
    }

    bool HasWork() const { return m_Work.size()>0; }

    int64_t TimeToProduce() { return m_TimeToProduce; }

private:
    const int64_t m_TimeToProduce{50}; // Important producer takes less time to produce!
    const int64_t m_TimeToConsume{100};
    std::queue<std::size_t> m_Work;
    std::mutex m_Mutex{};
};

void Produce(AssemblyLine& Line, std::size_t N)
{
    for(std::size_t itr=1; itr<=N; ++itr)
    {
        Line.Produce(itr);
    }
}

void Consume(AssemblyLine& Line)
{
    while(Line.HasWork()) // Important producer takes less time to produce!
    {
        Line.Consume();
    }
}

int main()
{

    AssemblyLine Line;

    // Main thread assigns task of producing work to a producer thread
    std::thread ProducerThread{Produce, std::ref(Line), 10};

    // Make the main thread wait before assigning tasks to consumer threads
    // This is to make sure that there is already some work added by the producer thread
    // before consumers start to consume.
    std::this_thread::sleep_for(AssemblyLine::MS{1*Line.TimeToProduce()});

    // Main thread assigns task of consuming work to consumer threads
    constexpr std::size_t NumConsumers{2};
    std::vector<std::thread> Consumers(NumConsumers);
    for(std::size_t itr=0; itr<Consumers.size(); ++itr)
    {
        std::thread ConsumerThread{Consume, std::ref(Line)};
        Consumers[itr] = std::move(ConsumerThread);
    }

    ProducerThread.join();
    for(std::size_t itr=0; itr<Consumers.size(); ++itr)
    {
        Consumers[itr].join();
    }

    Line.Print();

    assert(!Line.HasWork() && "Still work is remaining!");

    std::cout<<"End of main"<<std::endl;

    return 0;
}
