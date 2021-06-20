/*
 * Producer-consumer example
 * Producer takes some time to create work. Producer pushes work into a queue.
 * Consumer pops out work from a queue. Consumer takes some time to consume work.
 *
 * Introduces the simple std::lock_guard (not CopyAssignable)
 * Note: The scoped_lock is a strictly superior version of lock_guard and thus makes it obsolete.
 * Reference https://stackoverflow.com/questions/43019598/stdlock-guard-or-stdscoped-lock
 */

#include <thread>
#include <mutex>

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
        m_Mutex.lock();
        m_Work.push(itr); // Add work here - critical section
        m_Mutex.unlock();
        Write(std::string{"P_"}+std::to_string(itr)+"_");
        std::call_once(Flag, [](){ Init(); });
    }

    void Consume()
    {
        // try_lock returns immediately irrespective of whether the mutex is locked by another thread or not
        // Note: very important to check IsFirstItemProduced first due to short-circuit evaluation!
        if(IsFirstItemProduced && m_Mutex.try_lock())
        {
            auto item = m_Work.front();
            m_Work.pop(); // Remove work here - critical section
            m_Mutex.unlock();
            std::this_thread::sleep_for(MS{m_TimeToConsume}); // Process work here
            Write(std::string{"C_"}+std::to_string(item)+"_");
        }
        else
        {
            // Do something else in the meantime while Producer is adding work
            std::this_thread::sleep_for(MS{m_Time4ExtraWorkByConsumer});
            Write('X');
        }
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

    bool HasWork() const
    {
        return !IsEmpty() || !IsFirstItemProduced;
    }

    bool IsEmpty() const
    {
        return m_Work.empty();
    }

    int64_t TimeToProduce() { return m_TimeToProduce; }

    static void Init()
    {
        IsFirstItemProduced = true;
        Write("First_item_has_been_produced_");
    }

    static bool IsFirstItemProduced;

private:
    const int64_t m_TimeToProduce{80}; // Important producer takes less time to produce!
    const int64_t m_TimeToConsume{100};
    const int64_t m_Time4ExtraWorkByConsumer{10};
    std::queue<std::size_t> m_Work;
    std::mutex m_Mutex{};    
    static std::once_flag Flag;
};

bool AssemblyLine::IsFirstItemProduced = false;
std::once_flag AssemblyLine::Flag{};

void Produce(AssemblyLine& Line, std::size_t N)
{
    for(std::size_t itr=1; itr<=N; ++itr)
    {
        Line.Produce(itr);
    }
}

void Consume(AssemblyLine& Line)
{
    // Important producer takes less time to produce otherwise there is no work!
    while(Line.HasWork())
    {
        Line.Consume();
    }

    Write("No_work_thus_Died_");
}

int main()
{
    AssemblyLine Line{};

    // Main thread assigns task of producing work to a producer thread
    std::thread ProducerThread{Produce, std::ref(Line), 10};

    // Make the main thread wait before assigning tasks to consumer threads
    // This is to make sure that there is already some work added by the producer thread
    // before consumers start to consume.
    //std::this_thread::sleep_for(AssemblyLine::MS{10*Line.TimeToProduce()});
    // Note: the above was solved by using std::once_flag!

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
