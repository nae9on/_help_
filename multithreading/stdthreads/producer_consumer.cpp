/*
 * Producer consumer example
 * Producer takes some time to create work. Producer pushes work into a queue.
 * Consumer pops work from a queue. Consumer takes some time to consume work.
 */

#include <thread>
#include <mutex>

#include <queue>
#include <iostream>
#include <cassert>

std::mutex CoutMutex;

void Write(char C)
{
    std::lock_guard<std::mutex> Lck{CoutMutex};
    std::cout<<C<<std::this_thread::get_id()<<" "<<std::flush;
}

struct AssemblyLine
{
public:
    using MS = std::chrono::milliseconds;

    void Produce(int i)
    {
        std::this_thread::sleep_for(MS{m_TimeToProduce}); // Create work here
        m_Mutex.lock(); // Better to use std::lock_guard taking advantage of RAII
        m_Work.push(i); // Add work here
        Write('P');
        m_Mutex.unlock();
    }

    void Consume()
    {
        if(m_Mutex.try_lock()) // Returns immediately if the mutex is locked by another thread
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
        {
            std::unique_lock<std::mutex> Lck1{m_Mutex};
            while(!m_Work.empty())
            {
              std::cout << m_Work.front() << " ";
              m_Work.pop();
            }

        } // Ensures early unlock to minimize the critical section for m_Mutex

        std::lock_guard<std::mutex> Lck2{CoutMutex};
        std::cout << std::endl;
    }

    bool HasWork() const { return m_Work.size()>0; }

    int64_t TimeToProduce() { return m_TimeToProduce; }

private:
    const int64_t m_TimeToProduce{50};
    const int64_t m_TimeToConsume{100};
    std::queue<int> m_Work;
    std::mutex m_Mutex;
};

AssemblyLine Line;

void Produce()
{
    for(int i=0; i<10; ++i)
    {
        Line.Produce(i);
    }
}

void Consume()
{
    while(Line.HasWork())
    {
        Line.Consume();
    }
}

int main()
{
    // Main thread assigns task of producing work to a producer thread
    std::thread ProducerThread{Produce};

    // Make the main thread wait before assigning tasks to consumer threads
    // This is to make sure that there is already some work added by the producer thread
    // before consumers start to consume.
    std::this_thread::sleep_for(AssemblyLine::MS{10*Line.TimeToProduce()});

    // Main thread assigns task of consuming work to consumer threads
    std::thread ConsumerThread1{Consume};
    std::thread ConsumerThread2{Consume};

    ProducerThread.join();
    ConsumerThread1.join();
    ConsumerThread2.join();

    // Print queue
    Line.Print();

    assert(!Line.HasWork() && "Still work is remaining!");

    std::cout<<"End of main"<<std::endl;

    return 0;
}
