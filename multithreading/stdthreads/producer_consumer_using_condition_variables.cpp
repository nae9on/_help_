/*
 * Producer-consumer example
 * Producer takes some time to create work. Producer pushes work into a queue.
 * Consumer pops out work from a queue. Consumer takes some time to consume work.
 *
 * Introduces std::unique_lock (MoveConstructible and MoveAssignable but not CopyConstructible or CopyAssignable)
 * and std::condition_variable
 */

#include <thread>
#include <mutex>
#include <condition_variable>

#include <queue>
#include <iostream>
#include <cassert>

std::mutex CoutMutex;

template<typename T>
void Write(const T& Text)
{
    std::lock_guard<std::mutex> Lck{CoutMutex};
    std::cout<<Text<<std::this_thread::get_id()<<" "<<std::flush;
}

struct AssemblyLine
{
public:
    using MS = std::chrono::milliseconds;

    void Produce(std::size_t itr)
    {
        std::this_thread::sleep_for(MS{m_TimeToProduce}); // Create work here
        std::unique_lock<std::mutex> Lck{m_Mutex};
        m_Work.push(itr); // Add work here - critical section
        Write(std::string{"P_"}+std::to_string(itr)+"_");
        m_Cond.notify_all();
    }

    bool Consume()
    {
        std::unique_lock<std::mutex> Lck{m_Mutex};
        // Returns false if the queue is still empty after the max time to wait has expired, otherwise true
        bool NotEmpty = m_Cond.wait_for(Lck, MS{m_MaxTimeToWait}, [this]{return !IsEmpty();});
        if(NotEmpty)
        {
            auto item = m_Work.front();
            m_Work.pop(); // Remove work here - critical section
            Lck.unlock();
            std::this_thread::sleep_for(MS{m_TimeToConsume}); // Process work here
            Write(std::string{"C_"}+std::to_string(item)+"_");
        }
        else
        {
            Write("Waited_long_enough_and_still_no_work_");
            return true;
        }
        return false;
    }

    void Print()
    {
        std::queue<std::size_t> Copy;

        {
            std::lock_guard<std::mutex> Lck1{m_Mutex};
            Copy = m_Work; // critical section
        } // Ensures early unlock to minimize the critical section for m_Mutex

        {
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
    }

    bool IsEmpty() const
    {
        return m_Work.empty();
    }

private:
    const int64_t m_TimeToProduce{80}; // Important producer takes less time to produce!
    const int64_t m_TimeToConsume{100};
    const int64_t m_MaxTimeToWait{1000}; // Should be more than time to produce!
    std::queue<std::size_t> m_Work;
    std::mutex m_Mutex{};
    std::condition_variable m_Cond{};
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
    while(1)
    {
        if(bool IsTimedOut = Line.Consume())
        {
            (void) IsTimedOut; // To avoid un-used variable warning
            break;
        }
    }

    Write("No_work_thus_Died_");
}

int main()
{
    AssemblyLine Line{};

    // Main thread assigns task of producing work to a producer thread
    std::thread ProducerThread{Produce, std::ref(Line), 10};

    // Main thread assigns task of consuming work to consumer threads
    constexpr std::size_t NumConsumers{3};
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

    assert(Line.IsEmpty() && "Still work is remaining!");

    std::cout<<"End of main"<<std::endl;

    return 0;
}
